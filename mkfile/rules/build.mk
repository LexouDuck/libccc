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
		if [ $(PACKAGE_$(i)_LIBMODE) = "dynamic" ] ; then \
			for i in $(PACKAGE_$(i)_LINKDIR)*.$(LIBEXT_dynamic)* ; do \
				cp -Rp "$$i" $(BINPATH)$(1) || $(call print_warning,"No library files to copy from $(PACKAGE_$(i)_LINKDIR)*") ; \
			done ; \
		fi ; )

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



#! Compiles object files from C source files
$(OBJPATH)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: $@ -> "
	@$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Builds the static-link library '.a' binary file for the current target platform
$(BINPATH)static/$(NAME_static): $(OBJSFILE) $(OBJS)
	@rm -f $@
	@mkdir -p $(@D)
	@printf "Compiling static library: $@ -> "
	@$(AR) $(ARFLAGS) $@ $(call objs)
	@$(RANLIB) $(RANLIB_FLAGS) $@ || $(call print_warning,"call to 'ranlib' command failed: $(RANLIB) $(RANLIB_FLAGS) $@")
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@$(call bin_copylibs,static)
	@$(call bin_symlinks,$(BINPATH)static,$(NAME),$(LIBEXT_static))



#! Builds the dynamic-link library file(s) for the current target platform
$(BINPATH)dynamic/$(NAME_dynamic): $(OBJSFILE) $(OBJS)
	@rm -f $@
	@mkdir -p $(@D)
	@printf "Compiling dynamic library: $@ -> "
ifeq ($(OSMODE),other)
	@$(call print_warning,"Unknown platform: needs manual configuration.")
	@$(call print_warning,"You must manually configure the script to build a dynamic library")
endif
ifeq ($(OSMODE),linux)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-Wl,-rpath='$$ORIGIN/'
endif
ifeq ($(OSMODE),macos)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-install_name '@loader_path/$(NAME_dynamic)'
endif
ifeq ($(OSMODE),windows)
ifeq ($(CC),clang)
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-fvisibility=protected
else
	@$(CC) -shared -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-Wl,--output-def,$(BINPATH)dynamic/$(NAME).def \
		-Wl,--out-implib,$(BINPATH)dynamic/$(NAME).lib \
		-Wl,--export-all-symbols
endif
endif
ifeq ($(OSMODE),emscripten)
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(call objs) $(LDLIBS) \
		-s EXPORTED_FUNCTIONS=[_JSON_FromString_Lenient,_JSON_ToString_Minify,_KVT_Delete] \
		-s EXPORTED_RUNTIME_METHODS=[ccall,cwrap,getValue,setValue,stringToUTF8,UTF8ToString,lengthBytesUTF8] \
		-s MODULARIZE
endif
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@$(call bin_copylibs,dynamic)
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
clean-build-obj #! Deletes all .o build object files, for the current TARGETDIR
clean-build-obj:
	@$(call print_message,"Deleting all .o files for target $(TARGETDIR)...")
	$(foreach i,$(OBJS),	@rm -f "$(i)" $(C_NL))

.PHONY:\
clean-build-dep #! Deletes all .d build dependency files, for the current TARGETDIR
clean-build-dep:
	@$(call print_message,"Deleting all .d files for target $(TARGETDIR)...")
	$(foreach i,$(DEPS),	@rm -f "$(i)" $(C_NL))

.PHONY:\
clean-build-bin #! Deletes all build binaries, for the current TARGETDIR
clean-build-bin:
	@$(call print_message,"Deleting binaries in '$(BINPATH)static'...")
	@rm -f $(BINPATH)static/*
	@$(call print_message,"Deleting binaries in '$(BINPATH)dynamic'...")
	@rm -f $(BINPATH)dynamic/*

.PHONY:\
clean-build-lib #! Deletes the built library(ies), for the current TARGETDIR
clean-build-lib:
	@$(call print_message,"Deleting static library: $(BINPATH)static/$(NAME_static)")
	@rm -f $(BINPATH)static/$(NAME_static)
	@$(call print_message,"Deleting dynamic library: $(BINPATH)dynamic/$(NAME_dynamic)")
	@rm -f $(BINPATH)dynamic/$(NAME_dynamic)



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
