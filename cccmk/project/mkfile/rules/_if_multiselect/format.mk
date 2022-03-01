#! This file holds project-specific rules to run an automatic code style formatter



.PHONY:\
format #! Runs the code style auto-formatter on one or more files given as `ARGS`
format:
	@$(call print_warning,"No code style formatter implemented.")



.PHONY:\
format-all #! Runs the code style auto-formatter on all source code files
format-all:
	@$(MAKE) format ARGS="$(SRCS)"



.PHONY:\
prereq-format #! Checks prerequisite installs to run the automatic code style formatter
prereq-format:
	@-$(call check_prereq,'(format) indent',\
		which indent,\
		$(call install_prereq,indent))
