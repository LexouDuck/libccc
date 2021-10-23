# This file holds rules to run test executables



.PHONY:\
test # Builds and runs the test suite program with the given 'ARGS'
test: $(NAME_TEST)
	@./$(NAME_TEST) $(ARGS)

.PHONY:\
test-log # Builds and runs the test suite program with the given 'ARGS', logging all results to files
test-log: $(NAME_TEST)
	@mkdir -p $(LOGDIR)
	@./$(NAME_TEST) $(ARGS) -var --test-all >> $(LOGDIR)libccc_test.log



.PHONY:\
test-predef # Gets the list of all predefined macros for the current compiler/flags/env/arch
test-predef:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@./$(TEST_DIR)_predef.sh >	$(LOGDIR)env/$(OSMODE)/predef_$(CC).c
	@printf " => File saved to: $(LOGDIR)env/$(OSMODE)/predef_$(CC).c""\n"

.PHONY:\
test-errno # Gets the list of all 'errno' values for the current compiler/flags/env/arch
test-errno:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@./$(TEST_DIR)_errno.sh >	$(LOGDIR)env/$(OSMODE)/errno_$(CC).c
	@printf " => File saved to: $(LOGDIR)env/$(OSMODE)/errno_$(CC).c""\n"
