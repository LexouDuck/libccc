# the two following lines are to stay at the very top of this Makefile and never move
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH)))

#######################################
#          Project variables          #
#######################################

VERSION = 0.8

# Output file names
NAME      = libccc
NAME_STATIC  = $(NAME).a
NAME_DYNAMIC = $(NAME).$(DYNAMICLIB_FILE_EXT)
# Build names with filetype suffixes
NAME_LIBMODE = _
ifeq ($(LIBMODE),static)
	NAME_LIBMODE = $(NAME_STATIC)
endif
ifeq ($(LIBMODE),dynamic)
	NAME_LIBMODE = $(NAME_DYNAMIC)
endif
NAME_TEST = libccc-test

# Directories that this Makefile will use
HDRDIR = ./hdr/
SRCDIR = ./src/
OBJDIR = ./obj/
LIBDIR = ./lib/
DOCDIR = ./doc/
BINDIR = ./bin/
LOGDIR = ./log/
DISTDIR = ./dist/
LINTDIR = ./lint/
TEMPDIR = ./temp/



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
ifneq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	CFLAGS_DEBUG += -fsanitize=address
endif
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
	DYNAMICLIB_FILE_EXT=dll
else ifeq ($(OSMODE),win64)
	CC = $(CC_WIN64)
	CFLAGS_OS = $(CFLAGS_OS_WIN)
	LDFLAGS_OS = $(LDFLAGS_OS_WIN)
	DYNAMICLIB_FILE_EXT=dll
else ifeq ($(OSMODE),linux)
	CC = $(CC_LINUX)
	CFLAGS_OS = $(CFLAGS_OS_LINUX)
	LDFLAGS_OS = $(LDFLAGS_OS_LINUX)
	DYNAMICLIB_FILE_EXT=so
else ifeq ($(OSMODE),macos)
	CC = $(CC_MACOS)
	CFLAGS_OS = $(CFLAGS_OS_MACOS)
	LDFLAGS_OS = $(LDFLAGS_OS_MACOS)
	DYNAMICLIB_FILE_EXT=dylib
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
	encode/kvt/merge.c		\
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

.PHONY:\
all # Builds all targets (this is the default rule)
all: debug

.PHONY:\
debug # Builds the library, in DEBUG mode (with '-g -ggdb -D DEBUG=1')
debug: MODE = debug
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME_STATIC) $(NAME_DYNAMIC)

.PHONY:\
release # Fills the ./bin folder with necessary files for release distribution
release: MODE = release
release: CFLAGS += $(CFLAGS_RELEASE)
release: $(NAME_STATIC) $(NAME_DYNAMIC)
	@mkdir -p           $(BINDIR)$(OSMODE)/static/
	@cp $(NAME_STATIC)  $(BINDIR)$(OSMODE)/static/
	@mkdir -p           $(BINDIR)$(OSMODE)/dynamic/
	@cp $(NAME_DYNAMIC) $(BINDIR)$(OSMODE)/dynamic/



.PHONY:\
init # Should be executed once, after cloning the repo
init:
	@git config core.hooksPath ./.github/hooks



INSTALLDIR=/usr/local/lib/

.PHONY:\
install # Installs the libraries/programs (copies them from `./bin/` to `/usr/local/`, typically)
install:
	@cp    $(BINDIR)$(OSMODE)/static/$(NAME_STATIC)               $(INSTALLDIR)$(NAME).$(VERSION).a
	@cp    $(BINDIR)$(OSMODE)/dynamic/$(NAME_DYNAMIC)             $(INSTALLDIR)$(NAME).$(VERSION).$(DYNAMICLIB_FILE_EXT)
	@ln -s $(INSTALLDIR)$(NAME).$(VERSION).a                      $(INSTALLDIR)$(NAME).a
	@ln -s $(INSTALLDIR)$(NAME).$(VERSION).$(DYNAMICLIB_FILE_EXT) $(INSTALLDIR)$(NAME).$(DYNAMICLIB_FILE_EXT)

.PHONY:\
uninstall # Removes the installed libraries/programs (deletes files in `/usr/local/`, typically)
uninstall:
	@printf "Removing the following files:\n"
	@find $(INSTALLDIR) -name "$(NAME).*" -print -delete



.PHONY:\
dist # Prepares ZIP archives in ./dist for each platform from the contents of the ./bin folder
dist: release
	@mkdir -p $(DISTDIR)
	@-$(MAKE) -s dist-version OSMODE=win32
	@-$(MAKE) -s dist-version OSMODE=win64
	@-$(MAKE) -s dist-version OSMODE=linux
	@-$(MAKE) -s dist-version OSMODE=macos

.PHONY:\
dist-version # Creates one ZIP distributable according to the current 'OSMODE' and 'LIBMODE'
dist-version:
ifneq ($(wildcard $(BINDIR)$(OSMODE)/*),)
	@printf "Preparing .zip archive: "
else
	$(error Cannot produce distributable archive for target "$(OSMODE)")
endif
	@mkdir -p                   $(NAME)-$(VERSION)
	@cp -r $(BINDIR)$(OSMODE)/* $(NAME)-$(VERSION)
	@printf $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip"\n"
	@rm -rf $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip
	@zip -r $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip $(NAME)-$(VERSION)
	@rm -rf $(NAME)-$(VERSION)
	@printf $(C_GREEN)"  OK!"$(C_RESET)"\n"



# Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -MMD -I$(HDRDIR) -c $<
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# Builds the static library file to link against, in the root directory
$(NAME_STATIC): $(OBJS)
	@mkdir -p $(BINDIR)$(OSMODE)/static/
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"
	@cp -f $(NAME_STATIC)	$(BINDIR)$(OSMODE)/static/



# Builds the dynamically-linked library files for the current target platform
$(NAME_DYNAMIC): $(OBJS)
	@mkdir -p $(BINDIR)$(OSMODE)/dynamic/
ifeq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	@printf \
	"Compiling DLL: "$(NAME_DYNAMIC)" -> " ; \
	$(CC) -shared -o $(NAME_DYNAMIC) $(CFLAGS) $(LDFLAGS) $(OBJS) \
	-Wl,--output-def,$(NAME).def \
	-Wl,--out-implib,$(NAME).lib \
	-Wl,--export-all-symbols
	@cp -f $(NAME).def	$(BINDIR)$(OSMODE)/dynamic/
	@cp -f $(NAME).lib	$(BINDIR)$(OSMODE)/dynamic/
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
	@cp -f $(NAME_DYNAMIC)	$(BINDIR)$(OSMODE)/dynamic/



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
	$(TEST_DIR)libccc/encode/kvt.c			\
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



# Compiles object files from source files
$(OBJDIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c $(TEST_HDRS)
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -c $< -o $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# Builds the testing/CI program
$(NAME_TEST): $(NAME_STATIC) $(NAME_DYNAMIC) $(TEST_OBJS)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(TEST_OBJS) $(TEST_LIBS)
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

.PHONY:\
test # Builds and runs the test suite program with the given 'ARGS'
test: $(NAME_TEST)
	@./$(NAME_TEST) $(ARGS)

.PHONY:\
test-log # Builds and runs the test suite program with the given 'ARGS', logging all results to files
test-log: $(NAME_TEST)
	@mkdir -p $(LOGDIR)
	@./$(NAME_TEST) $(ARGS) -var --test-all >> $(LOGDIR)libccc_test.log



.PHONY:\
test-predef # Gets the list of all predefined macros for the current compiler/flags/env/arch
test-predef:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@./$(TEST_DIR)_predef.sh >	$(LOGDIR)env/$(OSMODE)/predef_$(CC).c
	@printf " => File saved to: $(LOGDIR)env/$(OSMODE)/predef_$(CC).c""\n"

.PHONY:\
test-errno # Gets the list of all 'errno' values for the current compiler/flags/env/arch
test-errno:
	@mkdir -p					$(LOGDIR)env/$(OSMODE)/
	@./$(TEST_DIR)_errno.sh >	$(LOGDIR)env/$(OSMODE)/errno_$(CC).c
	@printf " => File saved to: $(LOGDIR)env/$(OSMODE)/errno_$(CC).c""\n"



NAME_TEST_HELLOWORLD = libccc-test_helloworld
SRCS_TEST_HELLOWORLD = $(TEST_DIR)_helloworld.c

.PHONY:\
test-helloworld # Builds and runs a simple 'hello world' test program
test-helloworld: $(NAME_TEST_HELLOWORLD)
	@ ./$(NAME_TEST_HELLOWORLD) $(ARGS)
	@rm $(NAME_TEST_HELLOWORLD)

$(NAME_TEST_HELLOWORLD): $(NAME_STATIC) $(NAME_DYNAMIC) $(SRCS_TEST_HELLOWORLD)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) \
		-I$(HDRDIR) $(SRCS_TEST_HELLOWORLD) \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



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



NAME_TEST_KVT = libccc-test_kvt
SRCS_TEST_KVT = $(TEST_DIR)_kvt.c

.PHONY:\
test-kvt # Builds and runs a KVT (json,toml,yaml,xml) print/parse test program
test-kvt: $(NAME_TEST_KVT)
	@ ./$(NAME_TEST_KVT) $(ARGS)
	@rm $(NAME_TEST_KVT)

$(NAME_TEST_KVT): $(NAME_STATIC) $(NAME_DYNAMIC) $(SRCS_TEST_KVT)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) \
		-I$(HDRDIR) $(SRCS_TEST_KVT) \
		-L./ -lccc
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



#######################################
#        Generate documentation       #
#######################################

DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest

.PHONY:\
doc # Generates documentation for libccc
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

# define lint ouput files list from source list
LINT = ${SRCS:%.c=$(LINTDIR)%.html}

$(LINTDIR)%.html: $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Linting file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) 2> $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

.PHONY:\
lint # Runs a linter on all source files, giving useful additional warnings
lint: MODE = debug
ifeq (gcc,$(findstring gcc,$(CC)))
lint: CFLAGS += -fanalyzer
else ifeq (clang,$(findstring clang,$(CC)))
lint: CFLAGS += -Wthread-safety --analyze --analyzer-output text
else
$(error Unknown compiler "$(CC)", cannot estimate static analyzer linting options)
endif
lint: $(LINT)
	@find $(LINTDIR) -size 0 -print -delete
	@echo "Linting finished."



PCLP				= /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/pclp32.exe
PCLP_SETUP =python3.8 /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/config/pclp_config.py
PCLP_IMPOSTER		= /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/config/imposter
PCLP_IMPOSTER_LOG	= pclint_imposter_log.txt
PCLP_LOG			= pclint_log.txt
PCLP_CONFIG			= pclint_config
PCLP_PROJECT		= pclint_project

lint-pclint-setup:
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

# pc-lint: https://gimpel.com/
lint-pclint:
	@printf "Running linter: "
	@$(PCLP) -width"(120,4)" -format="%(%f:%l%):\n[%n]->%t: %m" -w2 \
		-e438 -e534 -e641 -e655 -e695 -e835 -e2445 \
		$(PCLP_CONFIG).lnt $(PCLP_PROJECT).lnt > $(PCLP_LOG)
	@printf $(C_GREEN)"SUCCESS"$(C_RESET)": output file is "$(PCLP_LOG)"\n"

# splint: http://splint.org/
#	@splint

# CCPcheck: http://cppcheck.sourceforge.net/
lint-cppcheck:
	@cppcheck $(SRCDIR) $(HDRDIR) --quiet --std=c99 --enable=all \
		-DTRUE=1 -DFALSE=0 -DERROR=1 -DOK=0 -D__GNUC__ \
		--suppress=variableScope \
		--suppress=unusedFunction \
		--suppress=memleak \
		--template="-[{severity}]\t{file}:{line}\t->\t{id}: {message}" \
		--template-location="  -> from:\t{file}:{line}\t->\t{info}"



#######################################
#       Preprocessing operations      #
#######################################

PREPROCESSED = ${SRCS:%.c=$(OBJDIR)%.c}

$(OBJDIR)%.c: $(SRCDIR)%.c
	@printf "Preprocessing file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -E $<
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"

.PHONY:\
preprocessed # Preprocesses all source files and stores them in the obj folder
preprocessed: all $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"



#######################################
#        File deletion rules          #
#######################################

.PHONY:\
clean # Deletes all intermediary build files
clean:
	@printf "Deleting all .o files...\n"
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@printf "Deleting all .d files...\n"
	@rm -f $(DEPS)
	@rm -f $(TEST_DEPS)
	@rm -f *.d

.PHONY:\
clean-exe # Deletes any libraries/executables
clean-exe:
	@rm -f $(NAME).*
	@printf "Deleting library: "$(NAME_STATIC)"\n"
	@rm -f $(NAME_STATIC)
	@printf "Deleting library: "$(NAME_DYNAMIC)"\n"
	@rm -f $(NAME_DYNAMIC)
	@printf "Deleting program: "$(NAME_TEST)"\n"
	@rm -f $(NAME_TEST)
	@rm -f $(NAME_TEST).d

.PHONY:\
clean-obj # Deletes the ./obj folder
clean-obj: clean-full
	@printf "Deleting "$(OBJDIR)" folder...\n"
	@rm -rf $(OBJDIR)

.PHONY:\
clean-bin # Deletes the ./bin folder
clean-bin:
	@printf "Deleting "$(BINDIR)" folder...\n"
	@rm -rf $(BINDIR)

.PHONY:\
clean-logs # Deletes the ./log folder
clean-logs:
	@printf "Deleting "$(LOGDIR)" folder...\n"
	@rm -rf $(LOGDIR)

.PHONY:\
clean-lint # Deletes the ./lint folder
clean-lint:
	@printf "Deleting "$(LINTDIR)" folder...\n"
	@rm -rf $(LINTDIR)

.PHONY:\
clean-full # Deletes every generated file
clean-full: clean clean-test

.PHONY:\
re # Deletes all generated files and rebuilds all
re: clean-full all



#######################################
#        Meta makefile rules          #
#######################################



.PHONY:\
help # Displays list of "PHONY" targets, with descriptions                                                                
help:                                                                                                                    
	@cat $(MKFILE_PATH) \
		| awk -v phony=0 '{ if(phony) { sub(/#/,"\t-"); phony=0; print } else if (/^\.PHONY:\\/) {phony=1} }' \
		| expand -t20



.PHONY:\
list # Displays list of all available targets in this Makefile, sorted in alphabetical order
list:
	@LC_ALL=C $(MAKE) -pRrq -f $(MKFILE_PATH) : 2>/dev/null \
		| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' \
		| sort \
		| egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
	# see https://stackoverflow.com/questions/4219255/how-do-you-get-the-list-of-targets-in-a-makefile



# The following line is for Makefile GCC dependency file handling (.d files)
-include ${DEPS}
-include ${TEST_DEPS}
