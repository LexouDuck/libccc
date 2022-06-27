#! This file holds certain utility variables for interacting with a UNIX shell



#! This allows us to use 'sudo' for certain operations while remaining cross-platform
ifeq ($(OS),Windows_NT)
	SUDO =
else
	SUDO = sudo
endif



#! This cross-platform function can be used to kill a running process via its name
ifeq ($(OS),Windows_NT)
kill = taskkill -F -IM $(1)
else
kill = sudo pkill $(1)
endif



#! Shell command used to run a program in a cross-platform manner
ifdef __EMSCRIPTEN__
run = node ./$(1)
else
ifneq ($(findstring iPhone,$(shell uname -m)),)
run = ldid -S ./$(1) && ./$(1)
else
run = ./$(1)
endif
endif



#! Shell command used to run a program as a background service
ifneq ($(findstring CYGWIN,$(shell uname -s)),)
daemon = cygstart --hide $(1)
else
daemon = $(1) &
endif
