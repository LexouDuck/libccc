#! This file holds project-specific rules to run an automatic code style formatter



.PHONY:\
format #! Runs the code style auto-formatter on one or more files given as `ARGS`
format:
	@$(call print_message,"No code style formatter implemented.")



.PHONY:\
format-all #! Runs the code style auto-formatter on one or more files given as `ARGS`
format-all:
	@$(MAKE) format ARGS="$(ARGS)"



.PHONY:\
prereq-format #! Checks prerequisite installs to run the code style auto-formatter
prereq-format:
	@-$(call check_prereq,'(format) indent',\
		which indent,\
		$(call install_prereq,indent))
