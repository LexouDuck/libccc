
include ../../mkfile/config/modes.mk

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
HDRS = $(YACC_HDR) $(SRCDIR)/ppp.h           
SRCS = $(YACC_SRC) $(SRCDIR)/ppp.c \
	$(SRCDIR)/ppp_log.c \
	$(SRCDIR)/ppp_symbol.c \
	$(LEX_SRC)



# c compiler
CC = clang
CFLAGS = -g \
	-Wall \
	-Wextra \
	-Winline \

LDLIBS = ../../bin/$(BUILDMODE)_$(OSMODE)_$(CPUMODE)/static/libccc.a -ll
INCLUDES = \
	-I$(GENDIR) \
	-I$(SRCDIR) \
	-I$(LIBDIR) \

# lex
LEX_SRC = $(GENDIR)/lex.yy.c
LEX_INPUT = $(SRCDIR)/parser.l
LEX = flex
LFLAGS = 

# yacc
YACC_HDR = $(GENDIR)/y.tab.h
YACC_SRC = $(GENDIR)/y.tab.c
YACC_INPUT = $(SRCDIR)/parser.y
YACC = bison
YFLAGS = 



all: dirs $(NAME)

test: all
ifeq ($(strip $(FILE)),)
	@echo "ERROR: expected FILE argument for this make rule" ; exit 1
endif
	@./$(NAME) --debug --verbose $(FILE) > "$(OUTFILE)"
	@echo "=========="
	@cat "$(OUTFILE)"

debug: LFLAGS += -d
debug: YFLAGS += -t
debug: all
ifeq ($(strip $(FILE)),)
	@echo "ERROR: expected FILE argument for this make rule" ; exit 1
endif
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
	@echo "OK!"

$(LEX_SRC): $(LEX_INPUT)
	$(LEX)  $(LFLAGS) -o $(LEX_SRC) $(LEX_INPUT)

$(YACC_SRC): $(YACC_INPUT)
	$(YACC) $(YFLAGS) --defines=$(YACC_HDR) -o $(YACC_SRC) $(YACC_INPUT)
