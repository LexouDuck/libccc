
# directories
BINDIR = bin
OBJDIR = obj
GENDIR = gen
SRCDIR = src

# output program
NAME = $(BINDIR)/ppp

# generated c code
HDRS = $(YACC_HDR)
SRCS = $(YACC_SRC) $(LEX_SRC)

# c compiler
CC = clang
CFLAGS = 
LDLIBS = -ll
# lex
LEX_SRC = $(GENDIR)/lex.yy.c
LEX_INPUT = $(SRCDIR)/c11.lex
LEX = lex
LFLAGS = 
# yacc
YACC_HDR = $(GENDIR)/y.tab.h
YACC_SRC = $(GENDIR)/y.tab.c
YACC_INPUT = $(SRCDIR)/c11.yacc
YACC = yacc
YFLAGS = -d



all: dirs $(NAME)

dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(GENDIR)

$(NAME): $(SRCS) $(HDRS)
	$(CC)   $(CFLAGS) -o $(NAME) $(SRCS) $(LDLIBS)

$(LEX_SRC): $(LEX_INPUT)
	$(LEX)  $(LFLAGS) -o $(LEX_SRC) $(LEX_INPUT)

$(YACC_SRC): $(YACC_INPUT)
	$(YACC) $(YFLAGS) -o $(YACC_SRC) $(YACC_INPUT)
