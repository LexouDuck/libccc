#! This file holds rules to install/uninstall a C library in the appropriate location



.PHONY:\
install #! Installs the libraries/programs (copies them from `./bin/` to `/usr/local/`, typically)
install: $(NAME_STATIC) $(NAME_DYNAMIC)
	@printf $(IO_CYAN)"Installing library: $(NAME)..."$(IO_RESET)"\n"
	@mkdir -p $(INSTALLDIR)/include/
	@mkdir -p $(INSTALLDIR)/lib/
	@$(INSTALL_DATA) $(HDRS)        $(INSTALLDIR)/include/
	@$(INSTALL_DATA) $(NAME_STATIC) $(INSTALLDIR)/lib/
	@$(INSTALL_PROGRAM) $(NAME_DYNAMIC) \
			$(INSTALLDIR)/lib/$(NAME).$(VERSION)$(EXT_LIB_DYNAMIC)
	@ln -sf $(INSTALLDIR)/lib/$(NAME).$(VERSION)$(EXT_LIB_DYNAMIC) \
			$(INSTALLDIR)/lib/$(NAME)$(EXT_LIB_DYNAMIC)
	@printf $(IO_GREEN)"SUCCESS!"$(IO_RESET)"\n"



.PHONY:\
uninstall #! Removes the installed libraries/programs (deletes files in `/usr/local/`, typically)
uninstall:
	@printf $(IO_CYAN)"Uninstalling library: $(NAME)..."$(IO_RESET)"\n"
	@rm -f $(INSTALLDIR)/include/$(HDRS)
	@rm -f $(INSTALLDIR)/lib/$(NAME_STATIC)
	@rm -f $(INSTALLDIR)/lib/$(NAME_DYNAMIC)
	@rm -f $(INSTALLDIR)/lib/$(NAME).$(VERSION)$(EXT_LIB_DYNAMIC)
	@printf $(IO_GREEN)"SUCCESS!"$(IO_RESET)"\n"
