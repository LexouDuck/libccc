# This file holds the rules to prepare distributable archives for release builds



.PHONY:\
dist # Prepares ZIP archives in ./dist for each platform from the contents of the ./bin folder
dist: release
	@mkdir -p $(DISTDIR)
	@-$(MAKE) -s dist-version OSMODE=win32
	@-$(MAKE) -s dist-version OSMODE=win64
	@-$(MAKE) -s dist-version OSMODE=linux
	@-$(MAKE) -s dist-version OSMODE=macos



.PHONY:\
dist-version # Creates one ZIP distributable according to the current 'OSMODE' and 'LIBMODE'
dist-version:
ifeq ($(wildcard $(BINDIR)$(OSMODE)/*),)
	@printf $(C_RED)"ERROR"$(C_RESET)": Cannot produce distributable archive for target '$(OSMODE)'\n"
else
	@printf "Preparing .zip archive: "
	@mkdir -p                   $(NAME)-$(VERSION)
	@cp -r $(BINDIR)$(OSMODE)/* $(NAME)-$(VERSION)
	@printf $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip"\n"
	@rm -rf $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip
	@zip -r $(DISTDIR)$(NAME)-$(VERSION)_$(OSMODE).zip $(NAME)-$(VERSION)
	@rm -rf $(NAME)-$(VERSION)
	@printf " -> "$(C_GREEN)"OK!"$(C_RESET)"\n"
endif
