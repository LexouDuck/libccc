#! This file holds rules to download/update/version all dependency packages



#! The folder which stores makefiles/scripts used for dependency package management
PACKAGESDIR := make/packages/



#! The file which stores all dependency package version info
PACKAGESFILE = $(LISTSDIR)packages.txt
#! The shell command to output the list of packages (from the set of .mk scripts in PACKAGESDIR)
echo_PACKAGESFILE = $(foreach i,$(wildcard $(PACKAGESDIR)*.mk), echo "$(i:$(PACKAGESDIR)%=%)@0.0.0-?" ;)
#! The shell command to generate the packages list file, if it doesn't exist
make_PACKAGESFILE = { $(call echo_PACKAGESFILE) } > $(PACKAGESFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(PACKAGESFILE) ; echo $$?),1)
$(shell $(call print_warning,"packages list file '$(PACKAGESFILE)' doesn't exist - creating now..."))
$(shell mkdir -p $(PACKAGESDIR))
$(shell $(call make_PACKAGESFILE))
endif
#! The raw contents of the packages list file
PACKAGES_INFO := $(shell cat $(PACKAGESFILE))

#! The list of names of each package (according to the packages list file)
PACKAGES := $(shell cat $(PACKAGESFILE) | cut -d '@' -f 1)

#! Here, we define necessary variables for each package
#{
PACKAGES_VERSIONS = $(foreach i,$(PACKAGES),PACKAGE_$(i)_VERSION)
PACKAGES_DIRS     = $(foreach i,$(PACKAGES),PACKAGE_$(i)_DIR)
PACKAGES_BINS     = $(foreach i,$(PACKAGES),PACKAGE_$(i)_BIN)
PACKAGES_INCLUDES = $(foreach i,$(PACKAGES),PACKAGE_$(i)_INCLUDE)
PACKAGES_LINKDIRS = $(foreach i,$(PACKAGES),PACKAGE_$(i)_LINKDIR)
PACKAGES_LINKLIBS = $(foreach i,$(PACKAGES),PACKAGE_$(i)_LINKLIB)
PACKAGES_LINKS    = $(foreach i,$(PACKAGES),PACKAGE_$(i)_LINK)
#}



#! The shell command to parse a version number from the packages list file
#	@param 1	The name of the package whose version number should be parsed
packages_getversion = \
	cat $(PACKAGESFILE) \
	| grep '^$(1)' \
	| cut -d'@' -f 2 \
	| cut -d'-' -f 1 \



#! The shell command to set a version number in the packages list file
#	@param 1	The name of the package whose version number should updated
#	@param 2	The new version number to set for the given package
packages_setversion = \
	cat $(PACKAGESFILE) \
	| awk '\
	{ \
		if (/^$(1)/) { print "$(1)@$(2)-?"; } \
		else { print; } \
	}'  > packages.temp \
	&& mv packages.temp $(PACKAGESFILE)



.PHONY:\
packages #! This rule builds/prepares the dependency external packages
packages: $(addprefix package-, $(PACKAGES))



.PHONY:\
update-all #! This rule update the dependency external packages to their latest versions
update-all: $(addprefix update-, $(PACKAGES))



# include makefiles for each external package
include $(foreach i,$(PACKAGES), $(PACKAGESDIR)$(i).mk)
