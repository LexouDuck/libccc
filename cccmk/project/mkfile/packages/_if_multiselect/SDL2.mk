#! External package: SDL2



PACKAGE_SDL2 = SDL2
PACKAGE_SDL2_VERSION := $(shell $(call packages_getversion,$(PACKAGE_SDL2)))
PACKAGE_SDL2_DIR = $(LIBDIR)$(PACKAGE_SDL2)/
PACKAGE_SDL2_BIN = $(PACKAGE_SDL2_DIR)bin/$(OSMODE)/
PACKAGE_SDL2_INCLUDE = $(PACKAGE_SDL2_BIN)include/SDL2/
PACKAGE_SDL2_LINKDIR = $(PACKAGE_SDL2_BIN)bin/
PACKAGE_SDL2_LINKLIB = -lSDL2
PACKAGE_SDL2_LINK = -L$(PACKAGE_SDL2_LINKDIR) $(PACKAGE_SDL2_LINKLIB)
# on MacOS, SDL2 is a framework, so linking is complicated
ifeq ($(OSMODE),macos)
	PACKAGE_SDL2_INCLUDE = $(PACKAGE_SDL2_BIN)SDL2.framework/Headers/
	PACKAGE_SDL2_LINKDIR = $(PACKAGE_SDL2_BIN)
	PACKAGE_SDL2_LINKLIB = -framework SDL2
	PACKAGE_SDL2_LINK = -F$(PACKAGE_SDL2_LINKDIR) $(PACKAGE_SDL2_LINKLIB)
endif



PACKAGE_SDL2_URL = https://www.libsdl.org/release/
PACKAGE_SDL2_PKG = SDL2-$(PACKAGE_SDL2_VERSION).zip
PACKAGE_SDL2_PKG_INSTALL = \
	@$(call print_warning,"Unsupported platform: SDL2 must be configured manually")

ifeq ($(OSMODE),other)
else ifneq ($(filter $(OSMODE), win32 win64),)
	PACKAGE_SDL2_PKG = SDL2-devel-$(PACKAGE_SDL2_VERSION)-mingw.tar.gz
	PACKAGE_SDL2_PKG_INSTALL = \
		tar -xf $(PACKAGE_SDL2_PKG) --directory=$(PACKAGE_SDL2_DIR) ; \
		{ mv -f $(PACKAGE_SDL2_DIR)SDL2-$(PACKAGE_SDL2_VERSION)/* $(PACKAGE_SDL2_DIR) && rmdir $(PACKAGE_SDL2_DIR)SDL2-$(PACKAGE_SDL2_VERSION) ; } ; \
		{ mkdir -p $(PACKAGE_SDL2_DIR)bin/win32/ && mv $(PACKAGE_SDL2_DIR)x86_64-w64-mingw32/* $(PACKAGE_SDL2_DIR)bin/win32/ && rmdir $(PACKAGE_SDL2_DIR)x86_64-w64-mingw32 ; } ; \
		{ mkdir -p $(PACKAGE_SDL2_DIR)bin/win64/ && mv $(PACKAGE_SDL2_DIR)i686-w64-mingw32/*   $(PACKAGE_SDL2_DIR)bin/win64/ && rmdir $(PACKAGE_SDL2_DIR)i686-w64-mingw32   ; } ;
	PACKAGE_SDL2_GETVERSIONS = \
		grep 'mingw.tar.gz'
else ifeq ($(OSMODE),macos)
	PACKAGE_SDL2_PKG = SDL2-$(PACKAGE_SDL2_VERSION).dmg
	PACKAGE_SDL2_PKG_INSTALL = \
		listing=`hdiutil attach $(PACKAGE_SDL2_PKG) | grep Volumes` ; \
		volume=`echo "$$listing" | cut -f 3` ; \
		cp -rf "$$volume"/SDL2.framework $(PACKAGE_SDL2_BIN) ; \
		hdiutil detach `echo "$$listing" | cut -f 1`
	PACKAGE_SDL2_GETVERSIONS = \
		grep '.dmg'
else ifeq ($(OSMODE),linux)
	PACKAGE_SDL2_PKG = SDL2-$(PACKAGE_SDL2_VERSION).zip
	PACKAGE_SDL2_PKG_INSTALL = \
		unzip $(PACKAGE_SDL2_PKG) -d $(PACKAGE_SDL2_BIN) ; \
		cd $(PACKAGE_SDL2_BIN) ; \
		./configure && make && make install
	PACKAGE_SDL2_GETVERSIONS = \
		grep '.zip'
else
$(error Unsupported platform: external package 'SDL2' must be configured manually)
endif



#! The shell command to retrieve and output list of newer versions, if any
package_SDL2_checkupdates = \
	curl --silent $(PACKAGE_SDL2_URL) \
	| grep 'SDL2' \
	| cut -d'"' -f 8 \
	| $(PACKAGE_SDL2_GETVERSIONS) \
	| sort --version-sort \
	| awk -v found=0 '\
	{\
		if (/$(PACKAGE_SDL2_VERSION)/) { found = 1 }\
		else if (found) { found += 1; print; }\
	}' \
	| sed -E 's/SDL2-.*([0-9]+\.[0-9]+\.[0-9]+).*/\1/g' \



.PHONY:\
package-SDL2 #! downloads the package, according to the version number set
package-SDL2:
	@$(call packages_setversion,$(PACKAGE_SDL2),$(PACKAGE_SDL2_VERSION))
	@$(call print_message,"Downloading package: $(PACKAGE_SDL2)@$(PACKAGE_SDL2_VERSION)...")
	@mkdir -p $(PACKAGE_SDL2_BIN)
	@curl $(PACKAGE_SDL2_URL)$(PACKAGE_SDL2_PKG) --progress-bar --output $(PACKAGE_SDL2_PKG)
	@$(PACKAGE_SDL2_PKG_INSTALL)
	@rm -f $(PACKAGE_SDL2_PKG)
	@$(call print_success,"Installed $(PACKAGE_SDL2)@$(PACKAGE_SDL2_VERSION)")



.PHONY:\
update-SDL2 #! updates the package to the latest version
update-SDL2:
	@$(call print_message,"Checking new versions for package: $(PACKAGE_SDL2)...")
	@echo "=> Current version is: $(PACKAGE_SDL2_VERSION)"
	@new_versions=`$(call package_SDL2_checkupdates)` ; \
	if [ -z "$${new_versions}" ]; then \
		printf "Newest version already set.\n" ; \
	else \
		newer_version=`echo "$${new_versions}" | tail -1` ; \
		printf "Found `echo "$${new_versions}" | wc -l | xargs` new versions.\n" ; \
		printf "Newest version is '$${newer_version}'.\n" ; \
		$(MAKE) package-SDL2  PACKAGE_SDL2_VERSION=$$newer_version ; \
	fi
