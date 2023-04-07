#! This file stores the main/default targets of the build system



.PHONY:\
all #! Builds all targets (this is the default rule)
all: $(GENERIC_OUTPUTS)
	$(foreach i,$(BUILDMODES),	@$(MAKE) BUILDMODE=$(i) build $(C_NL))



.PHONY:\
re #! Deletes all generated files and rebuilds `all`
re: \
clean \
all \



.PHONY:\
setup #! Performs initial setup steps for the project
setup: \
init \
version \
prereq \
packages \
