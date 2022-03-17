#! This file holds C-specific rules to build a library



#! Derive list of compiled object files (.o) from list of srcs
OBJS := $(SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS := $(OBJS:.o=.d)

# here we add dependency library linking flags for each package
LDLIBS := $(LDLIBS) \
	$(foreach i,$(PACKAGES), $(PACKAGE_$(i)_LINK))

# here we add include header folders for each package
INCLUDES := $(INCLUDES) \
	$(foreach i,$(PACKAGES), -I$(PACKAGE_$(i)_INCLUDE))

#! Shell command used to copy over libraries from ./lib into ./bin
#! @param $(1)	file extension glob
copylibs = $(foreach i,$(PACKAGES), \
	if [ "$(PACKAGE_$(i)_LIBMODE)" = "dynamic" ] ; then \
		for i in $(PACKAGE_$(i)_LINKDIR)*.$(LIBEXT_dynamic) ; do \
			cp -p "$$i" $(BINDIR)$(OSMODE)/ ; \
		done ; \
	fi ; )



.PHONY:\
build-debug #! Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-debug: MODE = debug
build-debug: $(NAME_static) $(NAME_dynamic)

.PHONY:\
build-release #! Builds the library, in 'release' mode (with optimization flags)
build-release: MODE = release
build-release: $(NAME_static) $(NAME_dynamic)



#! Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: $@ -> "
	@$(CC) -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Builds the static-link library '.a' binary file for the current target platform
$(NAME_static): $(OBJS)
	@printf "Compiling static library: $@ -> "
	@$(AR) $(ARFLAGS) $@ $(OBJS)
	@$(RANLIB) $(RANLIB_FLAGS) $@
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@mkdir -p $(BINDIR)$(OSMODE)/static/
	@cp -p $@ $(BINDIR)$(OSMODE)/static/
	@$(call copylibs)



#! Builds the dynamic-link library file(s) for the current target platform
$(NAME_dynamic): $(OBJS)
	@printf "Compiling dynamic library: $@ -> "
ifeq ($(OSMODE),$(filter $(OSMODE), win32 win64))
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) \
		-Wl,--output-def,$(NAME).def \
		-Wl,--out-implib,$(NAME).lib \
		-Wl,--export-all-symbols
	@mkdir -p          $(BINDIR)$(OSMODE)/dynamic/
	@cp -p $(NAME).def $(BINDIR)$(OSMODE)/dynamic/
	@cp -p $(NAME).lib $(BINDIR)$(OSMODE)/dynamic/
else ifeq ($(OSMODE),macos)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) \
		-install_name '@loader_path/$@'
else ifeq ($(OSMODE),linux)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) \
		-Wl,-rpath='$$ORIGIN/'
else
	@$(call print_warning,"Unknown platform: needs manual configuration.")
	@$(call print_warning,"You must manually configure the script to build a dynamic library")
endif
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@mkdir -p $(BINDIR)$(OSMODE)/dynamic/
	@cp -p $@ $(BINDIR)$(OSMODE)/dynamic/
	@$(call copylibs)



# The following line is for `.d` dependency file handling
-include $(DEPS)



.PHONY:\
mkdir-build #! Creates all the build folders in the ./bin folder (according to `OSMODES`)
mkdir-build:
	@$(call print_message,"Creating build folders...")
	@$(foreach i,$(OSMODES), mkdir -p $(BINDIR)$(i)/static  ; )
	@$(foreach i,$(OSMODES), mkdir -p $(BINDIR)$(i)/dynamic ; )



.PHONY:\
clean-build #! Deletes all intermediary build-related files
clean-build: \
clean-build-obj \
clean-build-dep \
clean-build-lib \
clean-build-bin \

.PHONY:\
clean-build-obj #! Deletes all .o build object files
clean-build-obj:
	@$(call print_message,"Deleting all build .o files...")
	@rm -f $(OBJS)

.PHONY:\
clean-build-dep #! Deletes all .d build dependency files
clean-build-dep:
	@$(call print_message,"Deleting all build .d files...")
	@rm -f $(DEPS)

.PHONY:\
clean-build-lib #! Deletes the built library(ies) in the root project folder
clean-build-lib:
	@$(call print_message,"Deleting static library: $(NAME_static)")
	@rm -f $(NAME_static)
	@$(call print_message,"Deleting dynamic library: $(NAME_dynamic)")
	@rm -f $(NAME_dynamic)

.PHONY:\
clean-build-bin #! Deletes all build binaries in the ./bin folder
clean-build-bin:
	@$(call print_message,"Deleting builds in '$(BINDIR)$(OSMODE)/static'...")
	@rm -f $(BINDIR)$(OSMODE)/static/*
	@$(call print_message,"Deleting builds in '$(BINDIR)$(OSMODE)/dynamic'...")
	@rm -f $(BINDIR)$(OSMODE)/dynamic/*



.PHONY:\
prereq-build #! Checks prerequisite installed tools to build a library
prereq-build:
	@-$(call check_prereq,'(build) C compiler: $(CC)',\
		$(CC) --version,\
		$(call install_prereq,$(CC)))
	@-$(call check_prereq,'(build) C archiver: $(AR)',\
		which $(AR),\
		$(call install_prereq,binutils))
	@-$(call check_prereq,'(build) C archive symbol table tool: $(RANLIB)',\
		which $(RANLIB),\
		$(call install_prereq,binutils))
