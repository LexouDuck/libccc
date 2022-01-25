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

	#! The URL of the tracked template file
	file_url="$cccmk_git_url/$trackedfile_ccc_rev/cccmk/$cccmk_dir_project/$trackedfile_cccpath"

	#! The file in the current project
	file_pwd="$trackedfile_pwdpath"
	#! The equivalent filepath tracked from the cccmk templates
	file_ccc="$trackedfile_cccpath"
	#! The temporary filepath for the newly updated cccmk template, fetched from the web
	file_old="$file_ccc.tmp"
	path_old="$path_ccc"

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
			echo "Are you sure you wish to update '$file_pwd' by merging it with the template ?"
			prompt_question response 'n'
		fi
	elif ! [ -f "$path_pwd/$file_pwd" ]
	then print_warning "Could not find project tracked file '$path_pwd/$file_pwd'."
		echo "Are you sure you wish to create the file '$file_pwd' using the template ?"
		prompt_question response 'n'
	elif ! [ -f "$path_ccc/$file_ccc" ]
	then print_warning "Could not find source template file '$path_ccc/$file_ccc'."
		response=true
	else
		print_error "Bad '$project_cccmkfile' tracker file - both files do not exist:\n%s\n%s" \
			"$path_ccc/$file_ccc" \
			"$path_pwd/$file_pwd" \
		; exit 1
	fi

	# check user response
	if $response
	then print_message "Updating file '$file_pwd'..."
	else print_message "Update operation cancelled for '$file_pwd'." ; continue
	fi

	# actually update the file in question
	if $response
	then
		# get tracked template from the internet
		print_verbose "fetching template file from url: '$file_url'"
		curl --silent "$file_url" > "$path_old/$file_old"
		if ! [ -f "$path_old/$file_old" ]
		then
			print_error "Could not retrieve tracked template from repo at '$file_url'."
			rm -f "$path_old/$file_old"
			exit 1
		elif ! [ -z "` head -1 "$path_old/$file_old" | grep '^[45][0-9][0-9]: ' `" ]
		then
			print_error "Error while retrieving template from repo at '$file_url':"
			print_error "` cat "$path_old/$file_old" `"
			rm -f "$path_old/$file_old"
			exit 1
		fi
		# do a git 3-way merge to update the file in question
		print_verbose "performing 3-way diff/merge:\n%s\n%s\n%s\n%s" \
			" - project_track modified file: [`file_timestamp "$path_pwd/$file_pwd"`] $path_pwd/$file_pwd" \
			" - last trakced cccmk template: [`file_timestamp "$path_old/$file_old"`] $path_old/$file_old" \
			" - localinstall cccmk template: [`file_timestamp "$path_ccc/$file_ccc"`] $path_ccc/$file_ccc" \
			""
		if [ -f "$path_pwd/$file_pwd" -a -f "$path_ccc/$file_ccc" ]
		then
			git merge-file -p --diff3 --union \
				"$path_pwd/$file_pwd" \
				"$path_old/$file_old" \
				"$path_ccc/$file_ccc" \
			>     "$path_pwd/.tmp" \
			&& mv "$path_pwd/.tmp" "$path_pwd/$file_pwd"
		elif [ -f "$path_ccc/$file_ccc" ]; then cp "$path_ccc/$file_ccc" "$path_pwd/$file_pwd"
		elif [ -f "$path_pwd/$file_pwd" ]; then cp "$path_old/$file_old" "$path_pwd/$file_pwd"
		else
			rm -f "$path_old/$file_old"
			exit 1
		fi
		# check that merge was successful
		if [ -z "` cat "$path_pwd/$file_pwd" | grep '^=======$' `" ]
		then print_success "Updated file '$file_pwd'."
		else print_warning "CONFLICT: There were merge conflicts when updating file: '$file_pwd'."
		fi
		# apply new tracking revision hash to .cccmk project tracker file
		awk_inplace "$path_pwd/$project_cccmkfile" \
			-v filepath="$file_pwd" \
			-v rev="$cccmk_git_rev" \
		'{
			if (/^[0-9a-fA-F]{40}:/)
			{
				split($0, parts, /:/);
				if (parts[3] == filepath)
				{
					print rev ":" parts[2] ":" filepath;
				}
				else print;
			}
			else print;
		}'
		# cleanup temp file
		rm "$path_old/$file_old"
		# keep track all previously updated/merged files
		updated_files="$updated_files $trackedfile_pwdpath"
	fi
done
print_verbose "finished updating files."
