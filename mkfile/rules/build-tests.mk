#! This file holds C-specific rules to build a test suite program



test_objs = ` cat "$(TEST_OBJSFILE)" | tr '\n' ' ' `

#! Path of the file which stores the list of compiled object files
TEST_OBJSFILE = $(OBJPATH)objs-test.txt

#! Derive list of compiled object files (.o) from list of srcs
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJPATH)%.o)

#! Derive list of dependency files (.d) from list of srcs
TEST_DEPS := $(TEST_OBJS:%.o=%.d)

# here we add dependency library linking flags for each package
TEST_LDLIBS := $(TEST_LDLIBS) \
	$(foreach i,$(PACKAGES), $(PACKAGE_$(i)_LINK))

# here we add include header folders for each package
TEST_INCLUDES := $(TEST_INCLUDES) \
	$(foreach i,$(PACKAGES), -I$(PACKAGE_$(i)_INCLUDE))



.PHONY:\
build-tests-debug #! Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-tests-debug: BUILDMODE = debug
build-tests-debug: \
build-debug \
$(NAME_TEST)

.PHONY:\
build-tests-release #! Builds the library, in 'release' mode (with optimization flags)
build-tests-release: BUILDMODE = release
build-tests-release: \
build-release \
$(NAME_TEST)



#! Generates the list of object files
$(TEST_OBJSFILE): $(TEST_SRCSFILE)
	@mkdir -p $(@D)
	@printf "" > $(TEST_OBJSFILE)
	$(foreach i,$(TEST_OBJS),	@printf "$(i)\n" >> $(TEST_OBJSFILE) $(C_NL))



#! Compiles object files from source files
$(OBJPATH)$(TESTDIR)%.o : $(TESTDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: $@ -> "
	@$(CC) -o $@ $(TEST_CFLAGS) -MMD $(TEST_INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Builds the testing/CI program
$(NAME_TEST): \
$(BINPATH)static/$(NAME_static) \
$(BINPATH)dynamic/$(NAME_dynamic) \
$(TEST_OBJSFILE) \
$(TEST_OBJS)
	@printf "Compiling testing program: $@ -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(TEST_LDFLAGS) $(call test_objs) $(TEST_LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(TEST_DEPS)



.PHONY:\
clean-tests #! Deletes all intermediary tests-related files
clean-tests: \
clean-tests-obj \
clean-tests-dep \
clean-tests-exe \

.PHONY:\
clean-tests-obj #! Deletes all .o tests object files
clean-tests-obj:
	@$(call print_message,"Deleting all tests .o files...")
	$(foreach i,$(TEST_OBJS),	@rm -f "$(i)" $(C_NL))

.PHONY:\
clean-tests-dep #! Deletes all .d tests dependency files
clean-tests-dep:
	@$(call print_message,"Deleting all tests .d files...")
	$(foreach i,$(TEST_DEPS),	@rm -f "$(i)" $(C_NL))

.PHONY:\
clean-tests-exe #! Deletes the built test program in the root project folder
clean-tests-exe:
	@$(call print_message,"Deleting program: $(NAME_TEST)")
	@rm -f $(NAME_TEST)
