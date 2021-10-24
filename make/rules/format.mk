# This file holds rules to run the automatic code style formatter



.PHONY:\
format # Runs the code style auto-formatter on one or more files given as `ARGS`
format:
	@printf $(C_YELLOW)"WARNING"$(C_RESET)": No code style formatter implemented.""\n"



.PHONY:\
format-all # Runs the code style auto-formatter on one or more files given as `ARGS`
format-all:
	@$(MAKE) format ARGS="$(ARGS)"
