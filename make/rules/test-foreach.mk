#! This file holds project-specific rules for a simple standalone testing program



NAME_TEST_FOREACH = libccc-test_foreach
SRCS_TEST_FOREACH = $(TESTDIR)_foreach.c

.PHONY:\
test-foreach #! Builds and runs a simple test program for the 'foreach ()' macro
test-foreach: $(NAME_TEST_FOREACH)
	@ ./$(NAME_TEST_FOREACH) $(ARGS)
	@rm $(NAME_TEST_FOREACH)

$(NAME_TEST_FOREACH): build-$(MODE) $(SRCS_TEST_FOREACH)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_DEBUG) \
		-I$(HDRDIR) $(SRCS_TEST_FOREACH) \
		-L./ -lccc
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
