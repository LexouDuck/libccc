#! This file holds conventional variables to install/uninstall a C program in the appropriate location



#! DESTDIR is a GNU-conventional environment variable, typically set to nothing (ie: root folder)),)
DESTDIR ?= 

#! PREFIX is a GNU-conventional environment variable, but if it is not set, then set default value
PREFIX ?= /usr/local

#! The folder in which to install the library
INSTALLDIR = $(DESTDIR)$(PREFIX)



#! INSTALL is a GNU-conventional environment variable, but if it is not set, then set default value
INSTALL ?= install

#! INSTALL_DATA is a GNU-conventional environment variable, but if it is not set, then set default value
INSTALL_DATA ?= $(INSTALL) -c -m 644

#! INSTALL_PROGRAM is a GNU-conventional environment variable, but if it is not set, then set default value
INSTALL_PROGRAM ?= $(INSTALL) -c -m 755



#! If not empty, then the 'make install' rule will use symlinks when installing, so as to allow multiple coexisting versions
INSTALL_SYMLINK = true
