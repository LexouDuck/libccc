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
prereq #! Checks all prerequisite tools/programs and their versions
prereq: init \
	prereq-build \
	prereq-tests \
	prereq-coverage \
	prereq-format \
	prereq-lint \
	prereq-doc \
