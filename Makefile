# Output file names
NAME      = libccc
NAME_TEST = libccc_test

VERSION = 0.7

# Compiler
CC	= _
CC_WIN32 = i686-w64-mingw32-gcc -static -static-libgcc
CC_WIN64 = x86_64-w64-mingw32-gcc -static -static-libgcc
CC_LINUX = gcc
CC_MACOS = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Winline -Wpedantic -Werror $(CFLAGS_OS) -MMD -fstrict-aliasing
CFLAGS_DEBUG = -g -ggdb -D DEBUG=1
CFLAGS_RELEASE = -O3
# -Wno-unused-result -Wno-unused-parameter
CFLAGS_OS = _
CFLAGS_OS_WIN   = -D__USE_MINGW_ANSI_STDIO=1
CFLAGS_OS_LINUX = -fPIC -Wno-unused-result
CFLAGS_OS_MACOS = 

# Directories that this Makefile will use
HDRDIR = ./hdr/
SRCDIR = ./src/
OBJDIR = ./obj/
BINDIR = ./bin/
DOCDIR = ./doc/
DISTDIR = ./dist/



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

ifeq ($(OSMODE),win32)
	CC = $(CC_WIN32)
	CFLAGS_OS = $(CFLAGS_OS_WIN)
endif
ifeq ($(OSMODE),win64)
	CC = $(CC_WIN64)
	CFLAGS_OS = $(CFLAGS_OS_WIN)
endif
ifeq ($(OSMODE),linux)
	CC = $(CC_LINUX)
	CFLAGS_OS = $(CFLAGS_OS_LINUX)
endif
ifeq ($(OSMODE),macos)
	CC = $(CC_MACOS)
	CFLAGS_OS = $(CFLAGS_OS_MACOS)
endif



# Define colors for terminal output
RED   = "\033[0;31m"
GREEN = "\033[0;32m"
RESET = "\033[0m"



# List of all source code files
SRCS = \
	char/isalpha.c		\
	char/isdigit.c		\
	char/isprint.c		\
	char/incharset.c	\
	char/to.c			\
	char/utf8.c			\
	char/utf16.c		\
	bool/bool_to_str.c		\
	bool/bool_from_str.c	\
	int/int_to_str.c		\
	int/int_to_strbase.c	\
	int/int_to_strhex.c		\
	int/int_to_stroct.c		\
	int/int_to_strbin.c		\
	int/int_from_str.c		\
	int/int_from_strbase.c	\
	int/int_from_strhex.c	\
	int/int_from_stroct.c	\
	int/int_from_strbin.c	\
	fixed/fixed.c			\
	fixed/fixed_to_str.c	\
	fixed/fixed_from_str.c	\
	fixed/operators.c		\
	float/float.c			\
	float/float_to_str.c	\
	float/float_from_str.c	\
	float/operators.c		\
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
	memory/getbits.c	\
	pointer/size_to_str.c	\
	pointer/str_to_size.c	\
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
	sys/io/fd.c					\
	sys/io/error.c				\
	sys/io/color.c				\
	sys/io/open.c				\
	sys/io/close.c				\
	sys/io/chmod.c				\
	sys/io/read.c				\
	sys/io/read_nextline.c		\
	sys/io/write.c				\
	sys/io/output.c				\
	sys/time/time.c			\
	sys/time/date.c			\
	sys/time/date_format.c	\
	sys/time/date_parse.c	\
	sys/time/strings.c		\
	sys/logger/core.c	\
	sys/logger/util.c	\
	sys/logger/init.c	\
	sys/logger/log.c	\
	math/math.c		\
	math/pow.c		\
	math/root.c		\
	math/exp.c		\
	math/log.c		\
	math/trig.c		\
	math/trig_h.c	\
	math/random/random.c	\
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
	encode/kvt/error.c		\
	encode/json/parse.c		\
	encode/json/print.c		\
	encode/json/minify.c	\

# define object files list (.o) from source list
OBJS = ${SRCS:%.c=$(OBJDIR)%.o}

# define dependency files list (.d)
DPDS = ${OBJS:.o=.d}



#######################################
#           Main build rules          #
#######################################

# This is the default build rule, called when doing 'make' without args
all: debug

# This rule builds the library, in DEBUG mode (with '-g -ggdb -D DEBUG=1')
debug: MODE = debug
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME).a dynlib

# This rule fills the ./bin folder with necessary files for release distribution
release: MODE = release
release: CFLAGS += $(CFLAGS_RELEASE)
release: $(NAME).a dynlib

dynlib: $(NAME).a
	@mkdir -p $(BINDIR)dynamic/$(OSMODE)/
	@mkdir -p $(BINDIR)static/$(OSMODE)/
	@cp $(NAME).a $(BINDIR)static/$(OSMODE)/
ifeq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	@printf \
	"Compiling DLL: "$(BINDIR)dynamic/$(OSMODE)/$(NAME).dll" -> " ; \
	$(CC) -shared -o $(BINDIR)dynamic/$(OSMODE)/$(NAME).dll $(OBJS)	\
	-Wl,--output-def,$(BINDIR)dynamic/$(OSMODE)/$(NAME).def	\
	-Wl,--out-implib,$(BINDIR)dynamic/$(OSMODE)/$(NAME).lib	\
	-Wl,--export-all-symbols
else ifeq ($(OSMODE),macos)
	@printf \
	"Compiling dylib: "$(BINDIR)dynamic/$(OSMODE)/$(NAME).dylib" -> " ; \
	$(CC) -shared   -o $(BINDIR)dynamic/$(OSMODE)/$(NAME).dylib $(OBJS)
else ifeq ($(OSMODE),linux)
	@printf \
	"Compiling .so: "$(BINDIR)dynamic/$(OSMODE)/$(NAME).so" -> " ; \
	$(CC) -shared -o $(BINDIR)dynamic/$(OSMODE)/$(NAME).so $(OBJS)
else
	@printf $(RED)"ERROR"$(RESET)": OS not supported -> OSMODE="$(OSMODE)"\n"
	exit 1
endif
	@printf $(GREEN)"OK!"$(RESET)"\n"

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
	@printf $(GREEN)"  OK!"$(RESET)"\n"



# This rule compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds the static library file to link against, in the root directory
$(NAME).a: $(OBJS)
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"



#######################################
#          CI Testing program         #
#######################################

TEST_DIR = ./test/

TEST_HDRS = $(TEST_DIR)test.h
TEST_SRCS = \
	$(TEST_DIR)main.c		\
	$(TEST_DIR)util.c		\
	$(TEST_DIR)util_print.c	\
	$(TEST_DIR)libccc/bool.c	\
	$(TEST_DIR)libccc/char.c	\
	$(TEST_DIR)libccc/int.c		\
	$(TEST_DIR)libccc/fixed.c	\
	$(TEST_DIR)libccc/float.c	\
	$(TEST_DIR)libccc/pointer.c	\
	$(TEST_DIR)libccc/memory.c	\
	$(TEST_DIR)libccc/string.c	\
	$(TEST_DIR)libccc/color.c	\
	$(TEST_DIR)libccc/sys/io.c		\
	$(TEST_DIR)libccc/sys/time.c	\
	$(TEST_DIR)libccc/sys/regex.c	\
	$(TEST_DIR)libccc/math/math.c		\
	$(TEST_DIR)libccc/math/stat.c		\
	$(TEST_DIR)libccc/math/algebra.c	\
	$(TEST_DIR)libccc/math/complex.c	\
	$(TEST_DIR)libccc/math/random.c		\
	$(TEST_DIR)libccc/math/vlq.c		\
	$(TEST_DIR)libccc/monad/array.c			\
	$(TEST_DIR)libccc/monad/pointerarray.c	\
	$(TEST_DIR)libccc/monad/stringarray.c	\
	$(TEST_DIR)libccc/monad/list.c			\
	$(TEST_DIR)libccc/monad/tree.c			\
	$(TEST_DIR)libccc/monad/dict.c			\

TEST_OBJS = ${TEST_SRCS:%.c=$(OBJDIR)%.o}

TEST_CFLAGS = -O2 -g -ggdb
TEST_INCLUDEDIRS = -I$(HDRDIR) -I$(TEST_DIR)

# This rule compiles object files from source files
$(OBJDIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c $(TEST_HDRS)
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds the testing/CI program
$(NAME_TEST): debug $(TEST_OBJS)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(TEST_OBJS) -L./ -lccc -lm -lpthread
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds and runs the test executable
test: $(NAME_TEST)
	@./$(NAME_TEST) -a



#######################################
#        File deletion rules          #
#######################################

clean:
	@printf "Deleting object files...\n"
	@rm -rf $(OBJS)
	@rm -rf $(TEST_OBJS)
	@printf "Deleting dependency files...\n"
	@rm -rf $(DPDS)
	@rm -rf *.d

fclean: clean
	@printf "Deleting library: "$(NAME).a"\n"
	@rm -rf $(NAME).a
	@printf "Deleting program: "$(NAME_TEST)"\n"
	@rm -rf $(NAME_TEST)
	@rm -rf $(NAME_TEST).d

rclean: fclean
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)
	@printf "Deleting bin folder...\n"
	@rm -rf $(BINDIR)

re: fclean all



#######################################
#        Generate documentation       #
#######################################

DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest

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
		--compiler=gcc \
		--compiler-bin=/usr/bin/gcc \
		--compiler-options="$(CFLAGS)" \
		--config-output-lnt-file=$(PCLP_CONFIG).lnt \
		--config-output-header-file=$(PCLP_CONFIG).h \
		--generate-compiler-config
	@export IMPOSTER_LOG=$(PCLP_IMPOSTER_LOG)
	@$(CC) $(CFLAGS) $(PCLP_IMPOSTER).c -o $(PCLP_IMPOSTER)
	@$(PCLP_IMPOSTER) $(CFLAGS) $(SRCS) -o $@ $(HDRDIR) $(LIBS)
	$(PCLP_SETUP) \
		--compiler=gcc \
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
	@printf $(GREEN)"SUCCESS"$(RESET)": output file is "$(PCLP_LOG)"\n"



#######################################
#       Preprocessing operations      #
#######################################

PREPROCESSED	=	${SRCS:%.c=$(OBJDIR)%.c}

preprocessed: all $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"

$(OBJDIR)%.c: $(SRCDIR)%.c
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"



# This line ensures the makefile won't conflict with files named 'clean', 'fclean', etc
.PHONY: all debug release dist dist_version
.PHONY: test
.PHONY: clean fclean rclean re
.PHONY: lint pclint_setup pclint
.PHONY: doc preprocessed

# The following line is for Makefile GCC dependency file handling (.d files)
-include ${DPDS}
