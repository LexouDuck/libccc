#! This file holds the default values and logic for project build configuration variables



#! Define all possible build modes
BUILDMODES = \
	debug	\
	release	\
# if the BUILDMODE variable has no value, give it a default value
ifeq ($(strip $(BUILDMODE)),)
	BUILDMODE=debug
else ifeq ($(BUILDMODE),debug)
else ifeq ($(BUILDMODE),release)
else
$(error Invalid value for BUILDMODE, should be `debug` or `release`)
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

#! Define build target name for library, according to current $(LIBMODE)
NAME_LIBMODE = $(NAME_$(LIBMODE))
#! Define build target name for static library with appropriate file extensions
NAME_static = $(NAME).$(LIBEXT_static)
#! Define build target name for dynamic library with appropriate file extensions
NAME_dynamic = $(NAME).$(LIBEXT_dynamic)



UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)
UNAME_P := $(shell uname -p)



#! Define all possible supported target platforms/operating systems
OSMODES = \
	emscripten	\
	windows	\
	macos	\
	linux	\
	other	\
# if the OSMODE variable has no value, give it a default value based on the current platform
ifeq ($(strip $(OSMODE)),)
	OSMODE := other
	ifdef __EMSCRIPTEN__
		OSMODE := emscripten
	else
	ifeq ($(OS),Windows_NT)
		OSMODE := windows
	else
		ifeq ($(UNAME_S),Linux)
			OSMODE := linux
		endif
		ifeq ($(UNAME_S),Darwin)
			OSMODE := macos
		endif
	endif
	endif
	ifeq ($(OSMODE),other)
	_:=$(call print_warning,"Could not estimate the current target platform, defaulting to 'OSMODE = other'...")
	endif
endif



#! Since it is not viable to have/maintain make an exhaustive list of all possible target ASM/CPU architectures, instead we simply use the result of `uname -m`)
CPUMODES = \
	other	\
# if the CPUMODE variable has no value, give it a default value based on the current CPU architecture
ifeq ($(strip $(CPUMODE)),)
	CPUMODE := other
	ifdef __EMSCRIPTEN__
		CPUMODE := wasm-$(if $(findstring 64, $(UNAME_M) $(UNAME_P)),64,32)
	else
		CPUMODE := $(subst _,-,$(UNAME_M))
	endif
	ifeq ($(OSMODE),other)
	_:=$(call print_warning,"Could not estimate the current target CPU architecture, defaulting to 'CPUMODE = other'...")
	endif
endif



#! The file extension used for static library files
LIBEXT_static := a

#! The file extension used for dynamic library files
LIBEXT_dynamic := 
ifeq ($(OSMODE),other)
	LIBEXT_dynamic := 
else ifeq ($(OSMODE),emscripten)
	LIBEXT_dynamic := js
else ifeq ($(OSMODE),windows)
	LIBEXT_dynamic := dll
else ifeq ($(OSMODE),linux)
	LIBEXT_dynamic := so
else ifeq ($(OSMODE),macos)
	LIBEXT_dynamic := dylib
else
$(error Unsupported platform: you must configure the dynamic library file extension your machine uses)
endif
