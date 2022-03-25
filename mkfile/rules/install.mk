#! This file holds rules to install/uninstall a C library in the appropriate location



.PHONY:\
install #! Installs the library (copies files from `./bin/` to `/usr/local/`, according to LIBMODE)
install: $(NAME_static) $(NAME_dynamic)
	@$(call print_message,"Installing library: $(NAME)...")
	@# install header files
	@$(SUDO) mkdir -p $(INSTALLDIR)/include/
	@for i in $(HDRS) ; do \
		$(SUDO) mkdir -p `dirname $(INSTALLDIR)/include/$$i` ; \
		$(SUDO) $(INSTALL_DATA) $(HDRDIR)$$i $(INSTALLDIR)/include/$$i ; \
	done
	@# install binary files
	@$(SUDO) mkdir -p $(INSTALLDIR)/lib/
ifeq ($(LIBMODE),)
	@$(call print_warning,"No value was set for LIBMODE, nothing was installed.")

else ifeq ($(LIBMODE),static)
ifeq ($(INSTALL_SYMLINK),)
	@$(SUDO) $(INSTALL_DATA) $(NAME_static) \
		$(INSTALLDIR)/lib/$(NAME).$(LIBEXT_static)
else
	@$(SUDO) $(INSTALL_DATA) $(NAME_static) \
		$(INSTALLDIR)/lib/$(NAME).$(VERSION).$(LIBEXT_static)
	@$(SUDO) ln -sf \
		$(INSTALLDIR)/lib/$(NAME).$(VERSION).$(LIBEXT_static) \
		$(INSTALLDIR)/lib/$(NAME).$(LIBEXT_static)
endif
	@$(call print_success,"Installed $(NAME_static) to $(INSTALLDIR)/lib/")

else ifeq ($(LIBMODE),dynamic)
ifeq ($(INSTALL_SYMLINK),)
	@$(SUDO) $(INSTALL_PROGRAM) $(NAME_dynamic) \
		$(INSTALLDIR)/lib/$(NAME).$(LIBEXT_dynamic)
else
	@$(SUDO) $(INSTALL_PROGRAM) $(NAME_dynamic) \
		$(INSTALLDIR)/lib/$(NAME).$(VERSION).$(LIBEXT_dynamic)
	@$(SUDO) ln -sf \
		$(INSTALLDIR)/lib/$(NAME).$(VERSION).$(LIBEXT_dynamic) \
		$(INSTALLDIR)/lib/$(NAME).$(LIBEXT_dynamic)
endif
	@$(call print_success,"Installed $(NAME_dynamic) to $(INSTALLDIR)/lib/ and .h headers in $(INSTALLDIR)/include/")

else
	@$(call print_error,"Invalid value for LIBMODE, should be 'static' or 'dynamic'.")
endif



.PHONY:\
uninstall #! Removes the installed library (deletes relevant files in `/usr/local/`)
uninstall:
	@$(call print_message,"Uninstalling library: $(NAME)...")
	@for i in $(HDRS) ; do \
		$(SUDO) rm -f $(INSTALLDIR)/include/$$i ; \
	done
	@$(SUDO) rm -f $(INSTALLDIR)/lib/$(NAME_static)
	@$(SUDO) rm -f $(INSTALLDIR)/lib/$(NAME).$(VERSION).$(LIBEXT_static)
	@$(SUDO) rm -f $(INSTALLDIR)/lib/$(NAME_dynamic)
	@$(SUDO) rm -f $(INSTALLDIR)/lib/$(NAME).$(VERSION).$(LIBEXT_dynamic)
	@@$(call print_success,"Uninstalled $(NAME) from $(INSTALLDIR)/lib/ and .h headers in $(INSTALLDIR)/include/")
