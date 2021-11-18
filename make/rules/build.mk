#! This file holds C-specific rules to build a library



#! Derive list of compiled object files (.o) from list of srcs
OBJS := $(SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS := $(OBJS:.o=.d)

# here we add linked library flags for each package
LDLIBS := $(LDLIBS) \
	$(foreach i,$(PACKAGES_LINK),$($(i)))

# here we add include header folders for each package
INCLUDES := $(INCLUDES) \
	$(foreach i,$(PACKAGES_INCLUDE),-I$($(i)))



.PHONY:\
build-debug #! Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-debug: MODE = debug
build-debug: CFLAGS += $(CFLAGS_DEBUG)
build-debug: $(NAME_STATIC) $(NAME_DYNAMIC)

.PHONY:\
build-release #! Builds the library, in 'release' mode (with optimization flags)
build-release: MODE = release
build-release: CFLAGS += $(CFLAGS_RELEASE)
build-release: $(NAME_STATIC) $(NAME_DYNAMIC)



#! Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Builds the static library file to link against, in the root directory
$(NAME_STATIC): $(OBJS)
	@mkdir -p $(BINDIR)$(OSMODE)/static/
	@printf "Compiling static library: "$@" -> "
	@ar -rc $@ $(OBJS)
	@ranlib $@
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@cp -f $(NAME_STATIC)	$(BINDIR)$(OSMODE)/static/



#! Builds the dynamically-linked library files for the current target platform
$(NAME_DYNAMIC): $(OBJS)
	@mkdir -p $(BINDIR)$(OSMODE)/dynamic/
ifeq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	@printf    "Compiling dynamic library: $(NAME_DYNAMIC) -> "
	@$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME_DYNAMIC) $(OBJS) $(LDLIBS) \
	-Wl,--output-def,$(NAME).def \
	-Wl,--out-implib,$(NAME).lib \
	-Wl,--export-all-symbols
	@cp -f $(NAME).def	$(BINDIR)$(OSMODE)/dynamic/
	@cp -f $(NAME).lib	$(BINDIR)$(OSMODE)/dynamic/
else ifeq ($(OSMODE),macos)
	@printf    "Compiling dynamic library: $(NAME_DYNAMIC) -> "
	@$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME_DYNAMIC) $(OBJS) $(LDLIBS)
else ifeq ($(OSMODE),linux)
	@printf    "Compiling dynamic library: $(NAME_DYNAMIC) -> "
	@$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME_DYNAMIC) $(OBJS) $(LDLIBS)
else
	@printf $(IO_YELLOW)"Unknown platform: needs manual configuration."$(IO_RESET)"\n"
	@printf "You must manually configure the script to build a dynamic library""\n"
endif
	@cp -f $(NAME_DYNAMIC)	$(BINDIR)$(OSMODE)/dynamic/
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(DEPS)
