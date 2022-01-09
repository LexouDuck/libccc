#!/bin/sh -e



if ! [ -z "$project_missing" ]
then print_error "The current folder is not a valid cccmk project folder (needed for command 'cccmk update')"
	exit 1
fi

if [ -z "$command_arg_path" ]
then print_verbose "No scripts filepath(s) given, so all tracked mkfile scripts will be updated."
	command_arg_path="$project_scripts"
fi

#! Changes the given filepath ($1) to add a folder ($2) near its end (right after the last '/' of the filepath)
cccmk_alt_folder()
{
	echo "$1" \
	| awk -v folder="$2" '
	function lastindex(str, c)
	{ return (match(str,"\\" c "[^" c "]*$") ? RSTART : 0); }
	{
		i = lastindex($0, "/");
		print substr($0, 1, i) folder substr($0, i);
	}' 
}

# iterate over all filepath arguments
for i in $command_arg_path
do
	#! the file to update (relative to this project's 'mkfile' folder)
	filepath="`echo "$i" | sed "s|^$project_mkpath/||g"`"
	#! The file in the current project
	file_cwd="$project_mkpath/$filepath"
	if ! [ -f "$file_cwd" ]
	then print_error "Invalid filepath given to 'cccmk update': '$file_cwd' - no such file exists."
		exit 1
	fi
	#! The source cccmk template corresponding to the file to update (again, relative to 'mkfile' folder)
	template="$filepath"
	# check any potential conditional subfolders the file might be in
	file_ccc_altdirs=" _if_selected  _if_type_$project_type "
	if ! [ -f "$CCCMK_PATH_MKFILES/$template" ]
	then
		for altdir in $file_ccc_altdirs
		do
			file_ccc_alt="`cccmk_alt_folder "$template" "$altdir" `"
			if [ -f "$CCCMK_PATH_MKFILES/$file_ccc_alt" ]
			then
				template="$file_ccc_alt"
				file_ccc_alt=""
				print_verbose "found file inside '$altdir' conditional dir: '$CCCMK_PATH_MKFILES/$template'"
				break
			fi
		done
		if ! [ -z "$file_ccc_alt" ]
		then
			print_error "Error doing 'cccmk update': couldn't find template file '$CCCMK_PATH_MKFILES/$template'."
			exit 1
		fi
	fi
	#! The equivalent file in the local cccmk installed templates
	file_ccc="$CCCMK_PATH_MKFILES/$template"
	#! The newly updated cccmk template, fetched from the web
	file_new="$CCCMK_PATH_MKFILES/$template.tmp"
	print_message "Checking latest template for '$file_cwd'..."
	print_verbose "fetching template file from url: '$cccmk_git_url/$cccmk_dir_mkfiles/$template'"
	curl --silent "$cccmk_git_url/$cccmk_dir_mkfiles/$template" > "$file_new"
	# perform diff check
	if ! cmp "$file_ccc" "$file_cwd"
	then
		cccmk_diff "$file_ccc" "$file_cwd"
		print_message "The file '$file_cwd' differs from the cccmk template (see diff above)"
		print_message "NOTE: your file is shown as old/red, and the cccmk template is shown as new/green."
		read -p "Are you sure you wish to overwrite '$file_cwd' ? [y/N]" response
		response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
		case $response in
			y|ye|yes)
				response=true
				;;
			n|no|'')
				print_message "Operation cancelled."
				continue
				;;
			*)
				print_error "Invalid answer, should be either 'y'/'yes' or 'n'/'no'."
				exit 1
				;;
		esac
	else
		print_message "The file '$file_cwd' is identical to the cccmk template."
		response=false
	fi
	# do a git 3-way merge to update the file in question
	if $response
	then print_message "Updating file '$file_cwd'..."
		#cp "$file_ccc" "$file_cwd"
		git merge-file -p --diff3 "$file_cwd" "$file_ccc" "$file_new"
		#cp "$file_new" "$file_ccc"
	fi
done
