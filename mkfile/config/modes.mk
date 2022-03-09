#! This file holds the default values and logic for project build configuration variables



#! Define all possible build modes
MODES = \
	debug	\
	release	\
# if the MODE variable has no value, give it a default value
ifeq ($(strip $(MODE)),)
	MODE=debug
else ifeq ($(MODE),debug)
else ifeq ($(MODE),release)
else
$(error Invalid value for MODE, should be `debug` or `release`)
endif



#! Define all possible library-linking modes
LIBMODES = \
	static	\
	dynamic	\
# if the LIBMODE variable has no value, give it a default value
ifeq ($(strip $(LIBMODE)),)
	LIBMODE=static
else ifeq ($(LIBMODE),static)
else ifeq ($(LIBMODE),dynamic)
else
$(error Invalid value for LIBMODE, should be `static` or `dynamic`)
endif

#! Define build target name for static library with appropriate file extensions
NAME_STATIC  = $(NAME).$(LIBEXT_STATIC)
#! Define build target name for dynamic library with appropriate file extensions
NAME_DYNAMIC = $(NAME).$(LIBEXT_DYNAMIC)
#! Define build target name for library with appropriate file extension according to LIBMODE
NAME_LIBMODE = _
ifeq ($(LIBMODE),static)
	NAME_LIBMODE = $(NAME_STATIC)
endif
ifeq ($(LIBMODE),dynamic)
	NAME_LIBMODE = $(NAME_DYNAMIC)
endif


#! Define all possible supported platforms
OSMODES = \
	win32	\
	win64	\
	macos	\
	linux	\
	other	\
# if the OSMODE variable has no value, give it a default value based on the current platform
ifeq ($(strip $(OSMODE)),)
	ifdef __EMSCRIPTEN__
		OSMODE=emscripten
	OSMODE = other
	else ifeq ($(OS),Windows_NT)
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			OSMODE = win32
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			OSMODE = win64
		endif
	else
		UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Linux)
			OSMODE = linux
		endif
		ifeq ($(UNAME_S),Darwin)
			OSMODE = macos
		endif
	endif
	ifeq ($(OSMODE),other)
	_:=$(call print_warning,"Could not estimate the current target platform, defaulting to 'OSMODE = other'...")
	endif
endif



#! The file extension used for static library files
LIBEXT_STATIC=a

#! The file extension used for dynamic library files
LIBEXT_DYNAMIC=
ifeq ($(OSMODE),other)
	LIBEXT_DYNAMIC=
else ifeq ($(OSMODE),emscripten)
	LIBEXT_DYNAMIC=
else ifeq ($(OSMODE),win32)
	LIBEXT_DYNAMIC=dll
else ifeq ($(OSMODE),win64)
	LIBEXT_DYNAMIC=dll
else ifeq ($(OSMODE),linux)
	LIBEXT_DYNAMIC=so
else ifeq ($(OSMODE),macos)
	LIBEXT_DYNAMIC=dylib
else
$(error Unsupported platform: you must configure the dynamic library file extension your machine uses)
endif
