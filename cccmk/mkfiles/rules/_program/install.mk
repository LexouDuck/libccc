#! This file holds rules to install/uninstall a C program in the appropriate location



.PHONY:\
install #! Installs the libraries/programs (copies them from `./bin/` to `/usr/local/`, typically)
install: $(NAME)
	@$(call print_message,"Installing library: $(NAME)...")
	@mkdir -p $(INSTALLDIR)/bin/
	@$(INSTALL_PROGRAM) $(NAME) $(INSTALLDIR)/bin/$(NAME)
	@$(call print_success,"Installed $(NAME) to $(INSTALLDIR)/bin/")



.PHONY:\
uninstall #! Removes the installed libraries/programs (deletes files in `/usr/local/`, typically)
uninstall:
	@$(call print_message,"Uninstalling library: $(NAME)...")
	@rm -f $(INSTALLDIR)/bin/$(NAME)
	@$(call print_success,"Uninstalled $(NAME) from $(INSTALLDIR)/bin/")
