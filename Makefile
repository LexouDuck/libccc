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
	bool/str_to_bool.c		\
	int/int_to_str.c			\
	int/int_to_strbase.c		\
	int/int_to_strhex.c			\
	int/str_to_int.c			\
	int/strbase_to_int.c		\
	int/strhex_to_int.c			\
	fixed/fixed.c				\
	fixed/fixed_to_str.c		\
	fixed/str_to_fixed.c		\
	float/float_equals.c	\
	float/float_to_str.c	\
	float/str_to_float.c	\
	memory/memalloc.c	\
	memory/memnew.c		\
	memory/memfree.c	\
	memory/memdel.c		\
	memory/memset.c		\
	memory/memcpy.c		\
	memory/memdup.c		\
	memory/memmove.c	\
	memory/memmerge.c	\
	memory/memcmp.c		\
	memory/memchr.c		\
	memory/memswap.c	\
	memory/memrep.c		\
	memory/getbits.c	\
	pointer/size_to_str.c	\
	pointer/str_to_size.c	\
	pointer/ptr_to_str.c	\
	pointerarray/ptrarrnew.c		\
	pointerarray/ptrarrlen.c		\
	string/strnew.c		\
	string/strset.c		\
	string/strclr.c		\
	string/strdel.c		\
	string/strdup.c		\
	string/strcpy.c		\
	string/strcat.c		\
	string/strlen.c		\
	string/strcmp.c		\
	string/strequ.c		\
	string/strhas.c		\
	string/strcount.c	\
	string/strfind.c	\
	string/strfind_r.c	\
	string/strfind_n.c	\
	string/strremove.c	\
	string/strtrim.c	\
	string/strpad.c		\
	string/strrev.c		\
	string/strmerge.c	\
	string/strinsert.c	\
	string/strsub.c		\
	string/strformat.c	\
	string/striter.c	\
	string/strmap.c		\
	string/strrep.c		\
	string/strprint.c	\
	stringarray/strsplit_char.c		\
	stringarray/strsplit_charset.c	\
	stringarray/strsplit_str.c		\
	stringarray/strdivide.c			\
	stringarray/strarrnew.c			\
	stringarray/strarrcnew.c		\
	stringarray/strarrdel.c			\
	stringarray/strarrmap.c			\
	stringarray/strarrsub.c			\
	stringarray/strarrpad_l.c		\
	stringarray/strarrfold.c		\
	stringarray/strarrjoin.c		\
	stringarray/strarrlen.c			\
	stringarray/strarrcount.c		\
	stringarray/strarrmerge.c		\
	color/color_argb_get.c	\
	color/color_argb_set.c	\
	color/color_argb_to.c	\
	color/color_convert.c	\
	color/color_nearest.c	\
	color/color_diff.c		\
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
	math/algebra/vector_new.c			\
	math/algebra/vector_equ.c			\
	math/algebra/vector_scale.c			\
	math/algebra/vector_invert.c		\
	math/algebra/vector_norm.c			\
	math/algebra/vector_normalize.c		\
	math/algebra/vector_add.c			\
	math/algebra/vector_dot.c			\
	math/algebra/vector_cross.c			\
	math/algebra/matrix_new.c			\
	math/algebra/matrix_equ.c			\
	math/algebra/matrix_apply.c			\
	math/algebra/matrix_determinant.c	\
	math/algebra/matrix_inverse.c		\
	math/algebra/matrix_transpose.c		\
	math/algebra/matrix_multiply.c		\
	math/complex/complex_new.c		\
	math/complex/complex_equ.c		\
	math/complex/complex_abs.c		\
	math/complex/complex_conj.c		\
	math/complex/complex_add.c		\
	math/complex/complex_sub.c		\
	math/complex/complex_mul.c		\
	math/complex/complex_div.c		\
	math/stat/stat_int.c	\
	math/stat/stat_float.c	\
	monad/array/arrnew.c		\
	monad/array/arrdel.c		\
	monad/array/arrdup.c		\
	monad/array/arrget.c		\
	monad/array/arrset.c		\
	monad/array/arrcpy.c		\
	monad/array/arrsub.c		\
	monad/array/arrappend.c		\
	monad/array/arrprepend.c	\
	monad/array/arrinsert.c		\
	monad/array/arrremove.c		\
	monad/array/arrremoveall.c	\
	monad/array/arrremoveat.c	\
	monad/array/arrreplace.c	\
	monad/array/arrfind.c		\
	monad/array/arrequ.c		\
	monad/array/arrcmp.c		\
	monad/array/arriter.c		\
	monad/array/arrmap.c		\
	monad/array/arrfilt.c		\
	monad/list/lstitem.c		\
	monad/list/lstnew.c			\
	monad/list/lstdel.c			\
	monad/list/lstdup.c			\
	monad/list/lstget.c			\
	monad/list/lstset.c			\
	monad/list/lstcpy.c			\
	monad/list/lstsub.c			\
	monad/list/lstappend.c		\
	monad/list/lstprepend.c		\
	monad/list/lstinsert.c		\
	monad/list/lstremove.c		\
	monad/list/lstremoveall.c	\
	monad/list/lstremoveat.c	\
	monad/list/lstreplace.c		\
	monad/list/lstfind.c		\
	monad/list/lstequ.c			\
	monad/list/lstcmp.c			\
	monad/list/lstsize.c		\
	monad/list/lstiter.c		\
	monad/list/lstmap.c			\
	monad/list/lstfilt.c		\
	monad/convert/list.c		\

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
	$(TEST_DIR)libccc/regex.c	\
	$(TEST_DIR)libccc/color.c	\
	$(TEST_DIR)libccc/sys/io.c		\
	$(TEST_DIR)libccc/sys/time.c	\
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
	@doxygen $(DOCDIR)project.doxygen
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
