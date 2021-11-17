#! This file holds rules to increment the project version number (in the root-level makefile)



#! The current project commit's revision hash code
COMMITREF = $(shell git rev-parse HEAD)

#! The filepath in which to store the version number
VERSIONFILE = VERSION
#! The shell command to generate the version file, if it doesn't exist
make_VERSIONFILE = echo "$(NAME)@$(1).$(2).$(3)-$(COMMITREF)" > $(VERSIONFILE) && cat $(VERSIONFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(VERSIONFILE) ; echo $$?),1)
$(warning NOTE: version file '$(VERSIONFILE)' doesn't exist - creating now...)
$(shell $(call make_VERSIONFILE,0,0,1))
endif
#! The filepath in which to store the version number
VERSIONFULL := $(shell cat $(VERSIONFILE))



#! The project's name, as parsed from the VERSION file
PARSED_NAME      := $(shell echo $(VERSIONFULL) | grep -o '^[^@]*')
#! The project's commit revision hash code, as parsed from the VERSION file
PARSED_COMMITREF := $(shell echo $(VERSIONFULL) | grep -o '[^-]*$')
#! The project's version number, as parsed from the VERSION file
PARSED_VERSION   := $(shell echo $(VERSIONFULL) | cut -d'@' -f 2 | cut -d'-' -f 1)

VERSION_MAJOR := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 1)
VERSION_MINOR := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 2)
VERSION_BUILD := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 3)

#! The current project version number
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_BUILD)



ifneq ($(PARSED_NAME),$(NAME))
$(error Project name mismatch: NAME is "$(NAME)",\
	but version file "$(VERSIONFILE)" has name "$(PARSED_NAME)")
endif

ifneq ($(PARSED_COMMITREF),$(COMMITREF))
#$(info Project commit changed: updating version file "$(VERSIONFILE)"...)
#VERSIONFULL := $(shell $(call make_VERSIONFILE,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_BUILD)))
endif



.PHONY:\
version #! Outputs the current project version number, and updates the VERSION file
version:
	@$(call make_VERSIONFILE,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_BUILD))



.PHONY:\
version-major #! Increments the project major version number (1st of the 3 numbers: X.0.0)
version-major:
	@printf $(IO_CYAN)"Incrementing major version number..."$(IO_RESET)"\n"
	@$(eval VERSION_MAJOR := $(shell echo $$(($(VERSION_MAJOR)+1))))
	@$(eval VERSION_MINOR := 0)
	@$(eval VERSION_BUILD := 0)
	@$(call make_VERSIONFILE,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_BUILD))

.PHONY:\
version-minor #! Increments the project minor version number (2nd of the 3 numbers: 0.X.0)
version-minor:
	@printf $(IO_CYAN)"Incrementing minor version number..."$(IO_RESET)"\n"
	@$(eval VERSION_MINOR := $(shell echo $$(($(VERSION_MINOR)+1))))
	@$(eval VERSION_BUILD := 0)
	@$(call make_VERSIONFILE,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_BUILD))

.PHONY:\
version-build #! Increments the project build number (3rd of the 3 numbers: 0.0.X)
version-build:
	@printf $(IO_CYAN)"Incrementing build version number..."$(IO_RESET)"\n"
	@$(eval VERSION_BUILD := $(shell echo $$(($(VERSION_BUILD)+1))))
	@$(call make_VERSIONFILE,$(VERSION_MAJOR),$(VERSION_MINOR),$(VERSION_BUILD))
