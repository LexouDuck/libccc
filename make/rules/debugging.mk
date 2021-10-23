# This file holds C-specific rules to debug the code in various ways

# The list of output files for 'debug-macros' - essentially just the list of sources, but in the ./obj folder
SRCS_PREPROCESSED = ${SRCS:%.c=$(OBJDIR)%.c}



# This rule runs the preprocessing step for each .c file, and outputs to obj
$(OBJDIR)%.c: $(SRCDIR)%.c
	@printf "Preprocessing file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -E $<
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

.PHONY:\
debug-macros # Preprocesses all source files and stores them in the obj folder
debug-macros: all $(SRCS_PREPROCESSED)
	@printf "Outputting preprocessed code...\n"



# TODO: rules for debugging linking (symbols dumping, linkpath-dependency-walking)
# TODO: rules for leak-checking (valgrind, dr.memory, etc)
