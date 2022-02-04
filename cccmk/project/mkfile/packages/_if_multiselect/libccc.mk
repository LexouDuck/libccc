#! External package: libccc



PACKAGE_libccc = libccc
PACKAGE_libccc_VERSION := $(shell $(call packages_getversion,$(PACKAGE_libccc)))
PACKAGE_libccc_LIBMODE = static
PACKAGE_libccc_DIR = $(LIBDIR)libccc/
PACKAGE_libccc_BIN = $(PACKAGE_libccc_DIR)bin/$(OSMODE)/$(PACKAGE_libccc_LIBMODE)/
PACKAGE_libccc_INCLUDE = $(PACKAGE_libccc_DIR)hdr/
PACKAGE_libccc_LINKDIR = $(PACKAGE_libccc_BIN)
PACKAGE_libccc_LINKLIB = -lccc
PACKAGE_libccc_LINK = -L$(PACKAGE_libccc_LINKDIR) $(PACKAGE_libccc_LINKLIB)



PACKAGE_libccc_URL = https://github.com/LexouDuck/libccc
PACKAGE_libccc_URL_VERSION = https://raw.githubusercontent.com/LexouDuck/libccc/master/VERSION

PACKAGE_libccc_GITBRANCH = dev



#! The shell command to retrieve and output list of newer versions, if any
package_libccc_checkupdates = \
	curl --silent $(PACKAGE_libccc_URL_VERSION) \
	| cut -d'@' -f 2 \
	| cut -d'-' -f 1 \



.PHONY:\
package-libccc #! prepares the package for building
package-libccc:
	@$(call packages_setversion,$(PACKAGE_libccc),$(PACKAGE_libccc_VERSION))
	@$(call print_message,"Downloading package: $(PACKAGE_libccc)@$(PACKAGE_libccc_VERSION)...")
	@git submodule update --init $(PACKAGE_libccc_DIR)
	@$(call print_message,"Building package: $(PACKAGE_libccc)...")
	@$(MAKE) -C $(PACKAGE_libccc_DIR) build-$(MODE)
	@$(call print_success,"Installed $(PACKAGE_SDL2)@$(PACKAGE_SDL2_VERSION)")



.PHONY:\
update-libccc #! updates the package to the latest version
update-libccc:
	@$(call print_message,"Checking new versions for package: $(PACKAGE_libccc)...")
	@echo "=> Current version is: $(PACKAGE_libccc_VERSION)"
	@cd $(PACKAGE_libccc_DIR) ; \
	if git status | grep -q "HEAD detached" ; then \
		$(call print_warning,"Your git submodule "$$i" is in detached HEAD state.") ; \
		printf "You need to manually go into the submodule folder and do:\n" ; \
		printf "$$ git checkout $(PACKAGE_libccc_GITBRANCH)\n" ; \
		printf "after making sure that you have no uncommitted local working changes.\n" ; \
	else \
		newer_version=`$(call package_libccc_checkupdates)` ; \
		printf "Newest version is '$${newer_version}'.\n" ; \
		git fetch ; \
		git checkout $(PACKAGE_libccc_GITBRANCH) ; \
		cd - ; \
		$(MAKE) package-libccc PACKAGE_libccc_VERSION=$$newer_version ; \
	fi
