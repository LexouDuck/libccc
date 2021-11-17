
# directories
BINDIR = bin
OBJDIR = obj
GENDIR = gen
SRCDIR = src
LIBDIR = ../../hdr

# output program
NAME = $(BINDIR)/ppp
OUTFILE = obj/test.c

# generated c code
HDRS = $(SRCDIR)/ppp.h $(YACC_HDR)
SRCS = $(SRCDIR)/ppp.c $(YACC_SRC) $(LEX_SRC)


# c compiler
CC = clang
CFLAGS = -g
LDLIBS = ../../libccc.a -ll
INCLUDES = \
	-I$(GENDIR) \
	-I$(SRCDIR) \
	-I$(LIBDIR) \

# lex
LEX_SRC = $(GENDIR)/lex.yy.c
LEX_INPUT = $(SRCDIR)/parser.l
LEX = lex
LFLAGS = 

# yacc
YACC_HDR = $(GENDIR)/y.tab.h
YACC_SRC = $(GENDIR)/y.tab.c
YACC_INPUT = $(SRCDIR)/parser.y
YACC = yacc
YFLAGS = 



all: dirs $(NAME)

test: all
	@./$(NAME) $(FILE) > "$(OUTFILE)"
	@echo "=========="
	@cat "$(OUTFILE)"

dirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(GENDIR)

clean:
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)
	@rm -rf $(GENDIR)

$(NAME): $(SRCS) $(HDRS)
	$(CC)   $(CFLAGS) -o $(NAME) $(INCLUDES) $(SRCS) $(LDLIBS)

$(LEX_SRC): $(LEX_INPUT)
	$(LEX)  $(LFLAGS) -o $(LEX_SRC) $(LEX_INPUT)

$(YACC_SRC): $(YACC_INPUT)
	$(YACC) $(YFLAGS) --defines=$(YACC_HDR) -o $(YACC_SRC) $(YACC_INPUT)
