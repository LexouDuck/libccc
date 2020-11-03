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
CFLAGS_OS_WIN   = -mwindows -shared
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
		OSMODE = "WIN32"
		CC = $(CC_WIN32)
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSMODE = "WIN64"
		CC = $(CC_WIN64)
    endif
	CFLAGS_OS = $(CFLAGS_OS_WIN)
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSMODE = "LINUX"
		CC = $(CC_LINUX)
		CFLAGS_OS = $(CFLAGS_OS_LINUX)
	endif
	ifeq ($(UNAME_S),Darwin)
		OSMODE = "MACOS"
		CC = $(CC_MACOS)
		CFLAGS_OS = $(CFLAGS_OS_MACOS)
	endif
endif



# Define colors for terminal output
RED   = "\033[0;31m"
GREEN = "\033[0;32m"
RESET = "\033[0m"



DIR_MEMORY = memory/
SRC_MEMORY = \
	ft_memalloc.c	\
	ft_memnew.c		\
	ft_memfree.c	\
	ft_memdel.c		\
	ft_memset.c		\
	ft_memcpy.c		\
	ft_memdup.c		\
	ft_memmove.c	\
	ft_memcmp.c		\
	ft_memchr.c		\
	ft_memswap.c	\
	ft_memrep.c 	\
	ft_getbits.c	\
	ft_ptrarrnew.c	\
	ft_ptrarrlen.c	\

DIR_CHAR = char/
SRC_CHAR = \
	ft_isalpha.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_to.c			

DIR_STRING = string/
SRC_STRING = \
	ft_strnew.c		\
	ft_strset.c		\
	ft_strclr.c		\
	ft_strdel.c		\
	ft_strdup.c		\
	ft_strcpy.c		\
	ft_strcat.c		\
	ft_strlen.c		\
	ft_strcmp.c		\
	ft_strequ.c		\
	ft_strhas.c		\
	ft_strcount.c	\
	ft_strchr.c		\
	ft_strstr.c		\
	ft_strremove.c	\
	ft_strtrim.c	\
	ft_strpad.c		\
	ft_strrev.c		\
	ft_strjoin.c	\
	ft_strinsert.c	\
	ft_strsub.c		\
	ft_striter.c	\
	ft_strmap.c		\
	ft_strrep.c		\
	ft_strmerge.c	\
	ft_strprint.c	\


DIR_STRINGARRAY = stringarray/
SRC_STRINGARRAY = \
	ft_strsplit_char.c		\
	ft_strsplit_charset.c	\
	ft_strsplit_str.c		\
	ft_strdivide.c			\
	ft_strarrnew.c			\
	ft_strarrcnew.c			\
	ft_strarrdel.c			\
	ft_strarrmap.c			\
	ft_strarrsub.c			\
	ft_strarrpad_l.c		\
	ft_strarrjoin.c			\
	ft_strarrlen.c			\
	ft_strarrcount.c		\
	ft_strarrmerge.c		\


DIR_CONVERT = convert/
SRC_CONVERT = \
	ft_int_s_to_str.c		\
	ft_int_s_to_strbase.c	\
	ft_int_u_to_str.c		\
	ft_int_u_to_strbase.c	\
	ft_int_u_to_hex.c		\
	ft_float_to_str.c		\
	ft_f32_to_str.c			\
	ft_f64_to_str.c			\
	ft_size_to_str.c		\
	ft_bool_to_str.c		\
	ft_str_to_int_s.c		\
	ft_str_to_int_u.c		\
	ft_str_to_float.c		\
	ft_str_to_f32.c			\
	ft_str_to_f64.c			\
	ft_str_to_size.c		\
	ft_str_to_bool.c		\
	ft_hex_to_int_u.c		\

DIR_COLOR = color/
SRC_COLOR = \
	ft_color_argb16_get.c	\
	ft_color_argb16_set.c	\
	ft_color_argb16_to.c	\
	ft_color_argb32_get.c	\
	ft_color_argb32_set.c	\
	ft_color_argb32_to.c	\

DIR_LIST = list/
SRC_LIST = \
	ft_lstnew.c			\
	ft_lstadd.c			\
	ft_lstcpy.c			\
	ft_lstdel.c			\
	ft_lstsize.c		\
	ft_lstget.c			\
	ft_lstsub.c			\
	ft_lstiter.c		\
	ft_lstmap.c			\
	ft_lst_to.c			\

DIR_MATH = math/
SRC_MATH = \
	ft_math.c			\
	ft_root.c			\
	ft_exp.c			\
	ft_calc.c			\
	ft_trigonometry.c	\

DIR_STAT = stat/
SRC_STAT = \
	ft_stat_int.c		\
	ft_stat_float.c		\

DIR_RANDOM = random/
SRC_RANDOM = \
	ft_random.c			\

DIR_VLQ	 = vlq/
SRC_VLQ	 = \

DIR_IO	 = io/
SRC_IO	 = \
	ft_output.c			\
	ft_write.c			\
	ft_read.c			\
	ft_getnextline.c	\



# List of all header files
HDRS = \
	$(HDRDIR)libft.h				\
	$(HDRDIR)libft_io.h				\
	$(HDRDIR)libft_memory.h			\
	$(HDRDIR)libft_char.h			\
	$(HDRDIR)libft_string.h			\
	$(HDRDIR)libft_stringarray.h	\
	$(HDRDIR)libft_convert.h		\
	$(HDRDIR)libft_color.h			\
	$(HDRDIR)libft_list.h			\
	$(HDRDIR)libft_math.h			\
	$(HDRDIR)libft_stat.h			\
	$(HDRDIR)libft_random.h			\
	$(HDRDIR)libft_vlq.h			\

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
	@cp $(NAME).a $(BINDIR) 2>/dev/null || :
	@if [ $(OSMODE) = "WIN32" ] || [ $(OSMODE) = "WIN64" ]; then printf \
		"Compiling DLL: "$(BINDIR)$(NAME).dll" -> " ; \
		$(CC) -shared -o $(BINDIR)$(NAME).dll $(OBJS) \
		-Wl,--output-def,$(BINDIR)$(NAME).def \
		-Wl,--out-implib,$(BINDIR)$(NAME).lib \
		-Wl,--export-all-symbols ; \
	elif [ $(OSMODE) = "MACOS" ]; then printf \
		"Compiling dylib: "$(BINDIR)$(NAME).dylib" -> " ; \
		$(CC) -shared   -o $(BINDIR)$(NAME).dylib $(OBJS) ; \
	elif [ $(OSMODE) = "LINUX" ]; then printf \
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
	@mkdir -p $(OBJDIR)
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
$(NAME_TEST): $(TEST_OBJS) $(NAME).a
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(TEST_OBJS) -L./ -lft -lm
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
