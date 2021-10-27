#! This file holds rules to install/uninstall a C library in the appropriate location



#! The folder in which to install to library files
INSTALL_DIR = /usr/local/lib/



.PHONY:\
install # Installs the libraries/programs (copies them from `./bin/` to `/usr/local/`, typically)
install:
	@cp    $(BINDIR)$(OSMODE)/static/$(NAME_STATIC)           $(INSTALL_DIR)$(NAME).$(VERSION).$(LIBEXT_STATIC)
	@cp    $(BINDIR)$(OSMODE)/dynamic/$(NAME_DYNAMIC)         $(INSTALL_DIR)$(NAME).$(VERSION).$(LIBEXT_DYNAMIC)
	@ln -s $(INSTALL_DIR)$(NAME).$(VERSION).$(LIBEXT_STATIC)  $(INSTALL_DIR)$(NAME).$(LIBEXT_STATIC)
	@ln -s $(INSTALL_DIR)$(NAME).$(VERSION).$(LIBEXT_DYNAMIC) $(INSTALL_DIR)$(NAME).$(LIBEXT_DYNAMIC)



.PHONY:\
uninstall # Removes the installed libraries/programs (deletes files in `/usr/local/`, typically)
uninstall:
	@printf "Removing the following files:\n"
	@find $(INSTALL_DIR) -name "$(NAME).*" -print -delete
