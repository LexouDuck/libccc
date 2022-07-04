#! This file holds rules to increment the project version number (in the root-level makefile)



#! Project metadata embedded in the version (by default, the date and commit, but it can be "alpha3", "beta", etc)
VERSION_METADATA = $(VERSION_METADATA_DATE)_$(VERSION_METADATA_COMMIT)
VERSION_METADATA_DATE   := $(shell date -u +%Y-%m-%d)
VERSION_METADATA_COMMIT := $(shell $(GIT) rev-parse HEAD)

#! The filepath in which to store the version number
VERSIONFILE = VERSION
#! The shell command to output the version string (takes 3 args, the 3 version numbers)
echo_VERSION = echo "$(NAME)@$(1).$(2).$(3)-$(VERSION_METADATA)"
#! The shell command to update the version file
make_VERSION = $(call echo_VERSION,$(1),$(2),$(3)) > $(VERSIONFILE) && cat $(VERSIONFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(VERSIONFILE) ; echo $$?),1)
_:=$(shell $(call print_warning,"version file '$(VERSIONFILE)' doesn't exist - creating now..."))
_:=$(shell mkdir -p `dirname $(VERSIONFILE)`)
_:=$(shell $(call make_VERSION,0,0,1))
endif
#! The filepath in which to store the version number
VERSIONINFO := $(shell cat $(VERSIONFILE))



REGEXP_NAME     := ^[^@]*
REGEXP_VERSION  := [0-9]+(\.[0-9]+)+
REGEXP_METADATA := (.*)$

#! The project's name, as parsed from the VERSION file
PARSED_NAME     := $(shell echo $(VERSIONINFO) | awk '{ if (match($$0, /$(REGEXP_NAME)/))    { print substr($$0, RSTART, RLENGTH); } }')
#! The project's version number, as parsed from the VERSION file
PARSED_VERSION  := $(shell echo $(VERSIONINFO) | awk '{ if (match($$0, /$(REGEXP_VERSION)/)) { print substr($$0, RSTART, RLENGTH); } }')
#! The project's commit revision hash code, as parsed from the VERSION file
PARSED_METADATA := $(shell echo $(VERSIONINFO) | cut -d'-' -f 2-)

VERSION_MAJOR := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 1)
VERSION_MINOR := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 2)
VERSION_PATCH := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 3)

#! The current project version number
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)



define VERSION_ERRORMESSAGE

The contents of the version file '$(VERSIONFILE)':
$(VERSIONINFO)
The version should follow a semver-like format (semantic versioning):
NAME@X.Y.Z-METADATA
where:
 - NAME is the project name (should be the same as the Makefile variable)
 - X, Y, Z are the version numbers (major, minor, and patch respectively, like in semver)
 - METADATA is project-specific metadata to identify builds (by default, the date and commit rev)
You can learn more about semver here: https://github.com/semver/semver/blob/master/semver.md

endef

ifneq ($(PARSED_NAME),$(NAME))
$(error Project name mismatch: NAME is "$(NAME)", but version file '$(VERSIONFILE)' contains name '$(PARSED_NAME)'.\
	$(VERSION_ERRORMESSAGE))
endif

ifeq ($(shell echo "$(VERSIONINFO)" | grep -E '$(REGEXP_NAME)@$(REGEXP_VERSION)-$(REGEXP_METADATA)'),)
$(error Project version file has invalid format.\
	$(VERSION_ERRORMESSAGE))
endif

#ifneq ($(PARSED_METADATA),$(VERSION_METADATA))
#$(info Project commit changed: updating version file "$(VERSIONFILE)"...)
#VERSIONINFO := $(shell $(call make_VERSION,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_PATCH)))
#endif



.PHONY:\
version #! Outputs the current project version number, and updates the VERSIONFILE
version:
	@$(call make_VERSION,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_PATCH))



.PHONY:\
version-major #! Increments the project major version number (1st of the 3 numbers: X.0.0)
version-major:
	@$(call print_message,"Incrementing major version number...")
	@$(eval VERSION_MAJOR := $(shell echo $$(($(VERSION_MAJOR)+1))))
	@$(eval VERSION_MINOR := 0)
	@$(eval VERSION_PATCH := 0)
	@$(call make_VERSION,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_PATCH))

.PHONY:\
version-minor #! Increments the project minor version number (2nd of the 3 numbers: 0.Y.0)
version-minor:
	@$(call print_message,"Incrementing minor version number...")
	@$(eval VERSION_MINOR := $(shell echo $$(($(VERSION_MINOR)+1))))
	@$(eval VERSION_PATCH := 0)
	@$(call make_VERSION,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_PATCH))

.PHONY:\
version-patch #! Increments the project patch version number (3rd of the 3 numbers: 0.0.Z)
version-patch:
	@$(call print_message,"Incrementing patch version number...")
	@$(eval VERSION_PATCH := $(shell echo $$(($(VERSION_PATCH)+1))))
	@$(call make_VERSION,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_PATCH))
