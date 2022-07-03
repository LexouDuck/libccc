#! This file holds C-specific rules to debug the code in various ways



#! The list of output files for 'debug-macros' - essentially just the list of sources, but in the ./obj folder
SRCS_PREPROCESSED = $(ARGS:%.c=$(OBJDIR)%.c)

#! This rule runs the preprocessing step for each .c file, and outputs to obj
$(OBJDIR)%.c: %.c
	@mkdir -p $(@D)
	@printf "Preprocessing file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -E $< $(INCLUDES)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"

.PHONY:\
debug-macros #! Preprocesses all source files and stores them in the obj folder (uses ARGS, or SRCS if no ARGS given)
debug-macros:
ifeq ($(ARGS),)
	@$(eval ARGS := $(SRCS))
endif
	@$(MAKE) $(SRCS_PREPROCESSED)
	@$(call print_success,"All source files have been preprocessed (in $(OBJDIR)).")



.PHONY:\
debug-include #! Outputs the list of header include paths searched by the current compiler
debug-include:
ifeq ($(strip $(CC)),)
	@$(call print_error,"This rule expects the CC compiler variable to be defined")
else
	@echo | $(CC) -E -Wp,-v -
endif



.PHONY:\
debug-symbols #! Outputs the list of symbols found inside the given `ARGS` binary/ies
debug-symbols:
ifeq ($(ARGS),)
	@$(call print_error,"This rule expects one or more binary files given as arguments (ARGS=...)")
else
	@nm -a $(ARGS)
endif
	


.PHONY:\
debug-linking #! Outputs the list of linking paths to find dynamic libraries for the given `ARGS`
debug-linking:
ifeq ($(ARGS),)
	@$(call print_error,"This rule expects one or more binary files given as arguments (ARGS=...)")
endif
ifeq ($(OSMODE),windows)
	@objdump -p $(ARGS)
endif
ifeq ($(OSMODE),macos)
	@otool -L $(ARGS)
endif
ifeq ($(OSMODE),linux)
	@ldd $(ARGS)
endif
ifeq ($(OSMODE),other)
	@$(call print_error,"Unknown platform, needs manual configuration")
endif



# TODO: rules for leak-checking (valgrind, dr.memory, etc)
