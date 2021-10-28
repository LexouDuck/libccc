#! This file holds rules to install/uninstall a C library in the appropriate location



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



.PHONY:\
install # Installs the libraries/programs (copies them from `./bin/` to `/usr/local/`, typically)
install: $(NAME_STATIC) $(NAME_DYNAMIC)
	@echo "Installing library: $(NAME)..."
	@mkdir -p $(INSTALLDIR)/include/
	@mkdir -p $(INSTALLDIR)/lib/
	@install -m 644 $(HDRS)        $(INSTALLDIR)/include/
	@install -m 644 $(NAME_STATIC) $(INSTALLDIR)/lib/
	@install -m 755 $(NAME_DYNAMIC) \
			$(INSTALLDIR)/lib/$(NAME).$(VERSION)$(EXT_LIB_DYNAMIC)
	@ln -sf $(INSTALLDIR)/lib/$(NAME).$(VERSION)$(EXT_LIB_DYNAMIC) \
			$(INSTALLDIR)/lib/$(NAME)$(EXT_LIB_DYNAMIC)
	@echo "done"



.PHONY:\
uninstall # Removes the installed libraries/programs (deletes files in `/usr/local/`, typically)
uninstall:
	@echo "Uninstalling library: $(NAME)..."
	@rm -f $(INSTALLDIR)/include/$(HDRS)
	@rm -f $(INSTALLDIR)/lib/$(NAME_STATIC)
	@rm -f $(INSTALLDIR)/lib/$(NAME_DYNAMIC)
	@rm -f $(INSTALLDIR)/lib/$(NAME).$(VERSION)$(EXT_LIB_DYNAMIC)
	@echo "done"
