# This file holds a cross-platform SUDO variable, for actions which necessitate privileges



#! This allows us to use 'sudo' for certain operations while remaining cross-platform
ifeq ($(OS),Windows_NT)
	SUDO =
else
	SUDO = sudo
endif
