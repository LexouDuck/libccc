# Output file names
NAME		=	libft
NAME_TEST	=	libft_test

# Compiler
CC	= _
CC_WIN	= i686-w64-mingw32-gcc
CC_LIN	= gcc
CC_MAC	= gcc

# Compiler flags
CFLAGS	=	-Wall -Wextra -Winline -Wpedantic -Werror $(CFLAGS_PLATFORM) -MMD -O2

CFLAGS_PLATFORM = _
CFLAGS_WIN	= -mwindows -shared
CFLAGS_LIN	= -Wno-unused-result
CFLAGS_MAC	= 

# Directories that this Makefile will use
BINDIR	=	./bin/
HDRDIR	=	./hdr/
SRCDIR	=	./src/
OBJDIR	=	./obj/

# Set platform-specific variables
ifeq ($(OS),Windows_NT)
	OSFLAG := "WIN"
	CC := $(CC_WIN)
	CFLAGS_PLATFORM := $(CFLAGS_WIN)
	SED_DEL_OPT	:=	-r
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG := "LIN"
		CC := $(CC_LIN)
		CFLAGS_PLATFORM := $(CFLAGS_LIN)
		SED_DEL_OPT	:= 
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG := "MAC"
		CC := $(CC_MAC)
		CFLAGS_PLATFORM := $(CFLAGS_MAC)
		SED_DEL_OPT	:=
	endif
endif



# Define colors for terminal output
RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"



DIR_MEMORY	:=	memory/
SRC_MEMORY	:=	ft_memalloc.c	\
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

DIR_CHAR	:=	char/
SRC_CHAR	:=	ft_isalpha.c	\
				ft_isdigit.c	\
				ft_isprint.c	\
				ft_to.c			

DIR_STRING	:=	string/
SRC_STRING	:=	ft_strnew.c		\
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


DIR_STRINGARRAY	:=	stringarray/
SRC_STRINGARRAY	:=	ft_strsplit_char.c		\
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


DIR_CONVERT	:=	convert/
SRC_CONVERT	:=	ft_int_s_to_str.c		\
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

DIR_COLOR	:=	color/
SRC_COLOR	:=	ft_color_argb16_get.c	\
				ft_color_argb16_set.c	\
				ft_color_argb16_to.c	\
				ft_color_argb32_get.c	\
				ft_color_argb32_set.c	\
				ft_color_argb32_to.c	\

DIR_LIST	:=	list/
SRC_LIST	:=	ft_lstnew.c			\
				ft_lstadd.c			\
				ft_lstcpy.c			\
				ft_lstdel.c			\
				ft_lstsize.c		\
				ft_lstget.c			\
				ft_lstsub.c			\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_lst_to.c			\

DIR_MATH	:=	math/
SRC_MATH	:=	ft_math.c			\
				ft_root.c			\
				ft_exp.c			\
				ft_calc.c			\
				ft_trigonometry.c	\

DIR_STAT	:=	stat/
SRC_STAT	:=	ft_stat_int.c		\
				ft_stat_float.c		\

DIR_RANDOM	:=	random/
SRC_RANDOM	:=	ft_random.c			\

DIR_VLQ		:=	vlq/
SRC_VLQ		:=	

DIR_IO		:=	io/
SRC_IO		:=	ft_output.c			\
				ft_write.c			\
				ft_read.c			\
				ft_getnextline.c	\



# List of all header files
HDRS	=	$(HDRDIR)libft_memory.h			\
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
			$(HDRDIR)libft_io.h				\
			$(HDRDIR)libft.h

# List of all source code files
SRCS	=	$(addprefix $(DIR_MEMORY),		$(SRC_MEMORY)		)	\
			$(addprefix $(DIR_CHAR),		$(SRC_CHAR)			)	\
			$(addprefix $(DIR_STRING),		$(SRC_STRING)		)	\
			$(addprefix $(DIR_STRINGARRAY),	$(SRC_STRINGARRAY)	)	\
			$(addprefix $(DIR_CONVERT),		$(SRC_CONVERT)		)	\
			$(addprefix $(DIR_COLOR),		$(SRC_COLOR)		)	\
			$(addprefix $(DIR_LIST),		$(SRC_LIST)			)	\
			$(addprefix $(DIR_MATH),		$(SRC_MATH)			)	\
			$(addprefix $(DIR_STAT),		$(SRC_STAT)			)	\
			$(addprefix $(DIR_RANDOM),		$(SRC_RANDOM)		)	\
			$(addprefix $(DIR_VLQ),			$(SRC_VLQ)			)	\
			$(addprefix $(DIR_IO),			$(SRC_IO)			)

# Define object list and dependency files (.d)
OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}
DEPENDS	=	${OBJS:.o=.d}



#######################################
#          Main build rules           #
#######################################

all: $(NAME).a
	@cp *.dll $(BINDIR)
	@cp $(NAME).* $(BINDIR)

$(OBJS): | dir

dir:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(DIR_MEMORY)
	@mkdir -p $(OBJDIR)$(DIR_CHAR)
	@mkdir -p $(OBJDIR)$(DIR_STRING)
	@mkdir -p $(OBJDIR)$(DIR_STRINGARRAY)
	@mkdir -p $(OBJDIR)$(DIR_CONVERT)
	@mkdir -p $(OBJDIR)$(DIR_COLOR)
	@mkdir -p $(OBJDIR)$(DIR_LIST)
	@mkdir -p $(OBJDIR)$(DIR_MATH)
	@mkdir -p $(OBJDIR)$(DIR_STAT)
	@mkdir -p $(OBJDIR)$(DIR_RANDOM)
	@mkdir -p $(OBJDIR)$(DIR_VLQ)
	@mkdir -p $(OBJDIR)$(DIR_IO)

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDRS)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) -o $@ -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(NAME).a: $(OBJS) $(HDRS)
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@if [ $(OSFLAG) = "WIN" ]; then \
		printf $(GREEN)"OK!"$(RESET)"\n" ; printf \
		"Compiling DLL: "$(NAME).dll" -> " ; \
		$(CC) -shared -o $(NAME).dll $(OBJS) \
		-Wl,--output-def,$(NAME).def ; \
	fi
	@printf $(GREEN)"OK!"$(RESET)"\n"



#######################################
#        File deletion rules          #
#######################################

clean:
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)
	@printf "Deleting dependency files...\n"
	@rm -f $(DEPENDS)
	@rm -f *.d

fclean: clean
	@printf "Deleting library file(s): "$(NAME)"\n"
	@rm -f $(NAME).*

rclean: clean
	@printf "Deleting obj folder...\n"
	@rmdir $(OBJDIR)

tclean:
	@printf "Deleting libft test...\n"
	@rm -f test
	@rm -f libft_test.exe*

re: fclean all



#######################################
#          CI Testing program         #
#######################################

TEST_DIR	=	./test/

TEST_HDR := $(TEST_DIR)test.h
TEST_SRC :=	$(TEST_DIR)main.c		\
			$(TEST_DIR)util.c		\
			$(TEST_DIR)util_print.c	\
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

TEST_OBJ	=	${TEST_SRC:$(TEST_DIR)%.c=$(OBJDIR)%.o}

TEST_CFLAGS			=	-O2 -g -ggdb
TEST_INCLUDEDIRS	=	-I$(HDRDIR) -I$(TEST_DIR)

# This rule compiles object files from source files
$(OBJDIR)%.o : $(TEST_DIR)%.c $(TEST_HDR)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds the testing/CI program
$(NAME_TEST): $(TEST_OBJ) $(TEST_HDR) $(NAME).a
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(TEST_OBJ) -L./ -lft -lm
	@printf $(GREEN)"OK!"$(RESET)"\n"

# This rule builds and runs the test executable
test: $(NAME_TEST)
	@./$(NAME_TEST)



#######################################
#          Other operations           #
#######################################

lint:
	@cppcheck $(SRCDIR) $(HDRDIR) --quiet --std=c99 --enable=all \
		--suppress=memleak \
		--suppress=variableScope \
		--suppress=unusedFunction \
		--template="-[{severity}]\t{file}:{line}\t->\t{id}: {message}" \
		--template-location="  -> from:\t{file}:{line}\t->\t{info}"



PREPROCESSED	=	${SRCS:%.c=$(OBJDIR)%.c}

preprocessed: all $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"

$(OBJDIR)%.c : $(SRCDIR)%.c $(HDRS)
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"



replace:
	@sed -i -e "s|$(old)|$(new)|g" $(addprefix $(SRCDIR), $(SRCS))
	@printf "Replaced all instances of \'"$(old)"\' with \'"$(new)"\'.\n"

rename:
	@sed -i -e "s|\<$(old)\>|$(new)|g" $(addprefix $(SRCDIR), $(SRCS))
	@printf "Renamed all words matching \'"$(old)"\' with \'"$(new)"\'.\n"



# The following line is for Makefile GCC dependency file handling (.d files)
-include ${DEPENDS}
