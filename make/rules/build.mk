#! This file holds C-specific rules to build a library



#! Path of the file which stores the list of header code files
HDRSFILE = make/lists/hdrs.txt
#! The shell command which generates the list of header code files
make_HDRSFILE = find $(HDRDIR) -name "*.h" | sort | sed "s|$(HDRDIR)/||g" > $(HDRSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(HDRSFILE) ; echo $$?),1)
$(warning NOTE: header code list file '$(HDRSFILE)' doesn't exist - creating now...)
$(shell $(call make_HDRSFILE))
endif
#! List of all C header code files
HDRS := $(shell cat $(HDRSFILE))



#! Path of the file which stores the list of source code files
SRCSFILE = make/lists/srcs.txt
#! The shell command which generates the list of source code files
make_SRCSFILE = find $(SRCDIR) -name "*.c" | sort | sed "s|$(SRCDIR)/||g" > $(SRCSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(SRCSFILE) ; echo $$?),1)
$(warning NOTE: source code list file '$(SRCSFILE)' doesn't exist - creating now...)
$(shell $(call make_SRCSFILE))
endif
#! List of all C source code files
SRCS := $(shell cat $(SRCSFILE))



#! Derive list of compiled object files (.o) from list of srcs
OBJS := $(SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS := $(OBJS:.o=.d)

#! GNU conventional variable: List of libraries to link against
LDLIBS = $(foreach i,$(PACKAGES_LINK),$($(i)))

#! GNU conventional variable: List of folders which store header code files
INCLUDES = -I$(HDRDIR) $(foreach i,$(PACKAGES_INCLUDE),-I$($(i)))



.PHONY:\
lists # Create/update the list of source/header files
lists:
	@$(call make_HDRSFILE)
	@$(call make_SRCSFILE)



.PHONY:\
build-debug # Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-debug: MODE = debug
build-debug: CFLAGS += $(CFLAGS_DEBUG)
build-debug: $(NAME_STATIC) $(NAME_DYNAMIC)

.PHONY:\
build-release # Builds the library, in 'release' mode (with debug flags and symbol-info)
build-release: MODE = release
build-release: CFLAGS += $(CFLAGS_RELEASE)
build-release: $(NAME_STATIC) $(NAME_DYNAMIC)



#! Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
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
	@printf $(C_YELLOW)"Unknown platform: needs manual configuration."$(C_RESET)"\n"
	@printf "You must manually configure the script to build a dynamic library""\n"
endif
	@cp -f $(NAME_DYNAMIC)	$(BINDIR)$(OSMODE)/dynamic/
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(DEPS)
