#! This file holds C-specific rules to build a test suite program



#! Path of the file which stores the list of header code files
TEST_HDRSFILE = make/lists/hdrs-test.txt
#! The shell command which generates the list of header code files
make_TEST_HDRSFILE = find $(TEST_DIR) -name "*.h" | sort | sed "s|//|/|g" | grep -v "/_" > $(TEST_HDRSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(TEST_HDRSFILE) ; echo $$?),1)
$(warning NOTE: header code list file '$(TEST_HDRSFILE)' doesn't exist - creating now...)
$(shell $(call make_TEST_HDRSFILE))
endif
#! List of all C header code files
TEST_HDRS := $(shell cat $(TEST_HDRSFILE))



#! Path of the file which stores the list of source code files
TEST_SRCSFILE = make/lists/srcs-test.txt
#! The shell command which generates the list of source code files
make_TEST_SRCSFILE = find $(TEST_DIR) -name "*.c" | sort | sed "s|//|/|g" | grep -v "/_" > $(TEST_SRCSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(TEST_SRCSFILE) ; echo $$?),1)
$(warning NOTE: source code list file '$(TEST_SRCSFILE)' doesn't exist - creating now...)
$(shell $(call make_TEST_SRCSFILE))
endif
#! List of all C source code files
TEST_SRCS := $(shell cat $(TEST_SRCSFILE))



#! Derive list of compiled object files (.o) from list of srcs
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
TEST_DEPS := $(TEST_OBJS:.o=.d)



.PHONY:\
lists-tests # Create/update the list of source/header files for the test suite program
lists-tests:
	@$(call make_TEST_HDRSFILE)
	@$(call make_TEST_SRCSFILE)



#! Compiles object files from source files
$(OBJDIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c $(TEST_HDRS)
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(TEST_INCLUDES) -c $<
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



#! Builds the testing/CI program
$(TEST_NAME): $(NAME_STATIC) $(NAME_DYNAMIC) $(TEST_OBJS)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(TEST_INCLUDES) $(TEST_OBJS) $(TEST_LDLIBS)
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(TEST_DEPS)
