#! This file holds certain utility variables for interacting with a UNIX shell



#! This allows us to use 'sudo' for certain operations while remaining cross-platform
ifeq ($(OS),Windows_NT)
	SUDO =
else
	SUDO = sudo
endif
