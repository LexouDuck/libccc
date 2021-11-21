#! This file holds project-specific rules for a simple standalone testing program



NAME_TEST_FOREACH = libccc-test_foreach
SRCS_TEST_FOREACH = $(TESTDIR)_foreach.c

.PHONY:\
test-foreach #! Builds and runs a simple test program for the 'foreach ()' macro
test-foreach: $(NAME_TEST_FOREACH)
	@ ./$(NAME_TEST_FOREACH) $(ARGS)
	@rm $(NAME_TEST_FOREACH)

$(NAME_TEST_FOREACH): $(NAME_STATIC) $(NAME_DYNAMIC) $(SRCS_TEST_FOREACH)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) \
		-I$(HDRDIR) $(SRCS_TEST_FOREACH) \
		-L./ -lccc
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
