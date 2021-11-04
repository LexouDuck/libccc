#! This file stores the main/default targets of the build system



.PHONY:\
all # Builds all targets (this is the default rule)
all: build-$(MODE)



.PHONY:\
re # Deletes all generated files and rebuilds `all`
re: clean-full all
