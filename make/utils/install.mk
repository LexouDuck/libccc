#! This file holds conventional variables to install/uninstall a C program in the appropriate location



#! DESTDIR is a GNU-conventional environment variable, typically set to nothing (ie: root folder)
ifeq ($(DESTDIR),)
	DESTDIR := 
endif
#! PREFIX is a GNU-conventional environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

#! The folder in which to install the library
INSTALLDIR = $(DESTDIR)$(PREFIX)



#! INSTALL is a GNU-conventional environment variable, but if it is not set, then set default value
ifeq ($(INSTALL),)
	INSTALL := install
endif
#! INSTALL_DATA is a GNU-conventional environment variable, but if it is not set, then set default value
ifeq ($(INSTALL_DATA),)
	INSTALL_DATA := $(INSTALL) -c -m 644
endif
#! INSTALL_PROGRAM is a GNU-conventional environment variable, but if it is not set, then set default value
ifeq ($(INSTALL_PROGRAM),)
	INSTALL_PROGRAM := $(INSTALL) -c -m 755
endif
