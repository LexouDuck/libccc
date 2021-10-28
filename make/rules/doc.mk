#! This file holds project-specific rules to generate/build the documentation for the project



#! doxygen command
DOXYGEN = doxygen
#! doxygen command options
DOXYGEN_FLAGS = 

#! doxyrest command
DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest
#! doxyrest command options
DOXYREST_FLAGS = 

#! sphinx-build command
SPHINX = sphinx-build
#! sphinx-build command options
SPHINX_FLAGS = 



.PHONY:\
doc # Generates documentation for libccc
doc:
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
