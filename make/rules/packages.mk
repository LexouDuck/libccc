#! This file holds rules to build dependencies (libraries, packages, binaries, etc)



#! The file which stores all dependency package version info
PACKAGESFILE = make/lists/packages.txt
#! The shell command to generate the packages list file, if it doesn't exist
make_PACKAGESFILE = $(foreach i,$(PACKAGES), echo "$(i)@0.0.0-?" >> $(PACKAGESFILE) ;)
# if file doesn't exist, create it
ifeq ($(shell test -f $(PACKAGESFILE) ; echo $$?),1)
$(warning NOTE: packages list file '$(PACKAGESFILE)' doesn't exist - creating now...)
$(shell $(call make_PACKAGESFILE))
endif



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
packages # This rule builds/prepares the dependency external packages
packages: $(addprefix package-, $(PACKAGES))



.PHONY:\
update-all # This rule update the dependency external packages to their latest versions
update-all: $(addprefix update-, $(PACKAGES))



# include makefiles for each external package
include $(foreach i,$(PACKAGES), make/packages/$(i).mk)
