#! This file holds the rules to prepare distributable archives for release builds



#! The folder path which contains distributable archives
DIST_PATH = $(DISTDIR)
#! The name to give to the distributable archive file
DIST_NAME = $(NAME)-$(VERSION)_$(OSMODE).zip
#! The filepath of the distributable zip archive to produce when calling 'make dist'
DIST_FILE = $(DIST_PATH)$(DIST_NAME)



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
	@if [ -f $(DIST_FILE) ]; then \
		$(call print_error,"File already exists: $(DIST_FILE)") ; \
	fi
	@$(MAKE) clean
	@$(call print_message,"Building release (for OSMODE=$(OSMODE))...")
	@$(MAKE) build-release LIBMODE=static
	@$(MAKE) build-release LIBMODE=dynamic
ifeq ($(wildcard $(BINOUT)*),)
	@$(call print_error,"Cannot produce distributable archive for target '$(OSMODE)':")
	@$(call print_error,"The bin folder is empty: '$(BINOUT)'.")
else
	@$(call print_message,"Preparing .zip archive: $(DIST_FILE)")
	@rm -rf   $(TEMPDIR)
	@mkdir -p $(TEMPDIR)
	@cp -rf $(BINOUT)*  $(TEMPDIR)
	@mkdir -p $(TEMPDIR)include
	@for i in $(HDRS) ; do \
		mkdir -p `dirname $(TEMPDIR)include/$$i` ; \
		cp -p $(HDRDIR)$$i $(TEMPDIR)include/$$i ; \
	done
	@cd $(TEMPDIR) && zip -r ../$(DIST_FILE) ./
	@rm -rf $(TEMPDIR)
	@printf " -> "$(IO_GREEN)"OK!"$(IO_RESET)"\n"
endif



.PHONY:\
mkdir-dist #! Creates the distributable builds folder
mkdir-dist:
	@mkdir -p $(DIST_PATH)

.PHONY:\
clean-dist #! Deletes the distributable builds folder
clean-dist:
	@$(call print_message,"Deleting distributable builds folder...")
	@rm -rf $(DIST_PATH)
