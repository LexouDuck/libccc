#! This file holds the default values and logic for project build configuration variables



#! Define all possible build modes
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



#! Define all possible library-linking modes
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
%%if is(type,library):
%%if is(type,library):#! Define build target name for static library with appropriate file extensions
%%if is(type,library):NAME_STATIC  = $(NAME).$(LIBEXT_STATIC)
%%if is(type,library):#! Define build target name for dynamic library with appropriate file extensions
%%if is(type,library):NAME_DYNAMIC = $(NAME).$(LIBEXT_DYNAMIC)
%%if is(type,library):#! Define build target name for library with appropriate file extension according to LIBMODE
%%if is(type,library):NAME_LIBMODE = _
%%if is(type,library):ifeq ($(LIBMODE),static)
%%if is(type,library):	NAME_LIBMODE = $(NAME_STATIC)
%%if is(type,library):endif
%%if is(type,library):ifeq ($(LIBMODE),dynamic)
%%if is(type,library):	NAME_LIBMODE = $(NAME_DYNAMIC)
%%if is(type,library):endif



#! Define all possible supported platforms
OSMODES = \
	win32	\
	win64	\
	macos	\
	linux	\
	other	\
# if the OSMODE variable has no value, give it a default value
ifeq ($(OSMODE),)
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
	OSMODE?=other
endif



#! The file extension used for static library files
LIBEXT_STATIC=a

#! The file extension used for dynamic library files
LIBEXT_DYNAMIC=
ifeq ($(OSMODE),other)
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
