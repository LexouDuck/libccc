#! This file holds certain utility variables for interacting with a UNIX shell



#! This allows us to use 'sudo' for certain operations while remaining cross-platform
ifeq ($(OS),Windows_NT)
	SUDO =
else
	SUDO = sudo
endif



#! Shell command used to run a program
ifdef __EMSCRIPTEN__
run = node $(1)
else
run = ./$(1)
endif



#! Makefile function used when passing long lists of arguments, to pass them via a file instead
#	@param 1	The long command-arguments string to pass via file
#	@param 2	The path of the file to create, to store this long command-arguments string
pass_as_file = \
	` echo "$(1)" > "$(2)" && cat "$(2)" `
