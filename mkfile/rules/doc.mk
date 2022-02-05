#! This file holds project-specific rules to generate/build the documentation for the project



#! The list of output formats of the documentation (doubles as list of folders)
DOC_OUTPUTS = \
	./docs/man/ \
	./docs/rtf/ \
	./docs/pdf/ \
	./docs/latex/ \
	./docs/html/ \
	./docs/xml/ \
	./docs/rst/ \

#! Simple function to get a doc output folder from the `DOC_OUTPUTS` list
DOC_OUTPUT = $(filter %/$(1)/, $(DOC_OUTPUTS))



#! Shell command: doxygen
DOXYGEN = doxygen
#! Shell command: doxygen options
DOXYGEN_FLAGS = 
#! The configuration file used by doxygen
DOXYGEN_CONFIG = $(DOCDIR)doxygen-config.doxygen

#! Shell command: doxyrest
DOXYREST = $(DOCDIR)_doxyrest/bin/doxyrest
#! Shell command: doxyrest options
DOXYREST_FLAGS = 
#! The configuration file used by doxyrest
DOXYREST_CONFIG = $(DOCDIR)doxyrest-config.lua

#! Shell command: sphinx-build
SPHINX = sphinx-build
#! Shell command: sphinx-build options
SPHINX_FLAGS = 
#! The configuration file used by sphinx
SPHINX_CONFIG = $(DOCDIR)#conf.py



.PHONY:\
doc #! Generates documentation for the project
doc: \
	clean-doc \
	mkdir-doc \
	doc-base \
	doc-html \

.PHONY:\
doc-base #! Generates documentation for the project (doxygen)
doc-base: doc-preprocess
	@$(call print_message,"Generating HTML + RTF + MAN + LaTeX documentation...")
	@(cat $(DOXYGEN_CONFIG) ; \
		echo "PROJECT_NUMBER = $(VERSION)" ; \
		echo "ENABLED_SECTIONS = DOXYGEN" ; \
		echo "GENERATE_HTML = YES" ; \
		echo "GENERATE_XML = NO" ; \
		echo "GENERATE_RTF = YES" ; \
		echo "GENERATE_MAN = YES" ; \
		echo "GENERATE_LATEX = YES" ; \
		echo "GENERATE_DOCBOOK = YES" ) \
		| $(DOXYGEN) $(DOXYGEN_FLAGS) -
	@$(call print_success,"Generated documentation (doxygen)")

.PHONY:\
doc-html #! Generates documentation for the project (doxyrest + sphinx)
doc-html: doc-preprocess
	@$(call print_message,"Generating XML documentation...")
	@# run it a second time, only to generate XML output for doxyrest
	@(cat $(DOXYGEN_CONFIG) ; \
		echo "PROJECT_NUMBER = $(VERSION)" ; \
		echo "ENABLED_SECTIONS = DOXYREST" ; \
		echo "GENERATE_HTML = NO" ; \
		echo "GENERATE_XML = YES" ; \
		echo "GENERATE_RTF = NO" ; \
		echo "GENERATE_MAN = NO" ; \
		echo "GENERATE_LATEX = NO" ; \
		echo "GENERATE_DOCBOOK = NO" ) \
		| $(DOXYGEN) $(DOXYGEN_FLAGS) -
	@awk '{ $$0 = gensub(/<\/?computeroutput>/, "``", "g"); print; }' \
		$(call DOC_OUTPUT,xml)group__libccc__format.xml > \
		$(call DOC_OUTPUT,xml)group__libccc__format.tmp && mv \
		$(call DOC_OUTPUT,xml)group__libccc__format.tmp \
		$(call DOC_OUTPUT,xml)group__libccc__format.xml
	@$(call print_message,"Generating RST documentation...")
	@$(DOXYREST) $(DOXYREST_FLAGS) -c $(DOXYREST_CONFIG) \
		   $(call DOC_OUTPUT,xml)index.xml \
		-o $(call DOC_OUTPUT,rst)index.rst
	@$(call print_message,"Generating HTML documentation...")
	@ $(SPHINX) $(SPHINX_FLAGS) -c $(SPHINX_CONFIG) -b html \
		$(call DOC_OUTPUT,rst) \
		$(call DOC_OUTPUT,html)
	@#$(call print_message,"Generating LaTeX documentation...")
	@#$(SPHINX) $(SPHINX_FLAGS) -c $(SPHINX_CONFIG) -M latexpdf \
		#$(call DOC_OUTPUT,rst) \
		#$(call DOC_OUTPUT,pdf)
	@#$(MAKE) -C $(call DOC_OUTPUT,pdf)latex/ all
	@mv $(call DOC_OUTPUT,html)page_index.html \
		$(call DOC_OUTPUT,html)index.html
	@$(call print_success,"Generated documentation (doxyrest + sphinx)")



.PHONY:\
doc-preprocess #! This rule is used to pre-process .h files for the doxygen parser to understand them
doc-preprocess:
	@$(call print_message,"Preprocessing headers for documentation...")
	@mkdir -p ./docs/$(HDRDIR)
	@cp -rf $(HDRDIR)* ./docs/$(HDRDIR)
	@for i in $(addprefix ./docs/$(HDRDIR), $(filter libccc/monad/%.h, $(HDRS))) ; do \
		awk '/^#define/ { gsub(/\(T\)/, "<T>"); } { print; }' $$i > $$i.tmp && mv $$i.tmp $$i ; \
	done
	@$(call print_success,"Successfully pre-processed header files")



.PHONY:\
mkdir-doc #! Creates all the build folders in the ./doc folder (according to `DOC_OUTPUTS`)
mkdir-doc:
	@$(call print_message,"Creating documentation build folders...")
	@$(foreach i,$(DOC_OUTPUTS), mkdir -p $(i) ;)

.PHONY:\
clean-doc #! Deletes any previous builds of documentation website in ./doc folder
clean-doc:
	@$(call print_message,"Deleting documentation build folders...")
	@$(foreach i,$(DOC_OUTPUTS), rm -rf $(i) ;)

	

.PHONY:\
prereq-doc #! Checks prerequisite installs to generate the documentation
prereq-doc:
	@-$(call check_prereq,'(doc) Doxygen',\
		$(DOXYGEN) --version,\
		$(call install_prereq,doxygen))
	@-$(call check_prereq,'(doc) Doxyrest',\
		$(DOXYREST) --version,\
		$(call print_error,"doxyrest must be manually installed from https://github.com/vovkos/doxyrest"))
	@-$(call check_prereq,'(doc) Sphinx python doc generator',\
		$(SPHINX) --version,\
		$(call install_prereq,sphinx-doc))
	@-$(call check_prereq,'(doc) Lua',\
		lua -v,\
		$(call install_prereq,lua))
	@-$(call check_prereq,'(doc) graphviz `dot` graph generator',\
		dot -V,\
		$(call install_prereq,graphviz))
	@# TODO: add LaTeX prereq ?
