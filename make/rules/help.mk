# This file holds the various rules which document the build system itself

# The char column at which the doc comments should show up
COLUMN_DOC=25



.PHONY:\
help # Displays list of "PHONY" targets, with descriptions                                                                
help:                                                                                                                    
	@cat $(MKFILE_PATH) make/rules/*.mk \
		| awk -v phony=0 '\
			{\
				if (phony)\
				{\
					sub(/#/,"\t-");\
					phony = 0;\
					print "make " $$0;\
				}\
				else if (/^\.PHONY:\\/)\
				{\
					phony = 1;\
				}\
			}' \
		| expand -t$(COLUMN_DOC)
