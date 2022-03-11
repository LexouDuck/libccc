#! This file holds rules to create a desktop GUI application, with relevant embedded metadata, icon, etc



#! The year for this application (used for copyright metadata)
APPYEAR := $(shell . .cccmk && echo $${project_year})
#! The author name for this application (used for copyright metadata)
APPSIGN := $(shell . .cccmk && echo $${project_author})
#! The full name of the application (with spaces, and any other strange characters)
APPNAME = %[name]%
#! The short description of the application
APPDESC = 
#! The filepath of the icon file to associate with this application (ideally, a 512x512 .png image)
APPICON = 

#! The various sizes of application icons to produce from the source $(APPICON)
ICON_SIZES := \
16 \
32 \
64 \
128 \
256 \
512 \

#! The file which stores application metadata (platform-dependent)
APPFILE = 
APPFILE_TEMPLATE = $(MKFILES_DIR)rules/app-info.$(OSMODE)

#! The output filepath of the distributable application (platform-dependent)
APPDIST = $(BINDIR)$(OSMODE)$(APPNAME)
APPFILE = $(BINDIR)$(OSMODE)$(APPNAME)



ifeq ($(OSMODE),)
_:=$(shell $(call print_error,"Unknown platform ($(OSMODE)), cannot embed application metadata"))



else ifeq ($(OSMODE),linux)
APPMETA = $(BINDIR)$(OSMODE)$(APPNAME).desktop
APPDIST = $(BINDIR)$(OSMODE)$(APPNAME)
.PHONY:\
$(APPDIST)
$(APPDIST):
	@cp $(NAME) $(APPDIST)



else ifeq ($(OSMODE),macos)
APPMETA = $(BINDIR)$(OSMODE)$(APPNAME).plist
APPDIST = $(BINDIR)$(OSMODE)$(APPNAME).app
.PHONY:\
$(APPDIST)
$(APPDIST): $(APPDIST)/$(APPNAME).icns
	@rm -rf $(APPDIST)
	@mkdir $(APPDIST)
	@mkdir $(APPDIST)/Contents
	@mkdir $(APPDIST)/Contents/MacOS
	@mkdir $(APPDIST)/Contents/Resources
	@mv $(APPMETA)                 $(APPDIST)/Contents/Info.plist
	@cp $(APPDIST)/$(APPNAME).icns $(APPDIST)/Contents/Resources/$(APPNAME).icns
	@cp $(NAME)                    $(APPDIST)/MacOS/$(APPNAME)
	@echo "APPL` echo "%[name]%" | cut -c1-4 `" > $(APPDIST)/Contents/PkgInfo

$(APPDIST)/$(APPNAME).icns: $(APPICON)
	@rm -rf $(APPDIST)/$(APPNAME).iconset
	@mkdir  $(APPDIST)/$(APPNAME).iconset
	@$(foreach i,$(ICON_SIZES), sips -z $(i) $(i) $(APPICON) --out $(APPDIST)/$(APPNAME).iconset/icon_$(i)x$(i).png ;)
	@iconutil -c icns -o $@ $(APPDIST)/$(APPNAME).iconset
	@rm -r $(APPDIST)/$(APPNAME).iconset



else ifneq ($(filter $(OSMODE), win32 win64),)
APPMETA = $(BINDIR)$(OSMODE)$(APPNAME).rc
APPDIST = $(BINDIR)$(OSMODE)$(APPNAME).exe
.PHONY:\
$(APPDIST)
$(APPDIST):
	@mv $(APPFILE) $(APPMETA)
	@echo '0 ICON "$(APPFILE).ico"' > $(APPMETA).icon
	@windres $(APPMETA)      -O coff -o $(APPFILE).res
	@windres $(APPMETA).icon -O coff -o $(APPFILE).res.icon
	@$(MAKE) NAME='$(APPDIST)' LDFLAGS_EXTRA=' $(APPFILE).res $(APPFILE).icon.res '

$(APPFILE).ico: $(APPICON)
	@mkdir -p $(TEMPDIR)
	@$(foreach i,$(ICON_SIZES), magick convert $(APPICON) -scale $(i) $(TEMPDIR)$(i).png ;)
	@magick convert $(foreach i,$(ICON_SIZES), $(TEMPDIR)$(i).png) $@
	@rm -rf $(TEMPDIR)



else
_:=$(shell $(call print_warning,"Unknown platform ($(OSMODE)), requires manual configuration"))
endif



.PHONY:\
app #! creates a distributable GUI desktop application, with metadata and icon
app: 
	@$(call print_message,"Processing application metadata...")
	@awk \
		-v variables="\
			name=$(NAME);\
			appname=$(APPNAME);\
			description=$(APPDESC);\
			icon=$(APPICON);\
			year=$(APPYEAR);\
			author=$(APPSIGN);\
			version=$(VERSION);\
		" \
		-f '$(MKFILES_DIR)utils/util.awk' \
		-f '$(MKFILES_DIR)utils/template.awk' \
		$(APPFILE_TEMPLATE) > $(APPFILE)
	@$(call print_message,"Creating application bundle...")
	@$(MAKE) $(APPDIST)
	@$(call print_success,"Created application bundle: $@")
