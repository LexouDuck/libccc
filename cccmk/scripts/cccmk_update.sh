#!/bin/sh -e



if ! [ -z "$project_missing" ]
then
	print_error "The current folder is not a valid cccmk project folder (needed for command 'cccmk update')"
	exit 1
fi

#! current project folder
path_pwd="."
#! local cccmk install folder which stores the project template
path_ccc="$CCCMK_PATH_PROJECT"

#! list of updated/merged files
updated_files=""
#! list of all tracked files in the current project
tracked_files=""

for i in $project_track
do
#	trackedfile_ccc_rev="`echo "$i" | cut -d':' -f 1 `"
#	trackedfile_cccpath="`echo "$i" | cut -d':' -f 2 `"
	trackedfile_pwdpath="`echo "$i" | cut -d':' -f 3 `"
	tracked_files="$tracked_files $trackedfile_pwdpath"
done


if [ -z "$command_arg_path" ]
then
	print_verbose "No scripts filepath(s) given, so all tracked mkfile scripts will be updated."
	command_arg_path="$tracked_files"
else
	# iterate over all user-specified files, if any
	for i in $command_arg_path
	do
		if [ -z "` echo $tracked_files | grep -w "$i" `" ]
		then
			print_warning "file is not tracked by '$project_cccmkfile' file: '$i'"
		fi
	done
fi

# iterate over all cccmk-tracked files
for i in $project_track
do
	trackedfile_ccc_rev="`echo "$i" | cut -d':' -f 1 `"
	trackedfile_cccpath="`echo "$i" | cut -d':' -f 2 `"
	trackedfile_pwdpath="`echo "$i" | cut -d':' -f 3 `"
	if ! [ -z "$command_arg_path" ]
	then
		if [ -z "` echo $command_arg_path | grep -w "$trackedfile_pwdpath" `" ]
		then continue # user did not ask for this file
		fi
	fi

	#! The file in the current project
	file_pwd="$trackedfile_pwdpath"
	#! The equivalent file in the local cccmk installed templates
	file_ccc="$trackedfile_cccpath"
	#! The temporary filepath for the newly updated cccmk template, fetched from the web
	file_tmp="$file_pwd.tmp"
	path_tmp="$path_pwd"

	# check if files exist, and prompt user accordingly
	if [ -f "$path_pwd/$file_pwd" -a -f "$path_ccc/$file_ccc" ]
	then
		if cmp -s "$path_ccc/$file_ccc" "$path_pwd/$file_pwd"
		then
			print_message "The file '$file_pwd' is identical to the cccmk template."
			response=false
		else
			cccmk_diff "$path_ccc/$file_ccc" "$path_pwd/$file_pwd"
			print_message "The file '$file_pwd' differs from the cccmk template (see diff above)"
			print_message "NOTE: the cccmk template is shown as old/red, and your file is shown as new/green."
			echo "Are you sure you wish to overwrite '$file_pwd' ?"
			prompt_question response 'n'
			if $response
			then print_message "Updating file '$file_pwd'..."
			else print_message "Update operation cancelled for '$file_pwd'." ; continue
			fi
		fi
	elif [ -f "$path_pwd/$file_pwd" ]
	then print_warning "Could not find source template file '$path_ccc/$file_ccc'."
	elif [ -f "$path_ccc/$file_ccc" ]
	then print_warning "Could not find project tracked file '$path_pwd/$file_pwd'."
	else
		print_error "Both files do not exist:\n%s\n%s" \
			"$path_ccc/$file_ccc" \
			"$path_pwd/$file_pwd" \
		;exit 1
	fi

	# actually update the file in question
	if $response
	then
		# get latest template from the internet
		print_message "Checking latest template for '$file_pwd'..."
		file_url="$cccmk_git_url/$cccmk_dir_project/$file_ccc"
		print_verbose "fetching template file from url: '$file_url'"
		curl --silent "$file_url" > "$path_tmp/$file_tmp"
		if ! [ -f "$path_tmp/$file_tmp" ]
		then
			print_error "Could not retrieve latest template from repo at '$file_url'."
			rm -f "$path_tmp/$file_tmp"
			exit 1
		elif ! [ -z "` head -1 "$path_tmp/$file_tmp" | grep '^[45][0-9][0-9]: ' `" ]
		then
			print_error "Error while retrieving template from repo at '$file_url':\n`cat "$path_tmp/$file_tmp"`"
			rm -f "$path_tmp/$file_tmp"
			exit 1
		fi
		# do a git 3-way merge to update the file in question
		print_verbose "performing 3-way diff/merge:\n%s\n%s\n%s\n%s" \
			" - modified file (project): [`file_timestamp "$path_pwd/$file_pwd"`] $path_pwd/$file_pwd" \
			" - up2dated file (cccmk):   [`file_timestamp "$path_tmp/$file_tmp"`] $path_tmp/$file_tmp" \
			" - original file (cccmk):   [`file_timestamp "$path_ccc/$file_ccc"`] $path_ccc/$file_ccc" \
			""
		if [ -f "$path_pwd/$file_pwd" -a -f "$path_ccc/$file_ccc" ]
		then
			git merge-file --diff3 --theirs \
				"$path_pwd/$file_pwd" \
				"$path_ccc/$file_ccc" \
				"$path_tmp/$file_tmp" \

		elif [ -f "$path_ccc/$file_ccc" ]; then cp "$path_tmp/$file_tmp" "$path_pwd/$file_pwd"
		elif [ -f "$path_pwd/$file_pwd" ]; then echo ''
		else exit 1
		fi
		# check that merge was successful
		if [ -z "` cat "$path_pwd/$file_pwd" | grep '^=======$' `" ]
		then print_success "Updated file '$file_pwd'."
		else print_warning "There were merge conflicts when updating file: '$file_pwd'."
		fi
		# cleanup temp file
		rm "$path_tmp/$file_tmp"
	fi
done
