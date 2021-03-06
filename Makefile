
#######################################
#          Project variables          #
#######################################

# Output file names
NAME      = libccc
NAME_STATIC  = $(NAME).a
NAME_DYNAMIC = $(NAME)$(DYNAMICLIB_FILE_EXT)
NAME_TEST = libccc_test
# Build names with filetype suffixes
NAME_LIBMODE = _
ifeq ($(LIBMODE),static)
	NAME_LIBMODE = $(NAME_STATIC)
endif
ifeq ($(LIBMODE),dynamic)
	NAME_LIBMODE = $(NAME_DYNAMIC)
endif

VERSION = 0.8

# Directories that this Makefile will use
HDRDIR = ./hdr/
SRCDIR = ./src/
OBJDIR = ./obj/
LIBDIR = ./lib/
DOCDIR = ./doc/
BINDIR = ./bin/
LOGDIR = ./log/
DISTDIR = ./dist/



#######################################
#          Building variables         #
#######################################

# Compiler
CC	= _
CC_WIN32 =   i686-w64-mingw32-gcc
CC_WIN64 = x86_64-w64-mingw32-gcc
CC_LINUX = gcc
CC_MACOS = clang

# Compiler flags
CFLAGS = $(CFLAGS_OS) $(CFLAGS_EXTRA) -MMD -fstrict-aliasing \
	-Werror \
	-Wall \
	-Wextra \
	-Winline \
	-Wpedantic \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wold-style-definition \
	-Wno-format-extra-args \
#	-L/usr/local/lib -ltsan
#	-fsanitize=address
#	-fsanitize=thread
#	-fanalyzer
CFLAGS_DEBUG = -g -ggdb -D DEBUG=1 # -D__NOSTD__=1
CFLAGS_RELEASE = -O3
#	-flto
CFLAGS_OS = _
CFLAGS_OS_WIN   = -D__USE_MINGW_ANSI_STDIO=1
CFLAGS_OS_LINUX = -Wno-unused-result -fPIC -pedantic
CFLAGS_OS_MACOS = -Wno-missing-braces -Wno-language-extension-token
CFLAGS_OS_OTHER = 
ifeq ($(CC),clang)
	CFLAGS_OS_WIN += -Wno-missing-braces
else
	CFLAGS_OS_WIN += -D__USE_MINGW_ANSI_STDIO=1
endif
CFLAGS_EXTRA = 



# Linker flags
LDFLAGS = $(LDFLAGS_OS) $(CFLAGS_EXTRA)
#	-fsanitize=address
#	-Wl,-rpath,bin/linux/dynamic/
#	-Wl,-rpath='$$ORIGIN/'
LDFLAGS_OS = _
LDFLAGS_OS_WIN   = 
LDFLAGS_OS_LINUX = 
LDFLAGS_OS_MACOS = 
LDFLAGS_OS_OTHER = 
ifeq ($(CC),clang)
	LDFLAGS_OS_WIN += -L/lib
else
	LDFLAGS_OS_WIN += -L./ -static-libgcc
endif
LDFLAGS_EXTRA = 



#######################################
#           General variables         #
#######################################

# Set platform-specific variables
ifeq ($(OS),Windows_NT)
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSMODE=win32
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSMODE=win64
	endif
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSMODE=linux
	endif
	ifeq ($(UNAME_S),Darwin)
		OSMODE=macos
	endif
endif



ifeq ($(OSMODE),other)
	CC = $(CC_OTHER)
	CFLAGS_OS = $(CFLAGS_OS_OTHER)
	LDFLAGS_OS = $(LDFLAGS_OS_OTHER)
	DYNAMICLIB_FILE_EXT=
else ifeq ($(OSMODE),win32)
	CC = $(CC_WIN32)
	CFLAGS_OS = $(CFLAGS_OS_WIN)
	LDFLAGS_OS = $(LDFLAGS_OS_WIN)
	DYNAMICLIB_FILE_EXT=.dll
else ifeq ($(OSMODE),win64)
	CC = $(CC_WIN64)
	CFLAGS_OS = $(CFLAGS_OS_WIN)
	LDFLAGS_OS = $(LDFLAGS_OS_WIN)
	DYNAMICLIB_FILE_EXT=.dll
else ifeq ($(OSMODE),linux)
	CC = $(CC_LINUX)
	CFLAGS_OS = $(CFLAGS_OS_LINUX)
	LDFLAGS_OS = $(LDFLAGS_OS_LINUX)
	DYNAMICLIB_FILE_EXT=.so
else ifeq ($(OSMODE),macos)
	CC = $(CC_MACOS)
	CFLAGS_OS = $(CFLAGS_OS_MACOS)
	LDFLAGS_OS = $(LDFLAGS_OS_MACOS)
	DYNAMICLIB_FILE_EXT=.dylib
endif



# Define colors for terminal output
C_RESET  = "\e[0m"
C_RED    = "\e[31m"
C_GREEN  = "\e[32m"
C_YELLOW = "\e[33m"



#######################################
#          Project variables          #
#######################################

# List of all source code files
SRCS = error.c \
	bool/bool_to_str.c		\
	bool/bool_from_str.c	\
	int/int_to_str.c		\
	int/int_to_strhex.c		\
	int/int_to_stroct.c		\
	int/int_to_strbin.c		\
	int/int_to_strbase.c	\
	int/int_from_str.c		\
	int/int_from_strdec.c	\
	int/int_from_strhex.c	\
	int/int_from_stroct.c	\
	int/int_from_strbin.c	\
	int/int_from_strbase.c	\
	fixed/fixed.c			\
	fixed/fixed_to_str.c	\
	fixed/fixed_from_str.c	\
	float/float.c			\
	float/float_to_str.c	\
	float/float_from_str.c	\
	memory/allocate.c	\
	memory/new.c		\
	memory/delete.c		\
	memory/set.c		\
	memory/copy.c		\
	memory/duplicate.c	\
	memory/move.c		\
	memory/merge.c		\
	memory/compare.c	\
	memory/find.c		\
	memory/swap.c		\
	memory/replace.c	\
	memory/bits.c		\
	pointer/int_from_str.c	\
	pointer/size_to_str.c	\
	pointer/ptr_to_str.c	\
	pointerarray/new.c		\
	pointerarray/length.c	\
	string/new.c		\
	string/set.c		\
	string/clear.c		\
	string/delete.c		\
	string/duplicate.c	\
	string/copy.c		\
	string/concat.c		\
	string/length.c		\
	string/compare.c	\
	string/equals.c		\
	string/has.c		\
	string/count.c		\
	string/find.c		\
	string/find_r.c		\
	string/find_n.c		\
	string/remove.c		\
	string/trim.c		\
	string/pad.c		\
	string/reverse.c	\
	string/merge.c		\
	string/insert.c		\
	string/sub.c		\
	string/format.c		\
	string/iterate.c	\
	string/map.c		\
	string/replace.c	\
	string/print.c		\
	string/parse.c		\
	stringarray/split_char.c	\
	stringarray/split_charset.c	\
	stringarray/split_str.c		\
	stringarray/divide.c		\
	stringarray/new.c		\
	stringarray/delete.c	\
	stringarray/length.c	\
	stringarray/count.c		\
	stringarray/add.c		\
	stringarray/sub.c		\
	stringarray/join.c		\
	stringarray/merge.c		\
	stringarray/map.c		\
	stringarray/fold.c		\
	stringarray/pad.c		\
	color/argb_get.c	\
	color/argb_set.c	\
	color/argb_to.c		\
	color/convert.c		\
	color/nearest.c		\
	color/diff.c		\
	text/ascii/isalpha.c		\
	text/ascii/isdigit.c		\
	text/ascii/isprint.c		\
	text/ascii/incharset.c		\
	text/ascii/to.c				\
	text/unicode/isalpha.c		\
	text/unicode/isdigit.c		\
	text/unicode/isprint.c		\
	text/unicode/incharset.c	\
	text/unicode/toupper.c		\
	text/unicode/tolower.c		\
	text/unicode/utf8.c			\
	text/unicode/utf16.c		\
	text/unicode/utfbom.c		\
	text/unicode/parse.c		\
	sys/io/fd.c			\
	sys/io/color.c		\
	sys/io/open.c		\
	sys/io/close.c		\
	sys/io/chmod.c		\
	sys/io/read.c		\
	sys/io/readline.c	\
	sys/io/write.c		\
	sys/io/output.c		\
	sys/time/time.c		\
	sys/time/date.c		\
	sys/time/print.c	\
	sys/time/parse.c	\
	sys/time/utils.c	\
	sys/time/strings.c	\
	sys/logger/core.c	\
	sys/logger/util.c	\
	sys/logger/init.c	\
	sys/logger/log.c	\
	random/prng.c	\
	random/csprng.c	\
	math/int/comparison.c	\
	math/int/operators.c	\
	math/fixed/comparison.c	\
	math/fixed/operators.c	\
	math/fixed/rounding.c	\
	math/float/comparison.c	\
	math/float/operators.c	\
	math/float/rounding.c	\
	math/float/pow.c		\
	math/float/root.c		\
	math/float/exp.c		\
	math/float/log.c		\
	math/float/trig.c		\
	math/float/trig_h.c		\
	math/algebra/calculus.c				\
	math/algebra/vector/new.c			\
	math/algebra/vector/equals.c		\
	math/algebra/vector/scale.c			\
	math/algebra/vector/invert.c		\
	math/algebra/vector/norm.c			\
	math/algebra/vector/normalize.c		\
	math/algebra/vector/add.c			\
	math/algebra/vector/dot.c			\
	math/algebra/vector/cross.c			\
	math/algebra/matrix/new.c			\
	math/algebra/matrix/equals.c		\
	math/algebra/matrix/apply.c			\
	math/algebra/matrix/determinant.c	\
	math/algebra/matrix/inverse.c		\
	math/algebra/matrix/transpose.c		\
	math/algebra/matrix/multiply.c		\
	math/complex/new.c		\
	math/complex/equals.c	\
	math/complex/abs.c		\
	math/complex/conj.c		\
	math/complex/add.c		\
	math/complex/sub.c		\
	math/complex/mul.c		\
	math/complex/div.c		\
	math/stat/int.c		\
	math/stat/float.c	\
	monad/array/new.c		\
	monad/array/create.c	\
	monad/array/delete.c	\
	monad/array/duplicate.c	\
	monad/array/get.c		\
	monad/array/set.c		\
	monad/array/copy.c		\
	monad/array/sub.c		\
	monad/array/append.c	\
	monad/array/prepend.c	\
	monad/array/insert.c	\
	monad/array/remove.c	\
	monad/array/removeall.c	\
	monad/array/removeat.c	\
	monad/array/replace.c	\
	monad/array/find.c		\
	monad/array/count.c		\
	monad/array/contains.c	\
	monad/array/has.c		\
	monad/array/equals.c	\
	monad/array/compare.c	\
	monad/array/iterate.c	\
	monad/array/map.c		\
	monad/array/filter.c	\
	monad/list/item.c		\
	monad/list/length.c		\
	monad/list/new.c		\
	monad/list/create.c		\
	monad/list/delete.c		\
	monad/list/duplicate.c	\
	monad/list/get.c		\
	monad/list/set.c		\
	monad/list/copy.c		\
	monad/list/sub.c		\
	monad/list/append.c		\
	monad/list/prepend.c	\
	monad/list/insert.c		\
	monad/list/remove.c		\
	monad/list/removeall.c	\
	monad/list/removeat.c	\
	monad/list/replace.c	\
	monad/list/find.c		\
	monad/list/count.c		\
	monad/list/contains.c	\
	monad/list/has.c		\
	monad/list/equals.c		\
	monad/list/compare.c	\
	monad/list/iterate.c	\
	monad/list/map.c		\
	monad/list/filter.c		\
	monad/convert/list.c	\
	encode/kvt/new.c		\
	encode/kvt/add.c		\
	encode/kvt/concat.c		\
	encode/kvt/create.c		\
	encode/kvt/length.c		\
	encode/kvt/get.c		\
	encode/kvt/set.c		\
	encode/kvt/array.c		\
	encode/kvt/duplicate.c	\
	encode/kvt/equals.c		\
	encode/kvt/insert.c		\
	encode/kvt/is.c			\
	encode/kvt/delete.c		\
	encode/kvt/detach.c		\
	encode/kvt/replace.c	\
	encode/kvt/print.c		\
	encode/json/parse.c		\
	encode/json/print.c		\
	encode/json/minify.c	\
	encode/toml/parse.c		\
	encode/toml/print.c		\
	encode/toml/minify.c	\

# define object files list (.o) from source list
OBJS = ${SRCS:%.c=$(OBJDIR)%.o}

# define dependency files list (.d)
DEPS = ${OBJS:.o=.d}



#######################################
#           Main build rules          #
#######################################

# This is the default build rule, called when doing 'make' without args
all: debug

# This rule builds the library, in DEBUG mode (with '-g -ggdb -D DEBUG=1')
debug: MODE = debug
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME_STATIC) $(NAME_DYNAMIC)

# This rule fills the ./bin folder with necessary files for release distribution
release: MODE = release
release: CFLAGS += $(CFLAGS_RELEASE)
release: $(NAME_STATIC) $(NAME_DYNAMIC)



# This rule should be executed once, after cloning the repo
init:
	@git config core.hooksPath ./.github/hooks



# This rule prepares ZIP archives in ./dist for each platform from the contents of the ./bin folder
dist: release
	@rm -f $(DISTDIR)*
	@mkdir -p $(DISTDIR)
	@$(MAKE) -s dist_version OSMODE=win32 LIBMODE=dynamic
	@$(MAKE) -s dist_version OSMODE=win32 LIBMODE=static
	@$(MAKE) -s dist_version OSMODE=win64 LIBMODE=dynamic
	@$(MAKE) -s dist_version OSMODE=win64 LIBMODE=static
	@$(MAKE) -s dist_version OSMODE=linux LIBMODE=dynamic
	@$(MAKE) -s dist_version OSMODE=linux LIBMODE=static
	@$(MAKE) -s dist_version OSMODE=macos LIBMODE=dynamic
	@$(MAKE) -s dist_version OSMODE=macos LIBMODE=static

# This rule creates one ZIP distributable according to the current OSMODE and LIBMODE
dist_version:
	@printf "Preparing ZIP: "
	@printf $(DISTDIR)$(NAME)_$(VERSION)_$(OSMODE)_$(LIBMODE).zip"\n"
	@zip -j $(DISTDIR)$(NAME)_$(VERSION)_$(OSMODE)_$(LIBMODE).zip	$(BINDIR)$(LIBMODE)/$(OSMODE)/*
	@printf $(C_GREEN)"  OK!"$(C_RESET)"\n"



# This rule compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# This rule builds the static library file to link against, in the root directory
$(NAME_STATIC): $(OBJS)
	@mkdir -p $(BINDIR)static/$(OSMODE)/
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"
	@cp -f $(NAME_STATIC)	$(BINDIR)static/$(OSMODE)/



# This rule builds the dynamically-linked library files for the current target platform
$(NAME_DYNAMIC): $(OBJS)
	@mkdir -p $(BINDIR)dynamic/$(OSMODE)/
ifeq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	@printf \
	"Compiling DLL: "$(NAME_DYNAMIC)" -> " ; \
	$(CC) -shared -o $(NAME_DYNAMIC) $(CFLAGS) $(LDFLAGS) $(OBJS) \
	-Wl,--output-def,$(NAME).def \
	-Wl,--out-implib,$(NAME).lib \
	-Wl,--export-all-symbols
	@cp -f $(NAME).def	$(BINDIR)dynamic/$(OSMODE)/
	@cp -f $(NAME).lib	$(BINDIR)dynamic/$(OSMODE)/
else ifeq ($(OSMODE),macos)
	@printf \
	"Compiling dylib: "$(NAME_DYNAMIC)" -> " ; \
	$(CC) -shared   -o $(NAME_DYNAMIC) $(CFLAGS) $(LDFLAGS) $(OBJS)
else ifeq ($(OSMODE),linux)
	@printf \
	"Compiling .so: "$(NAME_DYNAMIC)" -> " ; \
	$(CC) -shared -o $(NAME_DYNAMIC) $(CFLAGS) $(LDFLAGS) $(OBJS)
endif
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"
	@cp -f $(NAME_DYNAMIC)	$(BINDIR)dynamic/$(OSMODE)/



#######################################
#          CI Testing program         #
#######################################

TEST_DIR = ./test/

TEST_HDRS = \
	$(TEST_DIR)test.h		\
	$(TEST_DIR)test_catch.h	\
	$(TEST_DIR)test_timer.h	\
	$(TEST_DIR)test_utils.h	\

TEST_SRCS = \
	$(TEST_DIR)main.c		\
	$(TEST_DIR)test.c		\
	$(TEST_DIR)test_timer.c	\
	$(TEST_DIR)test_catch.c	\
	$(TEST_DIR)util.c		\
	$(TEST_DIR)util_print.c	\
	$(TEST_DIR)libccc/bool.c	\
	$(TEST_DIR)libccc/char.c	\
	$(TEST_DIR)libccc/int.c		\
	$(TEST_DIR)libccc/fixed.c	\
	$(TEST_DIR)libccc/float.c	\
	$(TEST_DIR)libccc/color.c	\
	$(TEST_DIR)libccc/memory.c			\
	$(TEST_DIR)libccc/pointer.c			\
	$(TEST_DIR)libccc/pointerarray.c	\
	$(TEST_DIR)libccc/string.c			\
	$(TEST_DIR)libccc/stringarray.c		\
	$(TEST_DIR)libccc/text/regex.c	\
	$(TEST_DIR)libccc/sys/io.c		\
	$(TEST_DIR)libccc/sys/time.c	\
	$(TEST_DIR)libccc/math/math.c		\
	$(TEST_DIR)libccc/math/int.c		\
	$(TEST_DIR)libccc/math/fixed.c		\
	$(TEST_DIR)libccc/math/float.c		\
	$(TEST_DIR)libccc/math/stat.c		\
	$(TEST_DIR)libccc/math/vlq.c		\
	$(TEST_DIR)libccc/math/algebra.c	\
	$(TEST_DIR)libccc/math/complex.c	\
	$(TEST_DIR)libccc/random/random.c	\
	$(TEST_DIR)libccc/monad/array.c			\
	$(TEST_DIR)libccc/monad/list.c			\
	$(TEST_DIR)libccc/monad/tree.c			\
	$(TEST_DIR)libccc/monad/dict.c			\
	$(TEST_DIR)libccc/monad/object.c		\
	$(TEST_DIR)libccc/encode/json.c			\
	$(TEST_DIR)libccc/encode/toml.c			\

TEST_OBJS = ${TEST_SRCS:%.c=$(OBJDIR)%.o}
TEST_DEPS = ${TEST_OBJS:.o=.d}

TEST_INCLUDEDIRS = \
	-I$(HDRDIR) \
	-I$(TEST_DIR) \

TEST_CFLAGS = -O2 -g -ggdb -Wno-format-extra-args -fno-inline
# -fanalyzer
TEST_LDFLAGS = $(LDFLAGS)

TEST_LIBS = -L./ -lccc -lpthread -lm
ifneq ($(OSMODE),macos)
	TEST_LIBS := -static $(TEST_LIBS)
endif



# This rule compiles object files from source files
$(OBJDIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c $(TEST_HDRS)
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -c $< -o $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# This rule builds the testing/CI program
$(NAME_TEST): debug $(TEST_OBJS)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(TEST_OBJS) $(TEST_LIBS)
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

# This rule builds and runs the test executable
test: $(NAME_TEST)
	@./$(NAME_TEST) $(ARGS)

test_log: $(NAME_TEST)
	@mkdir -p $(LOGDIR)
	@./$(NAME_TEST) $(ARGS) -var --test-all >> $(LOGDIR)libccc_test.log



test_predef:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@rm -f						$(LOGDIR)env/$(OSMODE)/predef_$(CC).c
	@./$(TEST_DIR)_predef.sh >>	$(LOGDIR)env/$(OSMODE)/predef_$(CC).c

test_errno:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@rm -f						$(LOGDIR)env/$(OSMODE)/errno_$(CC).c
	@./$(TEST_DIR)_errno.sh >>	$(LOGDIR)env/$(OSMODE)/errno_$(CC).c

$(NAME_TEST)_helloworld: debug
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(CFLAGS) -I$(HDRDIR) \
	-o $(NAME_TEST)_helloworld \
		$(TEST_DIR)_helloworld.c \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

test_helloworld: $(NAME_TEST)_helloworld
	@ ./$(NAME_TEST)_helloworld $(ARGS)
	@rm $(NAME_TEST)_helloworld

$(NAME_TEST)_foreach: debug
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(CFLAGS) -I$(HDRDIR) \
	-o $(NAME_TEST)_foreach \
		$(TEST_DIR)_foreach.c \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

test_foreach: $(NAME_TEST)_foreach
	@ ./$(NAME_TEST)_foreach $(ARGS)
	@rm $(NAME_TEST)_foreach



#######################################
#        Generate documentation       #
#######################################

DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest

# This rule generates documentation for libccc
doc:
	@rm -rf $(DOCDIR)xml/*
	@rm -rf $(DOCDIR)rst/*
	@rm -rf $(DOCDIR)man/*
	@rm -rf $(DOCDIR)rtf/*
	@rm -rf $(DOCDIR)pdf/*
	@rm -rf $(DOCDIR)html/*
	@rm -rf $(DOCDIR)latex/*
	@doxygen $(DOCDIR)doxygen-config.doxygen
	@$(DOXYREST) -c $(DOCDIR)doxyrest-config.lua
	@sphinx-build -b html $(DOCDIR)rst $(DOCDIR)html -c $(DOCDIR)

#	@sphinx-build -M latexpdf $(DOCDIR)rst $(DOCDIR)pdf  -c $(DOCDIR)
#	@$(MAKE) -C $(DOCDIR)pdf/latex/ all



#######################################
#          Linting operations         #
#######################################

# These rules run a linter on all source files,
# giving useful additionnal warnings concerning the code

lint:
# CCPcheck: http://cppcheck.sourceforge.net/
	@cppcheck $(SRCDIR) $(HDRDIR) --quiet --std=c99 --enable=all \
		-DTRUE=1 -DFALSE=0 -DERROR=1 -DOK=0 -D__GNUC__ \
		--suppress=variableScope \
		--suppress=unusedFunction \
		--suppress=memleak \
		--template="-[{severity}]\t{file}:{line}\t->\t{id}: {message}" \
		--template-location="  -> from:\t{file}:{line}\t->\t{info}"
# splint: http://splint.org/
#	@splint

PCLP				= /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/pclp32.exe
PCLP_SETUP =python3.8 /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/config/pclp_config.py
PCLP_IMPOSTER		= /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/config/imposter
PCLP_IMPOSTER_LOG	= pclint_imposter_log.txt
PCLP_LOG			= pclint_log.txt
PCLP_CONFIG			= pclint_config
PCLP_PROJECT		= pclint_project

pclint_setup:
	$(PCLP_SETUP) \
		--compiler=$(CC) \
		--compiler-bin=/usr/bin/$(CC) \
		--compiler-options="$(CFLAGS)" \
		--config-output-lnt-file=$(PCLP_CONFIG).lnt \
		--config-output-header-file=$(PCLP_CONFIG).h \
		--generate-compiler-config
	@export IMPOSTER_LOG=$(PCLP_IMPOSTER_LOG)
	@$(CC) $(CFLAGS) $(PCLP_IMPOSTER).c -o $(PCLP_IMPOSTER)
	@$(PCLP_IMPOSTER) $(CFLAGS) $(SRCS) -o $@ $(HDRDIR) $(LIBS)
	$(PCLP_SETUP) \
		--compiler=$(CC) \
		--imposter-file=$(PCLP_IMPOSTER_LOG) \
		--config-output-lnt-file=$(PCLP_PROJECT).lnt \
		--generate-project-config
	@rm $(PCLP_IMPOSTER_LOG)

pclint:
# pc-lint: https://gimpel.com/
	@printf "Running linter: "
	@$(PCLP) -width"(120,4)" -format="%(%f:%l%):\n[%n]->%t: %m" -w2 \
		-e438 -e534 -e641 -e655 -e695 -e835 -e2445 \
		$(PCLP_CONFIG).lnt $(PCLP_PROJECT).lnt > $(PCLP_LOG)
	@printf $(C_GREEN)"SUCCESS"$(C_RESET)": output file is "$(PCLP_LOG)"\n"



#######################################
#       Preprocessing operations      #
#######################################

PREPROCESSED	=	${SRCS:%.c=$(OBJDIR)%.c}

preprocessed: all $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"

$(OBJDIR)%.c: $(SRCDIR)%.c
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



#######################################
#        File deletion rules          #
#######################################

clean:
	@printf "Deleting all .o files...\n"
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@printf "Deleting all .d files...\n"
	@rm -f $(DEPS)
	@rm -f $(TEST_DEPS)
	@rm -f *.d

fclean: clean
	@printf "Deleting library: "$(NAME_STATIC)"\n"
	@rm -f $(NAME_STATIC)
	@printf "Deleting library: "$(NAME_DYNAMIC)"\n"
	@rm -f $(NAME_DYNAMIC)
	@rm -f $(NAME).*
	@printf "Deleting program: "$(NAME_TEST)"\n"
	@rm -f $(NAME_TEST)
	@rm -f $(NAME_TEST).d

rclean: fclean
	@printf "Deleting "$(OBJDIR)" folder...\n"
	@rm -rf $(OBJDIR)

aclean: rclean logclean
	@printf "Deleting "$(BINDIR)" folder...\n"
	@rm -rf $(BINDIR)

logclean:
	@printf "Deleting "$(LOGDIR)" folder...\n"
	@rm -rf $(LOGDIR)

tclean:
	@printf "Deleting test .o files...\n"
	@rm -f $(TEST_OBJS)
	@printf "Deleting test .d files...\n"
	@rm -f $(TEST_DEPS)

re: fclean all



#######################################
#        Meta makefile rules          #
#######################################

# This line ensures the makefile won't conflict with files named 'clean', 'fclean', etc
.PHONY: \
	all				\
	debug			\
	release			\
	init			\
	dist			\
	dist_version	\
	test			\
	test_predef		\
	test_errno		\
	test_helloworld	\
	test_foreach	\
	doc				\
	lint			\
	preprocessed	\
	clean			\
	fclean			\
	rclean			\
	aclean			\
	logclean		\
	re				\

# The following line is for Makefile GCC dependency file handling (.d files)
-include ${DEPS}
-include ${TEST_DEPS}
