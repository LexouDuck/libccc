#! This file holds project-specific rules to generate/build the documentation for the project



#! Shell command: doxygen
DOXYGEN = doxygen
#! Shell command: doxygen options
DOXYGEN_FLAGS = 

#! Shell command: doxyrest
DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest
#! Shell command: doxyrest options
DOXYREST_FLAGS = 

#! Shell command: sphinx-build
SPHINX = sphinx-build
#! Shell command: sphinx-build options
SPHINX_FLAGS = 



.PHONY:\
doc #! Generates documentation for libccc
doc:
	@$(call print_message,"Generating documentation...")
	@rm -rf $(DOCDIR)xml/*
	@rm -rf $(DOCDIR)rst/*
	@rm -rf $(DOCDIR)man/*
	@rm -rf $(DOCDIR)rtf/*
	@rm -rf $(DOCDIR)pdf/*
	@rm -rf $(DOCDIR)html/*
	@rm -rf $(DOCDIR)latex/*
	@$(DOXYGEN)  $(DOXYGEN_FLAGS)     $(DOCDIR)doxygen-config.doxygen
	@$(DOXYREST) $(DOXYREST_FLAGS) -c $(DOCDIR)doxyrest-config.lua
	@$(SPHINX)   $(SPHINX_FLAGS) -b html $(DOCDIR)rst $(DOCDIR)html -c $(DOCDIR)
	@#$(SPHINX)   $(SPHINX_FLAGS) -M latexpdf $(DOCDIR)rst $(DOCDIR)pdf  -c $(DOCDIR)
	@#$(MAKE) -C $(DOCDIR)pdf/latex/ all
