#!/bin/bash

replace()
{
	sed -E "s|$2|$3|g" "$1" > "$1.tmp" && mv "$1.tmp" "$1"
}

for f in $*
do
	if [ ! -f $f ]
	then
		echo "WARNING: file does not exist: $f"
		continue # if file doesnt exist, move on to the next arg
	fi
	replace "$f" '\bString_Concat(_[A-Z])?\b' 'String_Add\1'
	replace "$f" '\bString_Join\b'            'String_Concat'
	replace "$f" '\bStringArray_Fold\b'       'String_Join'
	replace "$f" '\bStringArray_Join\b'       'StringArray_Concat'
	replace "$f" '\bStringArray_Insert\b'     'StringArray_Wedge'
	replace "$f" '"libccc/math/math\.h"'      '"libccc/math.h"'
	replace "$f" '<libccc/math/math\.h>'      '<libccc/math.h>'
	replace "$f" '"libccc/error\.h"'          '"libccc/sys/error.h"'
	replace "$f" '<libccc/error\.h>'          '<libccc/sys/error.h>'
	replace "$f" '"libccc/color\.h"'          '"libccc/image/color.h"'
	replace "$f" '<libccc/color\.h>'          '<libccc/image/color.h>'
done
