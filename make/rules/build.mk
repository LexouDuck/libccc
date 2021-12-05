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
	@$(call print_warning,"Unknown platform: needs manual configuration.")
	@$(call print_warning,"You must manually configure the script to build a dynamic library")
endif
	@cp -f $(NAME_DYNAMIC)	$(BINDIR)$(OSMODE)/dynamic/
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(DEPS)



.PHONY:\
clean-build #! Deletes all intermediary build-related files
clean-build: \
clean-build-obj \
clean-build-dep \
clean-build-bin \

.PHONY:\
clean-build-obj #! Deletes all .o build object files
clean-build-obj:
	@$(call print_message,"Deleting all build .o files...")
	@rm -f $(TEST_OBJS)

.PHONY:\
clean-build-dep #! Deletes all .d build dependency files
clean-build-dep:
	@$(call print_message,"Deleting all build .d files...")
	@rm -f $(TEST_DEPS)

.PHONY:\
clean-build-bin #! Deletes all build binaries
clean-build-bin:
	@$(call print_message,"Deleting static library: $(NAME_STATIC)")
	@rm -f $(NAME_STATIC)
	@$(call print_message,"Deleting dynamic library: $(NAME_DYNAMIC)")
	@rm -f $(NAME_DYNAMIC)
