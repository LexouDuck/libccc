#!/bin/sh -e



for i in $command_arg_path
do
	file_pwd="$i"
	file_ccc="$CCCMK_PATH_MKFILES/$i"
	file_ccc=`echo "$file_ccc" | sed "s|$project_mkpath/||g"`
	if ! [ -f "$file_pwd" ]
	then
		print_error "Invalid filepath given to 'cccmk update': '$file_pwd' - no such file exists."
		exit 1
	fi
	if ! cmp "$file_ccc" "$file_pwd"
	then
		cccmk_diff "$file_ccc" "$file_pwd"
		print_message "The file '$file_pwd' differs from the cccmk template (see diff above)"
		print_message "NOTE: your file is shown as old/red, and the latest cccmk template is shown as new/green."
		read -p "Are you sure you wish to overwrite '$file_pwd' ? [y/N]" response
		response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
		case $response in
			y|ye|yes) response=true ;;
			n|no|'')  print_message "Operation cancelled." ; continue ;;
			*)        print_error "Invalid answer, should be either 'y'/'yes' or 'n'/'no'." ; exit 1 ;;
		esac
	else
		response=false
		print_message "The file '$file_pwd' is identical to the latest cccmk template."
	fi
	if $response
	then
		print_message "Updating file '$file_pwd'..."
		cp "$file_ccc" "$file_pwd"
	fi
done
