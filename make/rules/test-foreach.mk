# This file holds rules for a simple standalone testing program



NAME_TEST_FOREACH = libccc-test_foreach
SRCS_TEST_FOREACH = $(TEST_DIR)_foreach.c

.PHONY:\
test-foreach # Builds and runs a simple foreach() macro test program
test-foreach: $(NAME_TEST_FOREACH)
	@ ./$(NAME_TEST_FOREACH) $(ARGS)
	@rm $(NAME_TEST_FOREACH)

$(NAME_TEST_FOREACH): $(NAME_STATIC) $(NAME_DYNAMIC) $(SRCS_TEST_FOREACH)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) \
		-I$(HDRDIR) $(SRCS_TEST_FOREACH) \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"
