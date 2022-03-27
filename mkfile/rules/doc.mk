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
docs_folder = $(filter %/$(1)/, $(DOC_OUTPUTS))



#! Shell command: doxygen
DOXYGEN = doxygen
#! Shell command: doxygen options
DOXYGEN_FLAGS = 
#! The configuration file used by doxygen
DOXYGEN_CONFIG = $(DOCDIR)doxygen-config.doxygen

#! Shell command: doxyrest
DOXYREST = $(DOXYREST_DIR)bin/doxyrest
#! Shell command: doxyrest options
DOXYREST_FLAGS = 
#! The installation folder for doxyrest
DOXYREST_DIR = $(DOCDIR)doxyrest/
#! The configuration file used by doxyrest
DOXYREST_CONFIG = $(DOCDIR)doxyrest-config.lua
#! The version number of doxyrest to install with `make prereq`
DOXYREST_VERSION = 2.1.3
#! The link from which to get doxyrest to install  with `make prereq`
DOXYREST_URL = https://github.com/vovkos/doxyrest/releases/download/doxyrest-$(DOXYREST_VERSION)/

#! Shell command to install doxyrest prereq
doxyrest_install = \
{ \
	mkdir -p $(DOXYREST_DIR) && \
	curl -L $(DOXYREST_URL)$(DOXYREST_PACKAGE) --progress-bar --output $(DOXYREST_PACKAGE) && \
	$(call doxyrest_extract) && \
	cp -pf $(DOCDIR)_doxyrest/frame/cfamily/utils.lua $(DOXYREST_DIR)frame/cfamily/utils.lua && \
	cp -pf $(DOCDIR)_doxyrest/sphinx/cpplexer.py      $(DOXYREST_DIR)sphinx/cpplexer.py      && \
	cp -pf $(DOCDIR)_doxyrest/sphinx/doxyrest.py      $(DOXYREST_DIR)sphinx/doxyrest.py      && \
	$(call print_success,"Installed doxyrest (in folder: $(DOXYREST_DIR))") ; \
} ; rm -f $(DOXYREST_PACKAGE)

ifeq ($(OSMODE),other)
doxyrest_install = $(call print_warning,"Unknown platform: doxyrest must be manually installed from https://github.com/vovkos/doxyrest")

else ifeq ($(OSMODE),win32)
DOXYREST_PACKAGE = doxyrest-$(DOXYREST_VERSION)-windows-x86.7z
doxyrest_extract = \
	7z x $(DOXYREST_PACKAGE) -o$(DOXYREST_DIR) \

else ifeq ($(OSMODE),win64)
DOXYREST_PACKAGE = doxyrest-$(DOXYREST_VERSION)-windows-amd64.7z
doxyrest_extract = \
	7z x $(DOXYREST_PACKAGE) -o$(DOXYREST_DIR) \

else ifeq ($(OSMODE),macos)
DOXYREST_PACKAGE = doxyrest-$(DOXYREST_VERSION)-mac.tar.xz
doxyrest_extract = \
	tar -xf $(DOXYREST_PACKAGE) --directory=$(DOXYREST_DIR) && \
	mv -f $(DOXYREST_DIR)doxyrest-$(DOXYREST_VERSION)-mac/* $(DOXYREST_DIR) && \
	rmdir $(DOXYREST_DIR)doxyrest-$(DOXYREST_VERSION)-mac && \
	mv -f $(DOXYREST_DIR)share/doxyrest/* $(DOXYREST_DIR) && \
	rmdir $(DOXYREST_DIR)share/doxyrest && \
	rmdir $(DOXYREST_DIR)share \

else ifeq ($(OSMODE),linux)
DOXYREST_PACKAGE = doxyrest-$(DOXYREST_VERSION)-linux-x86.tar.xz
doxyrest_extract = \
	tar -xf $(DOXYREST_PACKAGE) --directory=$(DOXYREST_DIR) \

else
doxyrest_install = $(call print_failure,"Unknown platform: doxyrest must be manually installed from https://github.com/vovkos/doxyrest")
endif


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
	@# /!\ put any custom XML-fixing code here
	@awk '{ $$0 = gensub(/<\/?computeroutput>/, "``", "g"); print; }' \
		$(call docs_folder,xml)group__libccc__format.xml > \
		$(call docs_folder,xml)group__libccc__format.tmp && mv \
		$(call docs_folder,xml)group__libccc__format.tmp \
		$(call docs_folder,xml)group__libccc__format.xml
	@$(call print_message,"Generating RST documentation...")
	@$(DOXYREST) $(DOXYREST_FLAGS) -c $(DOXYREST_CONFIG) \
		   $(call docs_folder,xml)index.xml \
		-o $(call docs_folder,rst)index.rst
	@# /!\ put any custom RST-fixing code here
	@$(call print_message,"Generating HTML documentation...")
	@ $(SPHINX) $(SPHINX_FLAGS) -c $(SPHINX_CONFIG) -b html \
		$(call docs_folder,rst) \
		$(call docs_folder,html)
	@#$(call print_message,"Generating LaTeX documentation...")
	@#$(SPHINX) $(SPHINX_FLAGS) -c $(SPHINX_CONFIG) -M latexpdf \
		#$(call docs_folder,rst) \
		#$(call docs_folder,pdf)
	@#$(MAKE) -C $(call docs_folder,pdf)latex/ all
	@mv $(call docs_folder,html)page_index.html \
		$(call docs_folder,html)index.html
	@$(call print_success,"Generated documentation (doxyrest + sphinx)")



.PHONY:\
doc-preprocess #! This rule is used to pre-process .h files for the doxygen parser to understand them
doc-preprocess:
	@$(call print_message,"Preprocessing headers for documentation...")
	@mkdir -p ./docs/$(HDRDIR)
	@cp -rf $(HDRDIR)* ./docs/$(HDRDIR)
	@# /!\ put any custom preprocessing code here
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
		$(call doxyrest_install))
	@-$(call check_prereq,'(doc) Sphinx python doc generator',\
		$(SPHINX) --version,\
		$(call install_prereq,sphinx-doc))
	@-$(call check_prereq,'(doc) Lua',\
		lua -v,\
		$(call install_prereq,lua))
	@-$(call check_prereq,'(doc) dot graphviz graph generator',\
		dot -V,\
		$(call install_prereq,graphviz))
	@# TODO: add LaTeX prereq ?
