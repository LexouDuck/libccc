#! This file holds the rules to prepare distributable archives for release builds



#! The filepath of the distributable zip archive to produce when calling 'make dist'
DISTRIBUTABLE = $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip



.PHONY:\
dist-all #! Prepares .zip archives in ./dist for each platform from the contents of the ./bin folder
dist-all:
	@mkdir -p $(DISTDIR)
	@-$(MAKE) dist-version OSMODE=win32
	@-$(MAKE) dist-version OSMODE=win64
	@-$(MAKE) dist-version OSMODE=linux
	@-$(MAKE) dist-version OSMODE=macos



.PHONY:\
dist #! Creates a .zip distributable according to the current 'OSMODE' and 'LIBMODE'
dist: mkdir-dist
	@if [ -f $(DISTRIBUTABLE) ]; then \
		$(call print_error,"File already exists: $(DISTRIBUTABLE)") ; \
	fi
	@$(MAKE) clean
	@$(call print_message,"Building release (for OSMODE=$(OSMODE))...")
%%if is(type,library):	@$(MAKE) build-release LIBMODE=static
%%if is(type,library):	@$(MAKE) build-release LIBMODE=dynamic
%%if is(type,program):	@$(MAKE) build-release
ifeq ($(wildcard $(BINDIR)$(OSMODE)/*),)
	@$(call print_error,"Cannot produce distributable archive for target '$(OSMODE)':")
	@$(call print_error,"The bin folder is empty: '$(BINDIR)$(OSMODE)/'.")
else
	@$(call print_message,"Preparing .zip archive: $(DISTRIBUTABLE)")
	@rm -rf   $(TEMPDIR)
	@mkdir -p $(TEMPDIR)
	@cp -rf $(BINDIR)$(OSMODE)/*  $(TEMPDIR)
%%if is(type,library):	@mkdir -p $(TEMPDIR)include
%%if is(type,library):	@for i in $(HDRS) ; do \
%%if is(type,library):		mkdir -p `dirname $(TEMPDIR)include/$$i` ; \
%%if is(type,library):		cp -f $(HDRDIR)$$i $(TEMPDIR)include/$$i ; \
%%if is(type,library):	done
	@cd $(TEMPDIR) && zip -r ../$(DISTRIBUTABLE) ./
	@rm -rf $(TEMPDIR)
	@printf " -> "$(IO_GREEN)"OK!"$(IO_RESET)"\n"
endif



.PHONY:\
mkdir-dist #! Creates the distributable builds folder
mkdir-dist:
	@mkdir -p `dirname $(DISTRIBUTABLE)`

.PHONY:\
clean-dist #! Deletes the distributable builds folder
clean-dist:
	@$(call print_message,"Deleting distributable builds folder...")
	@rm -rf `dirname $(DISTRIBUTABLE)`
