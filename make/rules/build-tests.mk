#! This file holds C-specific rules to build a test suite program



#! List of all C header code files
HDRS_TEST := $(shell cat $(HDRSFILE_TEST))

#! List of all C source code files
SRCS_TEST := $(shell cat $(SRCSFILE_TEST))

#! Derive list of compiled object files (.o) from list of srcs
OBJS_TEST := $(SRCS_TEST:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS_TEST := $(OBJS_TEST:.o=.d)



.PHONY:\
lists-tests # Create/update the list of source/header files for the test suite program
lists-tests:
	@find $(TEST_DIR) -name "*.h" | sort | sed "s|//|/|g" | grep -v "/_" > $(HDRSFILE_TEST)
	@find $(TEST_DIR) -name "*.c" | sort | sed "s|//|/|g" | grep -v "/_" > $(SRCSFILE_TEST)



#! Compiles object files from source files
$(OBJDIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c $(HDRS_TEST)
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(TEST_INCLUDES) -c $<
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



#! Builds the testing/CI program
$(NAME_TEST): $(NAME_STATIC) $(NAME_DYNAMIC) $(OBJS_TEST)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(TEST_INCLUDES) $(OBJS_TEST) $(TEST_LDLIBS)
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(DEPS_TEST)
