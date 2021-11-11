#! This file holds the rules to prepare distributable archives for release builds



#! The filepath of the distributable zip archive to produce when calling 'make dist'
DISTRIBUTABLE = $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip



.PHONY:\
dist #! Prepares ZIP archives in ./dist for each platform from the contents of the ./bin folder
dist: build-release
	@mkdir -p $(DISTDIR)
	@-$(MAKE) -s dist-version OSMODE=win32
	@-$(MAKE) -s dist-version OSMODE=win64
	@-$(MAKE) -s dist-version OSMODE=linux
	@-$(MAKE) -s dist-version OSMODE=macos



.PHONY:\
dist-version #! Creates one ZIP distributable according to the current 'OSMODE' and 'LIBMODE'
dist-version:
ifeq ($(wildcard $(BINDIR)$(OSMODE)/*),)
	@printf $(C_RED)"ERROR"$(C_RESET)": Cannot produce distributable archive for target '$(OSMODE)'\n"
else
	@printf $(C_CYAN)"Preparing .zip archive: $(DISTRIBUTABLE)"$(C_RESET)"\n"
	@rm -f $(DISTRIBUTABLE)
	@rm -rf   $(TEMPDIR)
	@mkdir -p $(TEMPDIR)
	@cp -rf $(BINDIR)$(OSMODE)/* $(TEMPDIR)
	@zip -r $(DISTRIBUTABLE) $(TEMPDIR)
	@rm -rf $(TEMPDIR)
	@printf " -> "$(C_GREEN)"OK!"$(C_RESET)"\n"
endif
