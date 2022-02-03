#! This file holds the rules to prepare distributable archives for release builds



#! The filepath of the distributable zip archive to produce when calling 'make dist'
DISTRIBUTABLE = $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip



.PHONY:\
dist #! Prepares ZIP archives in ./dist for each platform from the contents of the ./bin folder
dist: build-release
	@mkdir -p $(DISTDIR)
	@-$(MAKE) dist-version OSMODE=win32
	@-$(MAKE) dist-version OSMODE=win64
	@-$(MAKE) dist-version OSMODE=linux
	@-$(MAKE) dist-version OSMODE=macos



#	@$(call print_message,"Building release (for OSMODE=$(OSMODE))...")

.PHONY:\
dist-version #! Creates one ZIP distributable according to the current 'OSMODE' and 'LIBMODE'
dist-version:
ifeq ($(wildcard $(BINDIR)$(OSMODE)/*),)
	@$(call print_error,"Cannot produce distributable archive for target '$(OSMODE)':")
	@$(call print_error,"The bin folder is empty: '$(BINDIR)$(OSMODE)/'.")
else
	@$(call print_message,"Preparing .zip archive: $(DISTRIBUTABLE)")
	@rm -f $(DISTRIBUTABLE)
	@rm -rf   $(TEMPDIR)
	@mkdir -p $(TEMPDIR)
	@cp -rf $(BINDIR)$(OSMODE)/* $(TEMPDIR)
	@zip -r $(DISTRIBUTABLE) $(TEMPDIR)
	@rm -rf $(TEMPDIR)
	@printf " -> "$(IO_GREEN)"OK!"$(IO_RESET)"\n"
endif
