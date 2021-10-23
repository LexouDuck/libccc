# This file holds rules to list/debug the contents of the build system



# see https://stackoverflow.com/questions/4219255/how-do-you-get-the-list-of-targets-in-a-makefile
.PHONY:\
list-targets # Displays list of all available targets in this Makefile, sorted in alphabetical order
list-targets:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' \
		| sort \
		| egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
