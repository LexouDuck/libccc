#! This file holds rules to install/uninstall a C program in the appropriate location



.PHONY:\
install #! Installs the program (copies files from `./bin/` to `/usr/local/`)
install: $(NAME)
	@$(call print_message,"Installing program: $(NAME)...")
	@$(SUDO) mkdir -p $(INSTALLDIR)/bin/
ifeq ($(INSTALL_SYMLINK),)
	@$(SUDO) $(INSTALL_PROGRAM) $(NAME) \
		$(INSTALLDIR)/bin/$(NAME)
else
	@$(SUDO) $(INSTALL_PROGRAM) $(NAME) \
		$(INSTALLDIR)/bin/$(NAME)-$(VERSION)
	@$(SUDO) ln -sf \
		$(INSTALLDIR)/bin/$(NAME)-$(VERSION) \
		$(INSTALLDIR)/bin/$(NAME)
endif
	@$(call print_success,"Installed $(NAME) to $(INSTALLDIR)/bin/")



.PHONY:\
uninstall #! Removes the installed program (deletes relevant files in `/usr/local/`)
uninstall:
	@$(call print_message,"Uninstalling program: $(NAME)...")
	@$(SUDO) rm -f $(INSTALLDIR)/bin/$(NAME)
	@$(call print_success,"Uninstalled $(NAME) from $(INSTALLDIR)/bin/")
