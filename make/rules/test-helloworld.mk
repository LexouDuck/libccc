#! This file holds project-specific rules for a simple standalone testing program



NAME_TEST_HELLOWORLD = libccc-test_helloworld
SRCS_TEST_HELLOWORLD = $(TEST_DIR)_helloworld.c

.PHONY:\
test-helloworld #! Builds and runs a simple 'Hello World!' test program
test-helloworld: $(NAME_TEST_HELLOWORLD)
	@ ./$(NAME_TEST_HELLOWORLD) $(ARGS)
	@rm $(NAME_TEST_HELLOWORLD)

$(NAME_TEST_HELLOWORLD): $(NAME_STATIC) $(NAME_DYNAMIC) $(SRCS_TEST_HELLOWORLD)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) \
		-I$(HDRDIR) $(SRCS_TEST_HELLOWORLD) \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"
