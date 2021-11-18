#! This file holds project-specific rules to run test executables



.PHONY:\
test #! Builds and runs the test suite program with the given 'ARGS'
test: $(NAME_TEST)
	@./$(NAME_TEST) $(ARGS)



.PHONY:\
test-log #! Builds and runs the test suite program with the given 'ARGS', logging all results to files
test-log: $(NAME_TEST)
	@mkdir -p $(LOGDIR)test/$(OSMODE)/
	@./$(NAME_TEST) $(ARGS) -var --test-all >> $(LOGDIR)test/$(OSMODE)/$(NAME_TEST).txt



.PHONY:\
test-memleaks #! Builds and runs the test suite program with the given 'ARGS', checking for memory leaks
test-memleaks: $(NAME_TEST)
	@mkdir -p $(LOGDIR)leaks/
ifeq ($(OSMODE),other)
	@$(call print_error,"Unsupported platform: requires manual configuration") ; exit 1
else ifeq ($(OSMODE),win32)
	@$(call print_error,"Windows 32-bit platform: requires manual configuration") ; exit 1
else ifeq ($(OSMODE),win64)
	@$(call print_error,"Windows 64-bit platform: requires manual configuration") ; exit 1
else ifeq ($(OSMODE),linux)
	@valgrind \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=definite \
		--track-origins=yes \
		--verbose \
		--log-file=$(LOGDIR)leaks/valgrind_$(NAME_TEST).txt \
		./$(NAME_TEST) $(ARGS)
else ifeq ($(OSMODE),macos)
	@./$(NAME_TEST) $(ARGS) >> $(LOGDIR)libccc_test.log
	@$(SUDO) ln -sf "`xcode-select -p`/usr/lib/libLeaksAtExit.dylib" "/usr/local/lib"
	@leaks --fullContent -atExit -- ./$(NAME_TEST) $(ARGS) > $(LOGDIR)leaks/xcode_$(NAME_TEST).txt
	@$(SUDO) rm "/usr/local/lib/libLeaksAtExit.dylib"
endif
