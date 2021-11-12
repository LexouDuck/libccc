#! This file holds project-specific rules to run tests on the current machine's setup



.PHONY:\
test-env-predef #! Gets the list of all predefined macros for the current compiler/flags/env/arch
test-env-predef:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@./$(TEST_DIR)_predef.sh >	$(LOGDIR)env/$(OSMODE)/predef_$(CC).c
	@printf " => File saved to: $(LOGDIR)env/$(OSMODE)/predef_$(CC).c""\n"



.PHONY:\
test-env-errno #! Gets the list of all 'errno' values for the current compiler/flags/env/arch
test-env-errno:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@./$(TEST_DIR)_errno.sh >	$(LOGDIR)env/$(OSMODE)/errno_$(CC).c
	@printf " => File saved to: $(LOGDIR)env/$(OSMODE)/errno_$(CC).c""\n"
