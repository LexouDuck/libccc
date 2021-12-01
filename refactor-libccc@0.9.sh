#!/bin/bash


replace()
{
	sed -E "s/\\b$2\\b/$3/g" "$1" > temp.ts
	mv temp.ts "$1"
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
done
