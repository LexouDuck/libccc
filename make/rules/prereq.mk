#! This file holds project-specific rules to check whether prerequisite programs are correctly installed/available



#! The shell command to check whether or not a prerequite program/library is installed
#	@param 1	The name of the prerequisite to check (can be full name with spaces)
#	@param 2	The shell command to check whether it exists (exit code 0 means it is ok)
#	@param 3	The shell command to install the prerequisite (will only run if command $(2) fails)
check_prereq = \
	$(call print_message,"\n\n|=> Checking prerequisite: $(1)") ; \
	echo "$$ $(2)\n" ; \
	{ $(2) ; } || \
	{ \
		$(call print_warning,"$(1) is not installed") ; \
		$(call print_message,"Installing prereq...") ; \
		$(3) ; \
	}



#! The shell command to install a prerequisite program/library (uses the appropriate OS-specific package manager)
#	@param 1	The name of the program/library/package to install
install_prereq = \
	$(call print_error,"Unknown platform. You must manually install: $(1)") \

ifeq ($(OS),Windows_NT)
install_prereq = \
	$(call print_error,"Windows platform detected. You must manually install: $(1)") \

else ifeq ($(UNAME_S),Darwin)
install_prereq = \
	brew install $(1) \

else ifeq ($(UNAME_S),Linux)
install_prereq = \
	if   [ -x "`command -v apk     `" ]; then $(SUDO) apk add --no-cache $(1) ; \
	elif [ -x "`command -v apt-get `" ]; then $(SUDO) apt-get install    $(1) ; \
	elif [ -x "`command -v yum     `" ]; then $(SUDO) yum     install    $(1) ; \
	elif [ -x "`command -v pacman  `" ]; then $(SUDO) pacman  -S         $(1) ; \
	elif [ -x "`command -v dnf     `" ]; then $(SUDO) dnf     install    $(1) ; \
	elif [ -x "`command -v zypp    `" ]; then $(SUDO) zypp    install    $(1) ; \
	elif [ -x "`command -v zypper  `" ]; then $(SUDO) zypper  install    $(1) ; \
	else \
		$(call print_error,"Package manager not found. You must manually install: $(1)") >&2 ; \
	fi \

endif





.PHONY:\
prereq #! Checks version numbers for all prerequisite tools
prereq: init \
prereq-build \
prereq-tests \
prereq-coverage \
prereq-format \
prereq-lint \
prereq-doc
	@printf $(IO_RESET)"\n\n"



.PHONY:\
prereq-build #! Checks prerequisite installs to build the library/program
prereq-build:
	@-$(call check_prereq,\
		(build) C compiler: $(CC),\
		$(CC) --version,\
		$(call install_prereq,$(CC)))
	@-$(call check_prereq,\
		(build) C archiver: $(AR),\
		which $(AR),\
		$(call install_prereq,binutils))

.PHONY:\
prereq-tests #! Checks prerequisite installs to run the various tests
prereq-tests:
ifeq ($(OSMODE),other)
	@$(call print_warning,"'other' platform: memory leak checking tool must be configured manually")
else ifeq ($(OSMODE),win32)
	@-# TODO drmemory.exe ?
else ifeq ($(OSMODE),win64)
	@-# TODO drmemory.exe ?
else ifeq ($(OSMODE),macos)
	@-$(call check_prereq,\
		(tests) Xcode leaks checker,\
		which leaks,\
		$(call install_prereq,leaks))
else ifeq ($(OSMODE),linux)
	@-$(call check_prereq,\
		(tests) Valgrind,\
		valgrind --version,\
		$(call install_prereq,valgrind))
else
	@$(call print_warning,"Unsupported platform: memory leak checking tool must be configured manually")
endif

.PHONY:\
prereq-coverage #! Checks prerequisite installs to run the automatic code style formatter
prereq-coverage:
	@-$(call check_prereq,\
		(coverage) gcov code-coverage tool,\
		gcov --version,\
		$(call install_prereq,gcov))
	@-$(call check_prereq,\
		(coverage) lcov code-coverage tool,\
		lcov --version && genhtml --version,\
		$(call install_prereq,lcov))

.PHONY:\
prereq-format #! Checks prerequisite installs to run the automatic code style formatter
prereq-format:
	@-$(call check_prereq,\
		(format) indent,\
		which indent,\
		$(call install_prereq,indent))

.PHONY:\
prereq-lint #! Checks prerequisite installs to run the linter/static analyzer
prereq-lint:
	@-$(call check_prereq,\
		(lint) cppcheck,\
		cppcheck --version,\
		$(call install_prereq,cppcheck))
	@-$(call check_prereq,\
		(lint) splint,\
		splint --help version,\
		$(call install_prereq,splint))

.PHONY:\
prereq-doc #! Checks prerequisite installs to generate the documentation
prereq-doc:
	@-$(call check_prereq,\
		(doc) Doxygen,\
		doxygen --version,\
		$(call install_prereq,doxygen))
	@-$(call check_prereq,\
		(doc) Doxyrest,\
		$(DOXYREST) --version,\
		$(call install_prereq,doxyrest))
	@-$(call check_prereq,\
		(doc) Lua,\
		lua -v,\
		$(call install_prereq,lua))
	@-$(call check_prereq,\
		(doc) Sphinx python doc generator,\
		sphinx-build --version,\
		$(call install_prereq,sphinx-doc))
