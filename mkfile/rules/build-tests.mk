#! This file holds C-specific rules to build a test suite program



#! Derive list of compiled object files (.o) from list of srcs
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
TEST_DEPS := $(TEST_OBJS:.o=.d)

# here we add linked library flags for each package
TEST_LDLIBS := $(TEST_LDLIBS) \
	$(foreach i,$(PACKAGES_LINK),$($(i)))

# here we add include header folders for each package
TEST_INCLUDES := $(TEST_INCLUDES) \
	$(foreach i,$(PACKAGES_INCLUDE),-I$($(i)))



.PHONY:\
build-tests-debug #! Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-tests-debug: MODE = debug
build-tests-debug: TEST_CFLAGS += $(TEST_CFLAGS_DEBUG)
build-tests-debug: build-debug $(NAME_TEST)

.PHONY:\
build-tests-release #! Builds the library, in 'release' mode (with optimization flags)
build-tests-release: MODE = release
build-tests-release: TEST_CFLAGS += $(TEST_CFLAGS_RELEASE)
build-tests-release: build-release $(NAME_TEST)



#! Compiles object files from source files
$(OBJDIR)$(TESTDIR)%.o: $(TESTDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) -MMD $(TEST_INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Builds the testing/CI program
$(NAME_TEST): $(NAME_STATIC) $(NAME_DYNAMIC) $(TEST_OBJS)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(TEST_LDFLAGS) $(TEST_OBJS) $(TEST_LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(TEST_DEPS)



.PHONY:\
clean-tests #! Deletes all intermediary tests-related files
clean-tests: \
clean-tests-obj \
clean-tests-dep \
clean-tests-bin \

.PHONY:\
clean-tests-obj #! Deletes all .o tests object files
clean-tests-obj:
	@$(call print_message,"Deleting all tests .o files...")
	@rm -f $(TEST_OBJS)

.PHONY:\
clean-tests-dep #! Deletes all .d tests dependency files
clean-tests-dep:
	@$(call print_message,"Deleting all tests .d files...")
	@rm -f $(TEST_DEPS)

.PHONY:\
clean-tests-bin #! Deletes all tests binaries
clean-tests-bin:
	@$(call print_message,"Deleting test program: "$(NAME_TEST)"")
	@rm -f $(NAME_TEST)
