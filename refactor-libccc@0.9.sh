#!/bin/bash


replace()
{
	sed -E "s/\\b$2\\b/$3/g" "$1" > "$1.tmp"
	mv "$1.tmp" "$1"
}

for f in $*
do
	if [ ! -f $f ]
	then
		echo "WARNING: file does not exist: $f"
		continue # if file doesnt exist, move on to the next arg
	fi
	replace "$f" "String_Concat(_[A-Z])?" "String_Add\\1"
	replace "$f" "String_Join"            "String_Concat"
	replace "$f" "StringArray_Fold"       "String_Join"
	replace "$f" "StringArray_Join"       "StringArray_Concat"
	replace "$f" "StringArray_Insert"     "StringArray_Wedge"
	replace "$f" "libccc/math/math.h"     "libccc/math.h"
	replace "$f" "libccc/error.h"         "libccc/sys/error.h"
	replace "$f" "libccc/color.h"         "libccc/image/color.h"
done
