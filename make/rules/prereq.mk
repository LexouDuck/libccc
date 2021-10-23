# This file holds rules to check whether prerequisite programs are correctly installed/available



define check_prereq
	@printf "\n\n"$(C_CYAN)"|=> Checking prerequisite: $1"$(C_RESET)"\n$$ $2\n"
	@- { $2 ; } || \
	{ \
		printf $(C_YELLOW)"$1 is not installed"$(C_RESET)"\n" ; \
		printf $(C_MAGENTA)"Installing...\n" ; \
		$3 ; \
	}
endef



ifeq ($(OS),Windows_NT)
define install_prereq
	printf $(C_RED)"ERROR"$(C_RESET)": Windows platform detected. You must manually install: "
endef
else ifeq ($(UNAME_S),Darwin)
define install_prereq
	brew install $1
endef
else ifeq ($(UNAME_S),Linux)
define install_prereq
	if   [ -x "$(command -v apk)"     ]; then $(SUDO) apk add --no-cache $1 ; \
	elif [ -x "$(command -v apt-get)" ]; then $(SUDO) apt-get install    $1 ; \
	elif [ -x "$(command -v yum)"     ]; then $(SUDO) yum     install    $1 ; \
	elif [ -x "$(command -v pacman)"  ]; then $(SUDO) pacman  install    $1 ; \
	elif [ -x "$(command -v dnf)"     ]; then $(SUDO) dnf     install    $1 ; \
	elif [ -x "$(command -v zypp)"    ]; then $(SUDO) zypp    install    $1 ; \
	elif [ -x "$(command -v zypper)"  ]; then $(SUDO) zypper  install    $1 ; \
	else \
		printf $(C_RED)"ERROR"$(C_RESET)": Package manager not found. You must manually install: $1" >&2 ; \
	fi
endef
else
define install_prereq
	printf $(C_RED)"ERROR"$(C_RESET)": Unknown platform. You must manually install: $1"
endef
endif





.PHONY:\
prereq # Checks version numbers for all prerequisite tools
prereq: init \
prereq-build \
prereq-tests \
prereq-format \
prereq-lint \
prereq-doc
	@printf $(C_RESET)"\n\n"



.PHONY:\
prereq-build # Checks prerequisite installs to build the library/program
prereq-build:
	$(call check_prereq,\
		(build) compiler: $(CC),\
		$(CC) --version,\
		$(call install_prereq,$(CC)))
	$(call check_prereq,\
		(build) archiver: $(AR),\
		which $(AR),\
		$(call install_prereq,binutils))

.PHONY:\
prereq-tests # Checks prerequisite installs to run the various tests
prereq-tests:
	$(call check_prereq,\
		(tests) Valgrind,\
		valgrind --version,\
		$(call install_prereq,valgrind))

.PHONY:\
prereq-format # Checks prerequisite installs to run the automatic code style formatter
prereq-format:
	$(call check_prereq,\
		(format) indent,\
		which indent,\
		$(call install_prereq,indent))

.PHONY:\
prereq-lint # Checks prerequisite installs to run the linter/static analyzer
prereq-lint:
	$(call check_prereq,\
		(lint) cppcheck,\
		cppcheck --version,\
		$(call install_prereq,cppcheck))
	$(call check_prereq,\
		(lint) splint,\
		splint --help,\
		$(call install_prereq,splint))

.PHONY:\
prereq-doc # Checks prerequisite installs to generate the documentation
prereq-doc:
	$(call check_prereq,\
		(doc) Doxygen,\
		doxygen --version,\
		$(call install_prereq,doxygen))
	$(call check_prereq,\
		(doc) Doxyrest,\
		$(DOXYREST) --version,\
		$(call install_prereq,doxyrest))
	$(call check_prereq,\
		(doc) Lua,\
		lua -v,\
		$(call install_prereq,lua))
	$(call check_prereq,\
		(doc) Python 3.7,\
		python3.7 --version,\
		$(call install_prereq,python@3.7))
	$(call check_prereq,\
		(doc) Python Sphinx doc generator,\
		sphinx-build --version,\
		$(call install_prereq,sphinx))
