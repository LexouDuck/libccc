#! This file holds C-specific rules to build a library



objs = ` cat "$(OBJSFILE)" | tr '\n' ' ' `

#! Path of the file which stores the list of compiled object files
OBJSFILE = $(OBJPATH)objs.txt

#! Derive list of compiled object files (.o) from list of srcs
OBJS := $(SRCS:$(SRCDIR)%.c=$(OBJPATH)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS := $(OBJS:%.o=%.d)

# here we add dependency library linking flags for each package
LDLIBS := $(LDLIBS) \
	$(foreach i,$(PACKAGES), $(PACKAGE_$(i)_LINK))

# here we add include header folders for each package
INCLUDES := $(INCLUDES) \
	$(foreach i,$(PACKAGES), -I$(PACKAGE_$(i)_INCLUDE))

#! Shell command used to copy over dependency libraries from ./lib into ./bin
#! @param	$(1)	The subdirectory within the ./bin target folder
bin_copylibs = \
	mkdir -p $(BINPATH)$(1) ; \
	$(foreach i,$(PACKAGES), \
		for i in $(PACKAGE_$(i)_LINKDIR)* ; do \
			cp -p "$$i" $(BINPATH)$(1) ; \
		done ; )

#! Shell command used to create symbolic links for version-named library binary
#! @param $(1)	path of the binary file (folder, relative to root-level Makefile)
#! @param $(2)	name of the binary file (without version number, and without file extension)
#! @param $(3)	file extension of the binary file
bin_symlinks = \
	cd $(1) \

ifeq ($(OSMODE),macos)
bin_symlinks += \
	&& mv     $(2).$(3)            $(2).$(VERSION).$(3) \
	&& ln -sf $(2).$(VERSION).$(3) $(2).$(VERSION_MAJOR).$(3) \
	&& ln -sf $(2).$(VERSION).$(3) $(2).$(3) \

endif
ifeq ($(OSMODE),linux)
bin_symlinks += \
	&& mv     $(2).$(3)            $(2).$(3).$(VERSION) \
	&& ln -sf $(2).$(3).$(VERSION) $(2).$(3).$(VERSION_MAJOR) \
	&& ln -sf $(2).$(3).$(VERSION) $(2).$(3) \

endif



.PHONY:\
build #! Builds the library, with the default BUILDMODE (typically debug)
build: \
$(BINPATH)static/$(NAME_static) \
$(BINPATH)dynamic/$(NAME_dynamic) \

.PHONY:\
build-debug #! Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-debug:
	@$(MAKE) build BUILDMODE=debug

.PHONY:\
build-release #! Builds the library, in 'release' mode (with optimization flags)
build-release:
	@$(MAKE) build BUILDMODE=release



#! Generates the list of object files
$(OBJSFILE): $(SRCSFILE)
	@mkdir -p $(@D)
	@printf "" > $(OBJSFILE)
	$(foreach i,$(OBJS),	@printf "$(i)\n" >> $(OBJSFILE) $(C_NL))



#! Compiles object files from source files
$(OBJPATH)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: $@ -> "
	@$(CC) -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Builds the static-link library '.a' binary file for the current target platform
$(BINPATH)static/$(NAME_static): $(OBJSFILE) $(OBJS)
	@rm -f $@
	@mkdir -p $(@D)
	@printf "Compiling static library: $@ -> "
	@$(AR) $(ARFLAGS) $@ $(call objs)
	@$(RANLIB) $(RANLIB_FLAGS) $@
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@$(call bin_copylibs)
	@$(call bin_symlinks,$(BINPATH)static,$(NAME),$(LIBEXT_static))



#! Builds the dynamic-link library file(s) for the current target platform
$(BINPATH)dynamic/$(NAME_dynamic): $(OBJSFILE) $(OBJS)
	@rm -f $@
	@mkdir -p $(@D)
	@printf "Compiling dynamic library: $@ -> "
ifeq ($(OSMODE),windows)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-Wl,--output-def,$(NAME).def \
		-Wl,--out-implib,$(NAME).lib \
		-Wl,--export-all-symbols
	@cp -p $(NAME).def $(BINPATH)dynamic/
	@cp -p $(NAME).lib $(BINPATH)dynamic/
else ifeq ($(OSMODE),macos)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-install_name '@loader_path/$(NAME_dynamic)'
else ifeq ($(OSMODE),linux)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-Wl,-rpath='$$ORIGIN/'
else ifeq ($(OSMODE),emscripten)
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-s MODULARIZE \
		-s EXPORTED_FUNCTIONS=[_JSON_FromString_Lenient,_JSON_ToString_Minify,_KVT_Delete] \
		-s EXPORTED_RUNTIME_METHODS=[ccall,cwrap,getValue,setValue,stringToUTF8,UTF8ToString,lengthBytesUTF8]
else
	@$(call print_warning,"Unknown platform: needs manual configuration.")
	@$(call print_warning,"You must manually configure the script to build a dynamic library")
endif
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@$(call bin_copylibs)
	@$(call bin_symlinks,$(BINPATH)dynamic,$(NAME),$(LIBEXT_dynamic))



# The following line is for `.d` dependency file handling
-include $(DEPS)



.PHONY:\
mkdir-build #! Creates all the build folders in the ./bin folder (according to `OSMODES`)
mkdir-build:
	@$(call print_message,"Creating build folders...")
	$(foreach i,$(BUILDMODES),\
	$(foreach os,$(OSMODES),\
	$(foreach libmode,$(LIBMODES),\
	$(foreach cpu,$(CPUMODES),	@mkdir -p $(BINDIR)$(i)_$(os)_$(cpu)/$(libmode)$(C_NL)))))



.PHONY:\
clean-build #! Deletes all intermediary build-related files
clean-build: \
clean-build-obj \
clean-build-dep \
clean-build-bin \
clean-build-lib \

.PHONY:\
clean-build-obj #! Deletes all .o build object files
clean-build-obj:
	@$(call print_message,"Deleting all build .o files...")
	$(foreach i,$(OBJS),	@rm -f "$(i)" $(C_NL))

.PHONY:\
clean-build-dep #! Deletes all .d build dependency files
clean-build-dep:
	@$(call print_message,"Deleting all build .d files...")
	$(foreach i,$(DEPS),	@rm -f "$(i)" $(C_NL))

.PHONY:\
clean-build-lib #! Deletes the built library(ies) in the root project folder
clean-build-lib:
	@$(call print_message,"Deleting static library: $(BINPATH)static/$(NAME_static)")
	@rm -f $(BINPATH)static/$(NAME_static)
	@$(call print_message,"Deleting dynamic library: $(BINPATH)dynamic/$(NAME_dynamic)")
	@rm -f $(BINPATH)dynamic/$(NAME_dynamic)

.PHONY:\
clean-build-bin #! Deletes all build binaries in the ./bin folder
clean-build-bin:
	@$(call print_message,"Deleting builds in '$(BINPATH)static'...")
	@rm -f $(BINPATH)static/*
	@$(call print_message,"Deleting builds in '$(BINPATH)dynamic'...")
	@rm -f $(BINPATH)dynamic/*



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
