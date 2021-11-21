#! This file holds project-specific rules for a simple standalone testing program



NAME_TEST_KVT = libccc-test_kvt
SRCS_TEST_KVT = $(TESTDIR)_kvt.c

.PHONY:\
test-kvt #! Builds and runs a KVT (json,toml,yaml,xml) print/parse test program
test-kvt: $(NAME_TEST_KVT)
	@ ./$(NAME_TEST_KVT) $(ARGS)
	@rm $(NAME_TEST_KVT)

$(NAME_TEST_KVT): build-$(MODE) $(SRCS_TEST_KVT)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_DEBUG) \
		-I$(HDRDIR) $(SRCS_TEST_KVT) \
		-L./ -lccc
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"