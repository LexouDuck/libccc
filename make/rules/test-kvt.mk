#! This file holds project-specific rules for a simple standalone testing program



NAME_TEST_KVT = libccc-test_kvt
SRCS_TEST_KVT = $(TEST_DIR)_kvt.c

.PHONY:\
test-kvt #! Builds and runs a KVT (json,toml,yaml,xml) print/parse test program
test-kvt: $(NAME_TEST_KVT)
	@ ./$(NAME_TEST_KVT) $(ARGS)
	@rm $(NAME_TEST_KVT)

$(NAME_TEST_KVT): $(NAME_STATIC) $(NAME_DYNAMIC) $(SRCS_TEST_KVT)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) \
		-I$(HDRDIR) $(SRCS_TEST_KVT) \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"