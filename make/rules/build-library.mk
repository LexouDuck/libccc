#! This file holds C-specific rules to build a library



#! List of all C header code files
HDRS := $(shell cat $(HDRSFILE))

#! List of all C source code files
SRCS := $(shell cat $(SRCSFILE))

#! Derive list of compiled object files (.o) from list of srcs
OBJS := ${SRCS:%.c=$(OBJDIR)%.o}

#! Derive list of dependency files (.d) from list of srcs
DEPS := ${OBJS:.o=.d}



.PHONY:\
update-lists-build # Create/update the list of source/header files
update-lists-build:
	@find $(HDRDIR) -name "*.h" | sort | sed "s|$(HDRDIR)/||g" > $(HDRSFILE)
	@find $(SRCDIR) -name "*.c" | sort | sed "s|$(SRCDIR)/||g" > $(SRCSFILE)



#! Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -MMD -I$(HDRDIR) -c $<
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



#! Builds the static library file to link against, in the root directory
$(NAME_STATIC): $(OBJS)
	@mkdir -p $(BINDIR)$(OSMODE)/static/
	@printf "Compiling static library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"
	@cp -f $(NAME_STATIC)	$(BINDIR)$(OSMODE)/static/



#! Builds the dynamically-linked library files for the current target platform
$(NAME_DYNAMIC): $(OBJS)
	@mkdir -p $(BINDIR)$(OSMODE)/dynamic/
ifeq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	@printf    "Compiling dynamic library: $(NAME_DYNAMIC) -> "
	@$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME_DYNAMIC) $(OBJS) \
	-Wl,--output-def,$(NAME).def \
	-Wl,--out-implib,$(NAME).lib \
	-Wl,--export-all-symbols
	@cp -f $(NAME).def	$(BINDIR)$(OSMODE)/dynamic/
	@cp -f $(NAME).lib	$(BINDIR)$(OSMODE)/dynamic/
else ifeq ($(OSMODE),macos)
	@printf    "Compiling dynamic library: $(NAME_DYNAMIC) -> "
	@$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME_DYNAMIC) $(OBJS)
else ifeq ($(OSMODE),linux)
	@printf    "Compiling dynamic library: $(NAME_DYNAMIC) -> "
	@$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME_DYNAMIC) $(OBJS)
else
	@printf $(C_YELLOW)"Unknown platform: needs manual configuration."$(C_RESET)"\n"
	@printf "You must manually configure the script to build a dynamic library""\n"
endif
	@cp -f $(NAME_DYNAMIC)	$(BINDIR)$(OSMODE)/dynamic/
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# The following line is for `.d` dependency file handling
-include ${DEPS}
