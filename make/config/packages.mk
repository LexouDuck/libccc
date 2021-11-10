#! This file stores project-specific variables relating to package management



#! Define the list of dependency packages for this project
PACKAGES = \



#! The makefile variable name for each packages (typically uppercase)
PACKAGES_VAR = \



#! The shell command to generate an initial packages list file if none exists
make_packageslist = \
	echo $(PACKAGES) \
	| tr -s '[:blank:]' '\n' \
	| awk '{ print $$0 "@0.0.0-" }' \
	> $(PACKAGESLIST)

#! The file which stores all dependency package version info
PACKAGESLIST = make/lists/packages.txt
# if file doesn't exist, create it
ifeq ($(shell test -f $(PACKAGESLIST) ; echo $$?),1)
$(warning NOTE: packages list file '$(PACKAGESLIST)' doesn't exist - creating now...)
$(shell $(make_packageslist))
endif



PACKAGES_VERSION = $(addsuffix _VERSION, $(PACKAGES_VAR))
PACKAGES_DIR     = $(addsuffix _DIR,     $(PACKAGES_VAR))
PACKAGES_BIN     = $(addsuffix _BIN,     $(PACKAGES_VAR))
PACKAGES_INCLUDE = $(addsuffix _INCLUDE, $(PACKAGES_VAR))
PACKAGES_LINKDIR = $(addsuffix _LINKDIR, $(PACKAGES_VAR))
PACKAGES_LINKLIB = $(addsuffix _LINKLIB, $(PACKAGES_VAR))
PACKAGES_LINK    = $(addsuffix _LINK,    $(PACKAGES_VAR))
