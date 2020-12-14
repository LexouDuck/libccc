# Output file names
NAME      = libft
NAME_TEST = libft_test

# Compiler
CC	= _
CC_WIN32 = i686-w64-mingw32-gcc
CC_WIN64 = x86_64-w64-mingw32-gcc
CC_LINUX = gcc
CC_MACOS = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Winline -Wpedantic -Werror $(CFLAGS_OS) -MMD
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



DIR_MEMORY = memory/
SRC_MEMORY = \
	memalloc.c		\
	memnew.c		\
	memfree.c		\
	memdel.c		\
	memset.c		\
	memcpy.c		\
	memdup.c		\
	memmove.c		\
	memcmp.c		\
	memchr.c		\
	memswap.c		\
	memrep.c		\
	getbits.c		\
	ptrarrnew.c		\
	ptrarrlen.c		\

DIR_IO	 = io/
SRC_IO	 = \
	output.c		\
	write.c			\
	read.c			\
	getnextline.c	\

DIR_CHAR = char/
SRC_CHAR = \
	isalpha.c		\
	isdigit.c		\
	isprint.c		\
	to.c			\

DIR_STRING = string/
SRC_STRING = \
	strnew.c		\
	strset.c		\
	strclr.c		\
	strdel.c		\
	strdup.c		\
	strcpy.c		\
	strcat.c		\
	strlen.c		\
	strcmp.c		\
	strequ.c		\
	strhas.c		\
	strcount.c		\
	strchr.c		\
	strstr.c		\
	strremove.c		\
	strtrim.c		\
	strpad.c		\
	strrev.c		\
	strjoin.c		\
	strinsert.c		\
	strsub.c		\
	striter.c		\
	strmap.c		\
	strrep.c		\
	strmerge.c		\
	strprint.c		\


DIR_STRINGARRAY = stringarray/
SRC_STRINGARRAY = \
	strsplit_char.c		\
	strsplit_charset.c	\
	strsplit_str.c		\
	strdivide.c			\
	strarrnew.c			\
	strarrcnew.c		\
	strarrdel.c			\
	strarrmap.c			\
	strarrsub.c			\
	strarrpad_l.c		\
	strarrjoin.c		\
	strarrlen.c			\
	strarrcount.c		\
	strarrmerge.c		\


DIR_CONVERT = convert/
SRC_CONVERT = \
	int_s_to_str.c		\
	int_s_to_strbase.c	\
	int_u_to_str.c		\
	int_u_to_strbase.c	\
	int_u_to_hex.c		\
	float_to_str.c		\
	f32_to_str.c		\
	f64_to_str.c		\
	size_to_str.c		\
	bool_to_str.c		\
	str_to_int_s.c		\
	str_to_int_u.c		\
	str_to_float.c		\
	str_to_f32.c		\
	str_to_f64.c		\
	str_to_size.c		\
	str_to_bool.c		\
	hex_to_int_u.c		\

DIR_COLOR = color/
SRC_COLOR = \
	color_argb_get.c	\
	color_argb_set.c	\
	color_argb_to.c		\
	color_nearest.c		\
	color_convert.c		\

DIR_LIST = list/
SRC_LIST = \
	lstnew.c			\
	lstadd.c			\
	lstcpy.c			\
	lstdel.c			\
	lstsize.c			\
	lstget.c			\
	lstsub.c			\
	lstiter.c			\
	lstmap.c			\
	lst_to.c			\

DIR_MATH = math/
SRC_MATH = \
	math.c				\
	pow.c				\
	root.c				\
	exp.c				\
	log.c				\
	trig.c				\
	trig_h.c			\

DIR_ALGEBRA = algebra/
SRC_ALGEBRA = \
	calculus.c				\
	vector_new.c			\
	vector_equ.c			\
	vector_scale.c			\
	vector_invert.c			\
	vector_norm.c			\
	vector_normalize.c		\
	vector_add.c			\
	vector_dot.c			\
	vector_cross.c			\
	matrix_new.c			\
	matrix_equ.c			\
	matrix_apply.c			\
	matrix_determinant.c	\
	matrix_inverse.c		\
	matrix_transpose.c		\
	matrix_multiply.c		\

DIR_COMPLEX = complex/
SRC_COMPLEX = \
	complex_new.c		\
	complex_equ.c		\
	complex_abs.c		\
	complex_conj.c		\
	complex_add.c		\
	complex_sub.c		\
	complex_mul.c		\
	complex_div.c		\

DIR_STAT = stat/
SRC_STAT = \
	stat_int.c			\
	stat_float.c		\

DIR_RANDOM = random/
SRC_RANDOM = \
	random.c			\

DIR_VLQ	 = vlq/
SRC_VLQ	 = \



# List of all source code files
SRCS = \
	$(addprefix $(DIR_IO),			$(SRC_IO)			) \
	$(addprefix $(DIR_MEMORY),		$(SRC_MEMORY)		) \
	$(addprefix $(DIR_CHAR),		$(SRC_CHAR)			) \
	$(addprefix $(DIR_STRING),		$(SRC_STRING)		) \
	$(addprefix $(DIR_STRINGARRAY),	$(SRC_STRINGARRAY)	) \
	$(addprefix $(DIR_CONVERT),		$(SRC_CONVERT)		) \
	$(addprefix $(DIR_COLOR),		$(SRC_COLOR)		) \
	$(addprefix $(DIR_LIST),		$(SRC_LIST)			) \
	$(addprefix $(DIR_MATH),		$(SRC_MATH)			) \
	$(addprefix $(DIR_ALGEBRA),		$(SRC_ALGEBRA)		) \
	$(addprefix $(DIR_COMPLEX),		$(SRC_COMPLEX)		) \
	$(addprefix $(DIR_STAT),		$(SRC_STAT)			) \
	$(addprefix $(DIR_RANDOM),		$(SRC_RANDOM)		) \
	$(addprefix $(DIR_VLQ),			$(SRC_VLQ)			) \

# define object files list (.o) from source list
OBJS = ${SRCS:%.c=$(OBJDIR)%.o}

# define dependency files list (.d)
DPDS = ${OBJS:.o=.d}



#######################################
#          Main build rules           #
#######################################

# This is the default build rule, called when doing 'make' without args
debug: MODE = debug
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: all

# This rule fills the 'bin' folder with necessary files for release distribution
release: MODE = release
release: CFLAGS += $(CFLAGS_RELEASE)
release: all
	@mkdir -p $(BINDIR)
	@if [ $(OSMODE) = win32 ] || [ $(OSMODE) = win64 ]; then printf \
		"Compiling DLL: "$(BINDIR)$(NAME).dll" -> " ; \
		$(CC) -shared -o $(BINDIR)$(NAME).dll $(OBJS) \
		-Wl,--output-def,$(BINDIR)$(NAME).def \
		-Wl,--out-implib,$(BINDIR)$(NAME).lib \
		-Wl,--export-all-symbols ; \
	elif [ $(OSMODE) = macos ]; then printf \
		"Compiling dylib: "$(BINDIR)$(NAME).dylib" -> " ; \
		$(CC) -shared   -o $(BINDIR)$(NAME).dylib $(OBJS) ; \
	elif [ $(OSMODE) = linux ]; then printf \
		"Compiling .so lib: "$(BINDIR)$(NAME).so" -> " ; \
		$(CC) -shared     -o $(BINDIR)$(NAME).so $(OBJS) ; \
	fi
	@printf $(GREEN)"OK!"$(RESET)"\n"

all: $(NAME).a

# This rule compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds the libft library file to link against
$(NAME).a: $(OBJS)
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"



#######################################
#          CI Testing program         #
#######################################

TEST_DIR	=	./test/

TEST_HDRS = $(TEST_DIR)test.h
TEST_SRCS = \
	$(TEST_DIR)main.c			\
	$(TEST_DIR)util.c			\
	$(TEST_DIR)util_print.c		\
	$(TEST_DIR)test_memory.c		\
	$(TEST_DIR)test_char.c			\
	$(TEST_DIR)test_string.c		\
	$(TEST_DIR)test_stringarray.c	\
	$(TEST_DIR)test_convert.c		\
	$(TEST_DIR)test_color.c			\
	$(TEST_DIR)test_list.c			\
	$(TEST_DIR)test_math.c			\
	$(TEST_DIR)test_stat.c			\
	$(TEST_DIR)test_random.c		\
	$(TEST_DIR)test_vlq.c			\
	$(TEST_DIR)test_io.c			\

TEST_OBJS = ${TEST_SRCS:$(TEST_DIR)%.c=$(OBJDIR)%.o}

TEST_CFLAGS = -O2 -g -ggdb
TEST_INCLUDEDIRS = -I$(HDRDIR) -I$(TEST_DIR)

# This rule compiles object files from source files
$(OBJDIR)%.o : $(TEST_DIR)%.c
	@printf "Compiling file: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds the testing/CI program
$(NAME_TEST): debug $(TEST_OBJS)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(TEST_OBJS) -L./ -lft -lm
	@if [ $(OSMODE) = win32 ]; then \
		cp $(TEST_DIR)libwinpthread-32.dll ./libwinpthread-1.dll ; \
	elif [ $(OSMODE) = win64 ]; then \
		cp $(TEST_DIR)libwinpthread-64.dll ./libwinpthread-1.dll ; \
	fi
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds and runs the test executable
test: $(NAME_TEST)
	@./$(NAME_TEST)



#######################################
#        File deletion rules          #
#######################################

clean:
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@printf "Deleting dependency files...\n"
	@rm -f $(DPDS)
	@rm -f *.d

fclean: clean
	@printf "Deleting library: "$(NAME).a"\n"
	@rm -f $(NAME).a
	@printf "Deleting program: "$(NAME_TEST)"\n"
	@rm -f $(NAME_TEST)
	@rm -f $(NAME_TEST).d

rclean: fclean
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)
	@printf "Deleting bin folder...\n"
	@rm -rf $(BINDIR)

re: fclean all



#######################################
#        Generate documentation       #
#######################################

DOXYREST = $(DOCDIR)doxyrest/bin/doxyrest.exe

doc:
	@doxygen $(DOCDIR)project.doxygen
	@$(DOXYREST) -c $(DOCDIR)doxyrest-config.lua
	@sphinx-build -b html $(DOCDIR)rst $(DOCDIR)html -c $(DOCDIR)



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

$(OBJDIR)%.c : $(SRCDIR)%.c
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"



# This line ensures the makefile won't conflict with files named 'clean', 'fclean', etc
.PHONY : test
.PHONY : clean fclean rclean re
.PHONY : lint pclint_setup pclint
.PHONY : doc preprocessed

# The following line is for Makefile GCC dependency file handling (.d files)
-include ${DPDS}
