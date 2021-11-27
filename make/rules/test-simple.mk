#! This file holds project-specific rules for a simple standalone testing programs



TESTDIR_STANDALONE = $(TESTDIR)standalone/



NAME_TEST_HELLOWORLD = libccc-test_helloworld
SRCS_TEST_HELLOWORLD = $(TESTDIR_STANDALONE)helloworld.c

.PHONY:\
test-helloworld #! Builds and runs a simple 'Hello World!' test program
test-helloworld: $(NAME_TEST_HELLOWORLD)
	@ ./$(NAME_TEST_HELLOWORLD) $(ARGS)
	@rm $(NAME_TEST_HELLOWORLD)

$(NAME_TEST_HELLOWORLD): build-$(MODE) $(SRCS_TEST_HELLOWORLD)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_DEBUG) \
		-I$(HDRDIR) $(SRCS_TEST_HELLOWORLD) \
		-L./ -lccc
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



NAME_TEST_FOREACH = libccc-test_foreach
SRCS_TEST_FOREACH = $(TESTDIR_STANDALONE)foreach.c

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



NAME_TEST_KVT = libccc-test_kvt
SRCS_TEST_KVT = $(TESTDIR_STANDALONE)kvt.c

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
