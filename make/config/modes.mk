# This file holds the default values and logic for project build configuration variables



# Define all possible build modes
MODES = \
	debug	\
	release	\
# if the MODE variable has no value, give it a default value
ifeq ($(MODE),)
	MODE=debug
else ifeq ($(MODE),debug)
else ifeq ($(MODE),release)
else
$(error Invalid value for MODE, should be `debug` or `release`)
endif



# Define all possible library-linking modes
LIBMODES = \
	static	\
	dynamic	\
# if the LIBMODE variable has no value, give it a default value
ifeq ($(LIBMODE),)
	LIBMODE=static
else ifeq ($(LIBMODE),static)
else ifeq ($(LIBMODE),dynamic)
else
$(error Invalid value for LIBMODE, should be `static` or `dynamic`)
endif

# Define build target names with appropriate file extensions
NAME_STATIC  = $(NAME).$(LIBEXT_STATIC)
NAME_DYNAMIC = $(NAME).$(LIBEXT_DYNAMIC)
NAME_LIBMODE = _
ifeq ($(LIBMODE),static)
	NAME_LIBMODE = $(NAME_STATIC)
endif
ifeq ($(LIBMODE),dynamic)
	NAME_LIBMODE = $(NAME_DYNAMIC)
endif



# Define all possible supported platforms
OSMODES = \
	win32	\
	win64	\
	macos	\
	linux	\
	other	\
# if the OSMODE variable has no value, give it a default value
ifeq ($(OSMODE),)
	OSMODE=other
	ifeq ($(OS),Windows_NT)
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			OSMODE=win32
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			OSMODE=win64
		endif
	else
		UNAME_S = $(shell uname -s)
		ifeq ($(UNAME_S),Linux)
			OSMODE=linux
		endif
		ifeq ($(UNAME_S),Darwin)
			OSMODE=macos
		endif
	endif
endif