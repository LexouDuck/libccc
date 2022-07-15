#! This file holds project-specific rules to run test executables



.PHONY:\
test #! Runs the test suite program, with the given 'ARGS'
test: $(NAME_TEST)
	@$(call run,$(NAME_TEST)) $(ARGS)



.PHONY:\
test-logs #! Builds and runs the test suite program with the given 'ARGS', logging all results to files
test-logs: $(NAME_TEST)
	@mkdir -p $(LOGPATH)/
	@$(call run,$(NAME_TEST)) -var --test-all $(ARGS) >> $(LOGPATH)/$(NAME_TEST).txt

.PHONY:\
clean-test-logs #! Deletes any test suite logs
clean-test-logs:
	@rm -f $(LOGPATH)/$(NAME_TEST).txt



.PHONY:\
test-memory #! Builds and runs the test suite program with the given 'ARGS', checking for memory leaks
test-memory: $(NAME_TEST)
	@mkdir -p $(LOGDIR)leaks/
ifeq ($(OSMODE),other)
	@$(call print_error,"Unsupported platform: requires manual configuration")
endif
ifeq ($(OSMODE),emscripten)
	@$(call print_error,"Unsupported platform: emscripten test-memory not implemented")
endif
ifeq ($(OSMODE),windows)
	@$(call print_error,"Windows platform: requires manual configuration")
endif
ifeq ($(OSMODE),macos)
	@$(call run,$(NAME_TEST)) $(ARGS) >> $(LOGDIR)libccc_test.log
	@$(SUDO) ln -sf "`xcode-select -p`/usr/lib/libLeaksAtExit.dylib" "/usr/local/lib"
	@leaks --fullContent -atExit -- $(call run,$(NAME_TEST)) $(ARGS) > $(LOGDIR)leaks/xcode_$(NAME_TEST).txt
	@$(SUDO) rm "/usr/local/lib/libLeaksAtExit.dylib"
endif
ifeq ($(OSMODE),linux)
	@valgrind \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=definite \
		--track-origins=yes \
		--verbose \
		--log-file=$(LOGDIR)leaks/valgrind_$(NAME_TEST).txt \
		$(call run,$(NAME_TEST)) $(ARGS)
endif



.PHONY:\
prereq-tests #! Checks prerequisite installs to run the various tests
prereq-tests:
ifeq ($(OSMODE),windows)
	@-# TODO drmemory.exe ?
endif
ifeq ($(OSMODE),macos)
	@-$(call check_prereq,'(tests) Xcode leaks checker',\
		which leaks,\
		$(call install_prereq,leaks))
endif
ifeq ($(OSMODE),linux)
	@-$(call check_prereq,'(tests) Valgrind',\
		valgrind --version,\
		$(call install_prereq,valgrind))
endif
ifeq ($(OSMODE),other)
	@$(call print_error,"Unsupported platform: memory leak checking tool must be configured manually")
endif
