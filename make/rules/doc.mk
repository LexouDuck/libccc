#! This file holds project-specific rules to generate/build the documentation for the project



#! The list of output formats of the documentation (doubles as list of folders)
DOC_OUTPUTS = \
	xml \
	rst \
	man \
	rtf \
	pdf \
	html \
	latex \



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
doc #! Generates documentation for the project
doc: clean-doc mkdir-doc
	@$(call print_message,"Generating documentation...")
	@$(DOXYGEN)  $(DOXYGEN_FLAGS)     $(DOCDIR)doxygen-config.doxygen
	@#$(DOXYREST) $(DOXYREST_FLAGS) -c $(DOCDIR)doxyrest-config.lua
	@#$(SPHINX)   $(SPHINX_FLAGS) -b html $(DOCDIR)rst $(DOCDIR)html -c $(DOCDIR)
	@#$(SPHINX)   $(SPHINX_FLAGS) -M latexpdf $(DOCDIR)rst $(DOCDIR)pdf  -c $(DOCDIR)
	@#$(MAKE) -C $(DOCDIR)pdf/latex/ all



.PHONY:\
mkdir-doc #! Creates all the build folders in the ./doc folder (according to `DOC_OUTPUTS`)
mkdir-doc:
	@$(call print_message,"Creating documentation build folders...")
	@for i in $(DOC_OUTPUTS); do \
		mkdir -p $(DOCDIR)$${i} ; \
	done

.PHONY:\
clean-doc #! Deletes any previous builds of documentation website in ./doc folder
clean-doc:
	@$(call print_message,"Deleting documentation build folders...")
	@for i in $(DOC_OUTPUTS); do \
		rm -rf $(DOCDIR)$${i} ; \
	done



install_prereq_doxyrest = \


.PHONY:\
prereq-doc #! Checks prerequisite installs to generate the documentation
prereq-doc:
	@-$(call check_prereq,'(doc) Doxygen',\
		$(DOXYGEN) --version,\
		$(call install_prereq,doxygen))
	@-$(call check_prereq,'(doc) Doxyrest',\
		$(DOXYREST) --version,\
		$(call install_prereq_doxyrest))
	@-$(call check_prereq,'(doc) Sphinx python doc generator',\
		$(SPHINX) --version,\
		$(call install_prereq,sphinx-doc))
	@-$(call check_prereq,'(doc) Lua',\
		lua -v,\
		$(call install_prereq,lua))
	@-$(call check_prereq,'(doc) graphviz `dot` graph generator',\
		dot -V,\
		$(call install_prereq,graphviz))
