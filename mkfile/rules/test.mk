#! This file holds project-specific rules to run test executables



#! Shell command used to launch the test program
ifdef __EMSCRIPTEN__
run_test = node $(NAME_TEST)
else
run_test = ./$(NAME_TEST)
endif

#! The directory in which to store text logs of the test suite output
TEST_LOGDIR = $(LOGDIR)test/



.PHONY:\
test #! Runs the test suite program, with the given 'ARGS'
test: $(NAME_TEST)
	@$(call run_test) $(ARGS)



.PHONY:\
test-logs #! Builds and runs the test suite program with the given 'ARGS', logging all results to files
test-logs: $(NAME_TEST)
	@mkdir -p $(TEST_LOGDIR)$(OSMODE)/
	@$(call run_test) -var --test-all $(ARGS) >> $(TEST_LOGDIR)$(OSMODE)/$(NAME_TEST).txt

.PHONY:\
clean-test-logs #! Deletes any test suite logs
clean-test-logs:
	@rm -rf $(TEST_LOGDIR)



.PHONY:\
test-memory #! Builds and runs the test suite program with the given 'ARGS', checking for memory leaks
test-memory: $(NAME_TEST)
	@mkdir -p $(LOGDIR)leaks/
ifeq ($(OSMODE),other)
	@$(call print_error,"Unsupported platform: requires manual configuration")
else ifeq ($(OSMODE),emscripten)
	@$(call print_error,"Unsupported platform: emscripten test-memory not implemented")
else ifeq ($(OSMODE),win32)
	@$(call print_error,"Windows 32-bit platform: requires manual configuration")
else ifeq ($(OSMODE),win64)
	@$(call print_error,"Windows 64-bit platform: requires manual configuration")
else ifeq ($(OSMODE),macos)
	@$(call run_test) $(ARGS) >> $(LOGDIR)libccc_test.log
	@$(SUDO) ln -sf "`xcode-select -p`/usr/lib/libLeaksAtExit.dylib" "/usr/local/lib"
	@leaks --fullContent -atExit -- $(call run_test) $(ARGS) > $(LOGDIR)leaks/xcode_$(NAME_TEST).txt
	@$(SUDO) rm "/usr/local/lib/libLeaksAtExit.dylib"
else ifeq ($(OSMODE),linux)
	@valgrind \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=definite \
		--track-origins=yes \
		--verbose \
		--log-file=$(LOGDIR)leaks/valgrind_$(NAME_TEST).txt \
		$(call run_test) $(ARGS)
endif



.PHONY:\
prereq-tests #! Checks prerequisite installs to run the various tests
prereq-tests:
ifeq ($(OSMODE),other)
	@$(call print_warning,"'other' platform: memory leak checking tool must be configured manually")
else ifeq ($(OSMODE),win32)
	@-# TODO drmemory.exe ?
else ifeq ($(OSMODE),win64)
	@-# TODO drmemory.exe ?
else ifeq ($(OSMODE),macos)
	@-$(call check_prereq,'(tests) Xcode leaks checker',\
		which leaks,\
		$(call install_prereq,leaks))
else ifeq ($(OSMODE),linux)
	@-$(call check_prereq,'(tests) Valgrind',\
		valgrind --version,\
		$(call install_prereq,valgrind))
else
	@$(call print_warning,"Unsupported platform: memory leak checking tool must be configured manually")
endif
