#! This file holds project-specific rules to generate/build the documentation for the project



#! The filepath of the doxyrest executable
DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest



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
	@doxygen $(DOCDIR)doxygen-config.doxygen
	@$(DOXYREST) -c $(DOCDIR)doxyrest-config.lua
	@sphinx-build -b html $(DOCDIR)rst $(DOCDIR)html -c $(DOCDIR)
	@#sphinx-build -M latexpdf $(DOCDIR)rst $(DOCDIR)pdf  -c $(DOCDIR)
	@#$(MAKE) -C $(DOCDIR)pdf/latex/ all
