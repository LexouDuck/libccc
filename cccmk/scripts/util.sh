#!/bin/sh -e



###
### utility functions for logging/io
###

ansi_esc() { printf "\033[""$@""m" ; }

io_reset="`   ansi_esc 0`"
io_red="`     ansi_esc 31`"
io_green="`   ansi_esc 32`"
io_yellow="`  ansi_esc 33`"
io_blue="`    ansi_esc 34`"
io_magenta="` ansi_esc 35`"
io_cyan="`    ansi_esc 36`"

print_verbose() {
if $verbose; then { printf "cccmk: %s%s%s%s\n" "$io_blue"   "verbose" "$io_reset: " "$@" ; } >&2 ; fi ; }
print_message() { { printf "cccmk: %s%s%s%s\n" "$io_blue"   "message" "$io_reset: " "$@" ; } >&2 ; }
print_warning() { { printf "cccmk: %s%s%s%s\n" "$io_yellow" "warning" "$io_reset: " "$@" ; } >&2 ; }
print_success() { { printf "cccmk: %s%s%s%s\n" "$io_green"  "success" "$io_reset: " "$@" ; } >&2 ; }
print_failure() { { printf "cccmk: %s%s%s%s\n" "$io_red"    "failure" "$io_reset: " "$@" ; } >&2 ; }
print_error()   { { printf "cccmk: %s%s%s%s\n" "$io_red"    "error"   "$io_reset: " "$@" ; } >&2 ; exit 1 ; }



###
### utility functions for string/array/list manipulation
###

#! Check if a space-separated list ($2) contains a certain string ($1)
contains()
{
	for i in $2
	do
		if [ "$i" == "$1" ]
		then return 0
		fi
	done
	return 1
}

#! Keep only certain items from the space-separated list given as input ($2), with a custom command ($1)
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



#! Call AWK on a file ($1), modifying it in-place
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
	| grep -v '.cccmk' \
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
