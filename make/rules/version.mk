# This file holds rules to increment the project version number (in the root-level makefile)

# The filepath in which to store the version number
VERSION_FILE = VERSION

# The complete project version number
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_BUILD)
VERSION_MAJOR := 0
VERSION_MINOR := 8
VERSION_BUILD := 3
# The current commit's revision hash code
COMMIT_REF = $(shell git rev-parse HEAD)



define set_version
	@echo "$(NAME)@$(VERSION)-$(COMMIT_REF)" > $(VERSION_FILE)
	@cat $(VERSION_FILE)
endef



.PHONY:\
version # Outputs the current project version number, and updates the VERSION file
version:
	@$(call set_version)



.PHONY:\
version-major # Increments the project major version number (1st of the 3 numbers: X.0.0)
version-major:
	@$(eval VERSION_MAJOR := $(shell echo $$(($(VERSION_MAJOR)+1))))
	@$(eval VERSION_MINOR := 0)
	@$(eval VERSION_BUILD := 0)
	@$(call set_version)

.PHONY:\
version-minor # Increments the project minor version number (2nd of the 3 numbers: 0.X.0)
version-minor:
	@$(eval VERSION_MINOR := $(shell echo $$(($(VERSION_MINOR)+1))))
	@$(eval VERSION_BUILD := 0)
	@$(call set_version)

.PHONY:\
version-build # Increments the project build number (3rd of the 3 numbers: 0.0.X)
version-build:
	@$(eval VERSION_BUILD := $(shell echo $$(($(VERSION_BUILD)+1))))
	@$(call set_version)
