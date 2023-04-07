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
	replace "$f" '\b''Error_STDC\b'       'Error_STD_GetMessage'
	replace "$f" '\b''Error_Set\b'        'Error_CCC_Set'
	replace "$f" '\b''Error_Get\b'        'Error_CCC_Get'
	replace "$f" '\b''Error_GetMessage\b' 'Error_CCC_GetMessage'
	replace "$f" '\b''Error_GetName\b'    'Error_CCC_GetName'
	replace "$f" '\b''Error_GetCode\b'    'Error_CCC_GetCode'
	replace "$f" '\b''Log_Error_IO\b'            'Log_Error_STD'
	replace "$f" '\b''LogAll_Error_IO\b'         'LogAll_Error_STD'
	replace "$f" '\b''Log_Error\b'               'Log_Error_CCC'
	replace "$f" '\b''LogAll_Error\b'            'LogAll_Error_CCC'
	replace "$f" '\b''Log_Message_Verbose\b'     'Log_Verbose'
	replace "$f" '\b''LogAll_Message_Verbose\b'  'LogAll_Verbose'
done
