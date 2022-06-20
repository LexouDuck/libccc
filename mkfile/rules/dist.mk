#! This file holds the rules to prepare distributable archives for release builds



#! The folder path which contains distributable archives
DIST_PATH = $(DISTDIR)
#! The name to give to the distributable archive file
DIST_NAME = $(NAME)-$(VERSION)_$(OSMODE)_$(CPUMODE).zip
#! The filepath of the distributable zip archive to produce when calling 'make dist'
DIST_FILE = $(DIST_PATH)$(DIST_NAME)



#! Shell command used to create a distributable archive file (by default, in .zip format)
#!	@param	$(1)	Folder to put into a distributable archive file
#!	@param	$(2)	Filename of the output archive file
dist_archive = \
	cd $(1) && zip --symlinks -r ../$(2) ./



.PHONY:\
dist-all #! Prepares .zip archives in ./dist for each platform from the contents of the ./bin folder
dist-all:
	@mkdir -p $(DISTDIR)
	$(foreach i,$(OSMODES),	@-$(MAKE) dist-version OSMODE=$(i)$(C_NL))



.PHONY:\
dist #! Creates a .zip distributable according to the current OSMODE, CPUMODE, and LIBMODE
dist: mkdir-dist
	@if [ -f $(DIST_FILE) ]; then \
		$(call print_error,"File already exists: $(DIST_FILE)") ; \
	fi
	@$(call print_message,"Building release (for target: '$(BUILDMODE)_$(OSMODE)_$(CPUMODE)')...")
	@$(MAKE) build-release
	$(eval BUILDMODE = release)
	@if [ -z "`ls $(BINPATH)* `" ] ; \
	then $(call print_error,"Cannot produce distributable archive for target '$(BUILDMODE)_$(OSMODE)_$(CPUMODE)':\n\t-> the bin output folder is empty: '$(BINPATH)'.") ; \
	fi
	@$(call print_message,"Preparing .zip archive: $(DIST_FILE)")
	@rm -rf   $(TEMPDIR)
	@mkdir -p $(TEMPDIR)
	@cp -Rf $(BINPATH)*  $(TEMPDIR)
	@mkdir -p $(TEMPDIR)include
	@for i in $(HDRS) ; do \
		mkdir -p `dirname $(TEMPDIR)include/$$i` ; \
		cp -p $$i $(TEMPDIR)include/$$i ; \
	done
	@$(call dist_archive,$(TEMPDIR),$(DIST_FILE))
	@rm -rf $(TEMPDIR)
	@printf " -> "$(IO_GREEN)"OK!"$(IO_RESET)"\n"



.PHONY:\
mkdir-dist #! Creates the distributable builds folder
mkdir-dist:
	@mkdir -p $(DIST_PATH)

.PHONY:\
clean-dist #! Deletes the distributable builds folder
clean-dist:
	@$(call print_message,"Deleting distributable builds folder...")
	@rm -rf $(DIST_PATH)



.PHONY:\
prereq-dist #! Checks prerequisite installs to distribute build archives of the program
prereq-dist:
	@-$(call check_prereq,'(dist) ZIP archive creator: zip',\
		zip --version,\
		$(call install_prereq,zip))
	@-$(call check_prereq,'(dist) ZIP archive extractor: unzip',\
		unzip --version,\
		$(call install_prereq,unzip))
