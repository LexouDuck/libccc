#!/bin/sh -e



###
### utility functions for logging/io
###

print_verbose() {
if $verbose; then { printf "cccmk: ""\033[34m""verbose""\033[0m: ""$@" ; echo "" ; } >&2 ; fi ; }
print_message() { { printf "cccmk: ""\033[34m""message""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_warning() { { printf "cccmk: ""\033[33m""warning""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_success() { { printf "cccmk: ""\033[32m""success""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_failure() { { printf "cccmk: ""\033[31m""failure""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_error()   { { printf   "cccmk: ""\033[31m""error""\033[0m: ""$@" ; echo "" ; } >&2 ; exit 1 ; }



###
### utility functions for string/array/list manipulation
###

#! Check if a space-separated list contains a certain string
contains()
{
	if [ -t 0 ] && [ $# -gt 1 ]
	then
		echo "$1" | grep -w -q "$2"
	else
		while read line
		do
			echo "$1" | grep -w -q "$line"
		done
	fi
}

#! Keep only certain items from the space-separated list given as input
filter()
{
	filter_inner()
	(
		for i in $2
		do
			$1 "$i" && echo "$i"
		done
	)
	if [ -t 0 ] && [ $# -gt 1 ]
	then
		filter_inner $1 "$2"
	else
		while read line
		do
			filter_inner $1 "$line"
		done
	fi
}



#! Call AWK on a file, modifying it in-place
awk_inplace()
{
	local file="$1"
	local temp="$1.tmp"
	shift 1
	awk "$@" "$file" > "$temp"
	mv "$temp" "$file"
}



###
### utility functions for filesystem operations
###

#! Get a UNIX UTC timestamp for the last modified date of a file
file_timestamp()
{
	if [ -f "$1" ]
	then date -r "$1" '+%m-%d-%Y %H:%M:%S'
	else echo        '??-??-???? ??:??:??'
	fi
}



#! List all regular files contained inside the given folder (no hidden files, nor folders, nor symlinks etc)
list_onlyfiles()
{
	( cd "$1" && ls -ap 2> /dev/null || echo '' ) \
	| grep -v '/' \
	| xargs
}

#! List subfolders of a folder, with no leading prefix (just the name of each folder)
list_subfolders()
{
	( cd "$1" && ls -ap 2> /dev/null || echo '' ) \
	| grep '.*/' \
	| grep -v '^\.*/$' \
	| tr '/' ' ' \
	| xargs 
}
