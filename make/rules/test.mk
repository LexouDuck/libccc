#! This file holds project-specific rules to run test executables



.PHONY:\
test # Builds and runs the test suite program with the given 'ARGS'
test: $(NAME_TEST)
	@./$(NAME_TEST) $(ARGS)



.PHONY:\
test-log # Builds and runs the test suite program with the given 'ARGS', logging all results to files
test-log: $(NAME_TEST)
	@mkdir -p $(LOGDIR)
	@./$(NAME_TEST) $(ARGS) -var --test-all >> $(LOGDIR)libccc_test.log

