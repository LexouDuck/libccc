#! This file holds utility functions to check whether prerequisite programs are correctly installed/available



#! The shell command to check whether a certain version number is good enough for the given "target version"
#	@param 1	The version number to be checked (left-hand-side)
#	@param 2	The target version to compare to (right-hand-side) - can have special characters such as `^`
check_version = \
	[ "`$(MKFILES_DIR)utils/compare_version.sh $(1) $(2)`" = "lt" ]



#! The shell command to check whether or not a prerequite program/library is installed
#	@param 1	The name of the prerequisite to check (can be full name with spaces)
#	@param 2	The shell command to check whether it exists (exit code 0 means it is ok)
#	@param 3	The shell command to install the prerequisite (will only run if command $(2) fails)
#	@param 4	(optional) The target version number for this prerequisite tool to install
check_prereq = \
	$(call print_message,"\n\n|=> Checking prerequisite: $(1)") ; \
	echo "$$ $(2)\n" ; \
	valid=false ; \
	$(2) && valid=true ; \
	if $$valid && ! [ -z "$(4)" ] ; \
	then \
		version="`$(2) 2>&1 | awk '{ if (match($$0, /[0-9]+(\.[0-9]+)+?/)) { print substr($$0, RSTART, RLENGTH); exit 0; } }' `" ; \
		$(call check_version,$$version,$(4)) \
		&& valid=false \
		&& $(call print_warning,"You have installed version '$$version' but this project requires version '$(4)'") ; \
	fi ; \
	$$valid || \
	{ \
		$(call print_warning,"$(1) is not installed") ; \
		$(call print_message,"Installing prereq...") ; \
		$(3) ; \
		{ $(2) ; } || $(call print_error,"Installation did not work: command '$(2)' exited with status $$?") ; \
	} \



#! The shell command to install a prerequisite program/library (uses the appropriate OS-specific package manager)
#	@param 1	The name of the program/library/package to install
install_prereq = \
	if   [ -x "`command -v apk     `" ]; then $(SUDO) apk add --no-cache $(1) ; \
	elif [ -x "`command -v apt-get `" ]; then $(SUDO) apt-get install    $(1) ; \
	elif [ -x "`command -v brew    `" ]; then $(SUDO) brew    install    $(1) ; \
	elif [ -x "`command -v choco   `" ]; then $(SUDO) choco   install    $(1) ; \
	elif [ -x "`command -v pacman  `" ]; then $(SUDO) pacman  -S         $(1) ; \
	elif [ -x "`command -v yum     `" ]; then $(SUDO) yum     install    $(1) ; \
	elif [ -x "`command -v dnf     `" ]; then $(SUDO) dnf     install    $(1) ; \
	elif [ -x "`command -v zypp    `" ]; then $(SUDO) zypp    install    $(1) ; \
	elif [ -x "`command -v zypper  `" ]; then $(SUDO) zypper  install    $(1) ; \
	else \
		$(call print_error,"No package manager program was found. You must manually install: $(1)") >&2 ; \
	fi
