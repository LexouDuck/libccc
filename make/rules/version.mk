# This file holds rules to increment the project version number (in the root-level makefile)



.PHONY:\
version # Outputs the current project version number
version:
	@echo "$(NAME) v$(VERSION)"



define set_version
	@echo "$(NAME) v$(VERSION)"
	@cat $(MKFILE_PATH) | awk '\
	{\
		if (/^VERSION\>/) { print }\
		else if (/^VERSION_MAJOR/) { print "VERSION_MAJOR := $(VERSION_MAJOR)" }\
		else if (/^VERSION_MINOR/) { print "VERSION_MINOR := $(VERSION_MINOR)" }\
		else if (/^VERSION_BUILD/) { print "VERSION_BUILD := $(VERSION_BUILD)" }\
		else { print }\
	}' > $(MKFILE_PATH).tmp && mv $(MKFILE_PATH).tmp $(MKFILE_PATH)
endef



.PHONY:\
version-major # Increments the project major version number (for significant and breaking changes)
version-major:
	@$(eval VERSION_MAJOR := $(shell echo $$(($(VERSION_MAJOR)+1))))
	@$(eval VERSION_MINOR := 0)
	@$(eval VERSION_BUILD := 0)
	@$(call set_version)

.PHONY:\
version-minor # Increments the project minor version number (for significant non-breaking changes)
version-minor:
	@$(eval VERSION_MINOR := $(shell echo $$(($(VERSION_MINOR)+1))))
	@$(eval VERSION_BUILD := 0)
	@$(call set_version)

.PHONY:\
version-minor # Increments the project minor version number (for significant non-breaking changes)
version-minor:
	@$(eval VERSION_BUILD := $(shell echo $$(($(VERSION_BUILD)+1))))
	@$(call set_version)
