#! This file stores project-specific variables relating to package management



#! Define the list of dependency packages for this project
PACKAGES = \



#! The makefile variable prefix for each package (typically, the uppercase equivalent)
PACKAGESVARS = \



PACKAGES_VERSION = $(addsuffix _VERSION, $(PACKAGESVARS))
PACKAGES_DIR     = $(addsuffix _DIR,     $(PACKAGESVARS))
PACKAGES_BIN     = $(addsuffix _BIN,     $(PACKAGESVARS))
PACKAGES_INCLUDE = $(addsuffix _INCLUDE, $(PACKAGESVARS))
PACKAGES_LINKDIR = $(addsuffix _LINKDIR, $(PACKAGESVARS))
PACKAGES_LINKLIB = $(addsuffix _LINKLIB, $(PACKAGESVARS))
PACKAGES_LINK    = $(addsuffix _LINK,    $(PACKAGESVARS))
