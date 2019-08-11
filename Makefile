NAME	=	libft.a

# Compiler
CC		= _
CC_WIN	= i686-w64-mingw32-gcc
CC_LIN	= gcc
CC_MAC	= gcc

# Compiler flags
CFLAGS	=	-Wall -Wextra -Werror $(CFLAGS_PLATFORM) -O2 -MMD
CFLAGS_PLATFORM = _
CFLAGS_WIN	= -mwindows
CFLAGS_LIN	= -Wno-unused-result 
CFLAGS_MAC	= 

# Set platform-specific variables
ifeq ($(OS),Windows_NT)
	CC := $(CC_WIN)
	CFLAGS_PLATFORM := $(CFLAGS_WIN)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC := $(CC_LIN)
		CFLAGS_PLATFORM := $(CFLAGS_LIN)
	endif
	ifeq ($(UNAME_S),Darwin)
		CC := $(CC_MAC)
		CFLAGS_PLATFORM := $(CFLAGS_MAC)
	endif
endif

DIR_MEMORY	:=	memory/
SRC_MEMORY	:=	ft_memalloc.c	\
				ft_memset.c		\
				ft_memdel.c		\
				ft_memcpy.c		\
				ft_memdup.c		\
				ft_memmove.c	\
				ft_memcmp.c		\
				ft_memchr.c		\
				ft_memswap.c	\
				ft_getbits.c	

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


DIR_STRINGARRAY	:=	stringarray/
SRC_STRINGARRAY	:=	ft_strsplit.c	\

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
SRC_LIST	:=	ft_lstnew.c		\
				ft_lstadd.c		\
				ft_lstcpy.c		\
				ft_lstdel.c		\
				ft_lstsize.c	\
				ft_lstget.c		\
				ft_lstsub.c		\
				ft_lstiter.c	\
				ft_lstmap.c		\
				ft_lst_to.c

DIR_MATH	:=	math/
SRC_MATH	:=	ft_realfunctions.c	\
				ft_random.c			\
				ft_calc.c			\
				ft_stat.c

DIR_VLQ		:=	vlq/
SRC_VLQ		:=	

DIR_IO		:=	io/
SRC_IO		:=	ft_output.c		\
				ft_write.c		\
				ft_read.c		\
				ft_getnextline.c

SRCDIR	=	./src/
OBJDIR	=	./obj/

HDRS	=	libft_memory.h	\
			libft_string.h	\
			libft_char.h	\
			libft_convert.h	\
			libft_math.h	\
			libft_list.h	\
			libft_io.h		\
			libft.h			
SRCS	=	$(addprefix $(DIR_MEMORY),		$(SRC_MEMORY)		)	\
			$(addprefix $(DIR_CHAR),		$(SRC_CHAR)			)	\
			$(addprefix $(DIR_STRING),		$(SRC_STRING)		)	\
			$(addprefix $(DIR_STRINGARRAY),	$(SRC_STRINGARRAY)	)	\
			$(addprefix $(DIR_CONVERT),		$(SRC_CONVERT)		)	\
			$(addprefix $(DIR_COLOR),		$(SRC_COLOR)		)	\
			$(addprefix $(DIR_LIST),		$(SRC_LIST)			)	\
			$(addprefix $(DIR_MATH),		$(SRC_MATH)			)	\
			$(addprefix $(DIR_VLQ),			$(SRC_VLQ)			)	\
			$(addprefix $(DIR_IO),			$(SRC_IO)			)

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

all: $(NAME)

$(OBJS): | objdir

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDRS)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@ -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

objdir:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)$(DIR_MEMORY)
	@mkdir -p $(OBJDIR)$(DIR_CHAR)
	@mkdir -p $(OBJDIR)$(DIR_STRING)
	@mkdir -p $(OBJDIR)$(DIR_STRINGARRAY)
	@mkdir -p $(OBJDIR)$(DIR_CONVERT)
	@mkdir -p $(OBJDIR)$(DIR_COLOR)
	@mkdir -p $(OBJDIR)$(DIR_LIST)
	@mkdir -p $(OBJDIR)$(DIR_MATH)
	@mkdir -p $(OBJDIR)$(DIR_VLQ)
	@mkdir -p $(OBJDIR)$(DIR_IO)

clean:
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@printf "Deleting library file: "$(NAME)"\n"
	@rm -f $(NAME)

rclean:
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)

tclean:
	@printf "Deleting libft test...\n"
	@rm -f test
	@rm -f test.exe*

re: fclean all



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



TESTS :=	test_memory.c		\
			test_char.c			\
			test_string.c		\
			test_stringarray.c	\
			test_convert.c		\
			test_color.c		\
			test_list.c			\
			test_math.c			\
			test_vlq.c			\
			test_io.c			\
			test.c				\
			util_test.c

testprogram: all
	@gcc -g -o test $(addprefix $(SRCDIR), $(TESTS)) $(NAME)

test: testprogram
	@./test

test_memory: testprogram
	@./test -memory

test_char: testprogram
	@./test -char

test_string: testprogram
	@./test -string

test_stringarray: testprogram
	@./test -stringarray

test_convert: testprogram
	@./test -convert

test_color: testprogram
	@./test -color

test_list: testprogram
	@./test -list

test_math: testprogram
	@./test -math

test_vlq: testprogram
	@./test -vlq

test_io: testprogram
	@./test -io

-include ${DEPENDS}
