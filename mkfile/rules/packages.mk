#! This file holds rules to download/update/version all dependency packages



#! The folder which stores makefiles/scripts used for dependency package management
PACKAGESDIR := $(MKFILES_DIR)packages/



#! The file which stores all dependency package version info
PACKAGESFILE = $(LISTSDIR)packages.txt
#! The shell command to output the list of packages (from the set of .mk scripts in PACKAGESDIR)
echo_PACKAGESFILE = $(foreach i,$(wildcard $(PACKAGESDIR)*.mk), echo "$(i:$(PACKAGESDIR)%.mk=%)@0.0.0-?" ;)
#! The shell command to generate the packages list file, if it doesn't exist
make_PACKAGESFILE = { $(call echo_PACKAGESFILE) } > $(PACKAGESFILE) && cat $(PACKAGESFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(PACKAGESFILE) ; echo $$?),1)
_:=$(shell $(call print_warning,"packages list file '$(PACKAGESFILE)' doesn't exist - creating now..."))
_:=$(shell mkdir -p `dirname $(PACKAGESFILE)`)
_:=$(shell $(call make_PACKAGESFILE))
_:=$(shell mkdir -p $(PACKAGESDIR))
endif
#! The raw contents of the packages list file
PACKAGES_INFO := $(shell cat $(PACKAGESFILE))

#! The list of names of each package (according to the packages list file)
PACKAGES := $(shell cat $(PACKAGESFILE) | cut -d '@' -f 1)



#! There are some PHONY rules that a package mkfile script should define:
#{
# make package-% : installs the package into its folder
# make update-%  : updates the package to its latest available version
#}
#! In addition to these rules, here is the list of variables that a package mkfile script should define:
#{
# PACKAGE_%_VERSION : the version number of the package
# PACKAGE_%_LIBMODE : the method of library linking: can be either 'static' or 'dynamic'
# PACKAGE_%_DIR     : the directory in which this package is
# PACKAGE_%_BIN     : the directory in which the library binaries are stored
# PACKAGE_%_INCLUDE : the directory/ies to include (without the -I prefix)
# PACKAGE_%_LINKDIR : the directory/ies to add to library search path (without the -L prefix)
# PACKAGE_%_LINKLIB : the library name, as it is written for linking (including the -l prefix)
# PACKAGE_%_LINK    : both LINKDIR and LINKLIB variables together: `-L$(PACKAGE_%_LINKDIR) $(PACKAGE_%_LINKLIB)`
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
	| awk \
	-v package="$(1)" \
	-v version="$(2)" \
	'{ \
		if ($$0 ~ "^" package) \
		{ print package "@" version "-?"; } \
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
ifneq ($(strip $(PACKAGES)),)
include $(foreach i,$(PACKAGES), $(PACKAGESDIR)$(i).mk)
endif
