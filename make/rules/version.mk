#! This file holds rules to increment the project version number (in the root-level makefile)



#! The current project commit's revision hash code
COMMITREF = $(shell git rev-parse HEAD)

#! The filepath in which to store the version number
VERSION_FILE = VERSION
# if file doesn't exist, create it
ifeq ($(shell test -f $(VERSION_FILE) ; echo $$?),1)
$(warning NOTE: version file '$(VERSION_FILE)' doesn't exist - creating now...)
$(shell echo "$(NAME)@0.0.1-$(COMMITREF)" > $(VERSION_FILE) && cat $(VERSION_FILE))
endif

#! The current project version number
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_BUILD)



#! The project name, as parsed from the VERSION file
PARSED_NAME      := $(shell cat $(VERSION_FILE) | cut -d'@' -f 1)
#! The project commit's revision hash code, as parsed from the VERSION file
PARSED_COMMITREF := $(shell cat $(VERSION_FILE) | rev | cut -d'-' -f 1 | rev)
#! The project version number, as parsed from the VERSION file
PARSED_VERSION   := $(shell cat $(VERSION_FILE) | cut -d'@' -f 2 | cut -d'-' -f 1)

VERSION_MAJOR := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 1)
VERSION_MINOR := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 2)
VERSION_BUILD := $(shell echo $(PARSED_VERSION) | cut -d'.' -f 3)

ifneq ($(PARSED_NAME),$(NAME))
$(error Project name mismatch: NAME is "$(NAME)", but version file "$(VERSION_FILE)" has name "$(PARSED_NAME)")
endif

ifneq ($(PARSED_COMMITREF),$(COMMITREF))
#$(warning Project commit changed: current HEAD is "$(COMMITREF)",\
#	but version file "$(VERSION_FILE)" has "$(PARSED_COMMITREF)")
endif



set_version = \
	echo "$(NAME)@$(VERSION)-$(COMMITREF)" > $(VERSION_FILE) \
	&& cat $(VERSION_FILE) \



.PHONY:\
version # Outputs the current project version number, and updates the VERSION file
version:
	@$(call set_version)



.PHONY:\
version-major # Increments the project major version number (1st of the 3 numbers: X.0.0)
version-major:
	@printf $(C_CYAN)"Incrementing major version number..."$(C_RESET)"\n"
	@$(eval VERSION_MAJOR := $(shell echo $$(($(VERSION_MAJOR)+1))))
	@$(eval VERSION_MINOR := 0)
	@$(eval VERSION_BUILD := 0)
	@$(call set_version)

.PHONY:\
version-minor # Increments the project minor version number (2nd of the 3 numbers: 0.X.0)
version-minor:
	@printf $(C_CYAN)"Incrementing minor version number..."$(C_RESET)"\n"
	@$(eval VERSION_MINOR := $(shell echo $$(($(VERSION_MINOR)+1))))
	@$(eval VERSION_BUILD := 0)
	@$(call set_version)

.PHONY:\
version-build # Increments the project build number (3rd of the 3 numbers: 0.0.X)
version-build:
	@printf $(C_CYAN)"Incrementing build version number..."$(C_RESET)"\n"
	@$(eval VERSION_BUILD := $(shell echo $$(($(VERSION_BUILD)+1))))
	@$(call set_version)
