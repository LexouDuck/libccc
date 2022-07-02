#! This file holds project-specific rules for a simple standalone testing programs



TESTDIR_STANDALONE = $(TESTDIR)standalone/



NAME_TEST_HELLOWORLD = libccc_test-helloworld
SRCS_TEST_HELLOWORLD = $(TESTDIR_STANDALONE)helloworld.c

.PHONY:\
test-helloworld #! Builds and runs a simple 'Hello World!' test program
test-helloworld: $(NAME_TEST_HELLOWORLD)
	@$(call run,$(NAME_TEST_HELLOWORLD)) $(ARGS)
	@rm $(NAME_TEST_HELLOWORLD)

$(NAME_TEST_HELLOWORLD): all $(SRCS_TEST_HELLOWORLD)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_BUILDMODE_debug) \
		-I$(HDRDIR) $(SRCS_TEST_HELLOWORLD) \
		$(TEST_LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



NAME_TEST_FOREACH = libccc_test-foreach
SRCS_TEST_FOREACH = $(TESTDIR_STANDALONE)foreach.c

.PHONY:\
test-foreach #! Builds and runs a simple test program for the 'foreach ()' macro
test-foreach: $(NAME_TEST_FOREACH)
	@$(call run,$(NAME_TEST_FOREACH)) $(ARGS)
	@rm $(NAME_TEST_FOREACH)

$(NAME_TEST_FOREACH): all $(SRCS_TEST_FOREACH)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_BUILDMODE_debug) \
		-I$(HDRDIR) $(SRCS_TEST_FOREACH) \
		$(TEST_LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



NAME_TEST_KVT = libccc_test-kvt
SRCS_TEST_KVT = $(TESTDIR_STANDALONE)kvt.c

.PHONY:\
test-kvt #! Builds and runs a KVT (json,toml,yaml,xml) print/parse test program
test-kvt: $(NAME_TEST_KVT)
	@$(call run,$(NAME_TEST_KVT)) $(ARGS)
	@rm $(NAME_TEST_KVT)

$(NAME_TEST_KVT): all $(SRCS_TEST_KVT)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_BUILDMODE_debug) \
		-I$(HDRDIR) $(SRCS_TEST_KVT) \
		$(TEST_LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



NAME_TEST_UNDEFINED = libccc_test-undefined
SRCS_TEST_UNDEFINED = $(TESTDIR_STANDALONE)undefined.c

.PHONY:\
test-undefined #! Builds and runs a simple test program to check if headers expose any undefined functions
test-undefined: $(NAME_TEST_UNDEFINED)
	@$(call run,$(NAME_TEST_UNDEFINED)) $(ARGS)
	@rm $(NAME_TEST_UNDEFINED)

$(NAME_TEST_UNDEFINED): all $(SRCS_TEST_UNDEFINED)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(TEST_CFLAGS) $(CFLAGS_BUILDMODE_debug) -Wno-unused-variable \
		-I$(HDRDIR) $(SRCS_TEST_UNDEFINED) \
		$(TEST_LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"

TEST_UNDEFINED_INCLUDES = $(HDRS:$(HDRDIR)libccc/monad/%.h=$(HDRDIR)libccc/monad/%.h)

.PHONY:\
$(SRCS_TEST_UNDEFINED) #! Generates a .c file which calls every function declared from every header in the project
$(SRCS_TEST_UNDEFINED): HDRS := $(filter-out libccc/monad/convert.h,$(HDRS))
$(SRCS_TEST_UNDEFINED): $(TEST_UNDEFINED_INCLUDES)
	@printf "Generating testing program: "$@" -> "
	@$(MAKE) doc-help \
		DOCHELP_AWK_DECL_SPACING="" \
		DOCHELP_AWK_SYNTAXCOLORS="" \
	| grep ');' \
	| grep -v '[usqfUSQF]128' \
	| awk '\
	BEGIN {\
		print "// This is a generated source file: see $(MKFILES_DIR)rules/test-simple.mk for more info";\
		print "";\
		$(foreach i,$(TEST_UNDEFINED_INCLUDES:$(HDRDIR)lib%=lib%),print "#include <$(i)>";)\
		print "#define T_TYPE	t_sint";\
		print "#define T_NAME	int";\
		print "#define T_NULL	0";\
		print "#include <libccc/monad/array.h>";\
		print "#define T_TYPE	t_float";\
		print "#define T_NAME	float";\
		print "#define T_NULL	0.0";\
		print "#include <libccc/monad/array.h>";\
		print "";\
		print "int main()";\
		print "{";\
	}\
	{\
		gsub(/<T>/, "(any)");\
		gsub(/\<T\>/, "void*");\
		split($$0, line, "\t");\
		if (line[1] == "void")\
			 { assign = sprintf("\t%-32s", " "); }\
		else { assign = sprintf("\t%-20s var_%04i = ", line[1], NR); }\
		funcname = sprintf("%-30s", line[2]);\
		decl = $$0;\
		decl = substr(decl, index($$0, "(") + 1);\
		decl = substr(decl, 0, length(decl) - 2);\
		if (decl == "void")\
		{\
			args = "";\
		}\
		else\
		{\
			split(decl, arg_array, /,[ \t]*/);\
			skip = 0;\
			args = "";\
			for (i in arg_array)\
			{\
				if (skip)\
				{\
					if (arg_array[i] ~ /\)/) { skip = 0; }\
					continue;\
				}\
				if (arg_array[i] == "...")					{ value = ""; }\
				else if (arg_array[i] ~ /\(\*[a-z_]+\)/)	{ value = "NULL"; skip = 1; }\
				else if (arg_array[i] ~ /\*/)				{ value = "NULL"; }\
				else if (arg_array[i] ~ /^s_/)\
				{ value = "(" substr(arg_array[i], 1, index(arg_array[i], " ") - 1) "){0}"; }\
				else\
				{ value = "0"; }\
				if (length(args) > 0 && length(value) > 0)\
				{ args = args ", "; }\
				args = args value;\
			}\
		}\
		args = "(" args ");";\
		print assign funcname args;\
	}\
	END { print "}"; }\
	' $$i > $(SRCS_TEST_UNDEFINED)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
