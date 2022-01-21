#!/bin/sh -e

#! Copies over files from a source directory to the output directory, for creating a project
project_template_copy()
{
	local srcdir="$1"
	local srcpath="$2"
	local outpath="$3"
	local files="$4"
	for i in $files
	do
		# skip any project template helper scripts
		if [ "$i" == ".cccmk" ]
		then continue
		fi
		# if no value was provided to the 'output_filename' variable, then use the source filename
		if [ -z "$output_filename" ]
		then output_filename="$i"
		fi
		# copy source template file over to output folder
		print_verbose "copying template file: '$srcdir/$srcpath/$i'"
		cp -p "$srcdir/$srcpath/$i"   "$outpath/$output_filename"
		# update the .cccmk project tracker file (only if path is not in an '_untracked' folder)
		case "$srcpath" in
			(*_untracked*) ;;
			(*)
				echo "$rev"":""$srcpath/$i"":""$outpath/$output_filename" \
				| awk '{ gsub(/\.\//, ""); print; }' \
				>> "$project_cccmkfile"
				;;
		esac
		# replace %[vars]% in newly copied-over file
		cccmk_template "$outpath/$output_filename"
		output_filename=""
	done
}

#! Recursive function used to copy over template files from the `cccmk/project` folder
project_template_recurse()
{
	local srcdir="$1"
	local outdir="$2"
	local dir="$3"
	local rev="`( cd "$cccmk_install" && git rev-parse HEAD )`"
	# create destination folder
	mkdir -p "$outdir/$dir"
	# copy over all regular files
	project_template_copy "$srcdir" "$dir" "$outdir/$dir" \
		"`list_onlyfiles "$srcdir/$dir"`"
	# iterate over all subfolders, and check '_if_*' folders to conditionally copy certain files
	for subdir in `list_subfolders "$srcdir/$dir"`
	do
		case "$subdir" in
			# prompt the user to select one out of several files
			_if_select)
				if [ -f "$srcdir/$dir/$subdir/.cccmk" ]
				then  . "$srcdir/$dir/$subdir/.cccmk"
				else prompt_message="Select the one file you wish to include in your project:"
				fi
				proposed_files=`ls "$srcdir/$dir/$subdir/" | sort --ignore-case | xargs | tr ' ' ';' `
				selected_file=
				echo "$prompt_message"
				prompt_select selected_file "$proposed_files"
				if [ -z "$output_filename" ]
				then output_filename="$selected_file"
				fi
				project_template_copy "$srcdir" "$dir/$subdir" "$outdir/$dir" \
					"$selected_file"
				;;
			# prompt the user to select which files they want
			_if_multiselect)
				if [ -f "$srcdir/$dir/$subdir/.cccmk" ]
				then  . "$srcdir/$dir/$subdir/.cccmk"
				else prompt_message="Select which files you wish to include in your project:"
				fi
				proposed_files=`ls "$srcdir/$dir/$subdir/" | sort --ignore-case | xargs`
				selected_files=
				echo "$prompt_message"
				prompt_multiselect selected_files `echo "$proposed_files" | tr [:space:] ';' `
				project_template_copy "$srcdir" "$dir/$subdir" "$outdir/$dir" \
					"$selected_files"
				;;
			# prompt the user with a y/n question, only copy over files if user answers y/yes
			_if_flag_*)
				if [ -f "$srcdir/$dir/$subdir/.cccmk" ]
				then  . "$srcdir/$dir/$subdir/.cccmk"
				else prompt_message="Do you wish to include the following files ?""\n`ls "$srcdir/$dir/$subdir/"`"
				fi
				echo "$prompt_message"
				prompt_question response 'n'
				if $response
				then
					project_template_copy "$srcdir" "$dir/$subdir" "$outdir/$dir" \
						"`list_onlyfiles "$srcdir/$dir/$subdir"`"
				fi
				;;
			# only copy over files if $project_type matches folder name part after '_if_type_'
			_if_type_*)
				if [ "$subdir" == "_if_type_$project_type" ]
				then
					project_template_copy "$srcdir" "$dir/$subdir" "$outdir/$dir" \
						"`list_onlyfiles "$srcdir/$dir/$subdir"`"
				fi
				;;
			# any other '_if_*' folder is unknown syntax
			_if_*)
				print_error "Unknown conditional project template subfolder: '$subdir'"
				exit 1
				;;
			# these folders simply hold files which should not be added to the .cccmk project_track list
			_untracked)
				project_template_copy "$srcdir" "$dir/$subdir" "$outdir/$dir" \
					"`list_onlyfiles "$srcdir/$dir/$subdir"`"
				;;
			# for any other normal folder, recurse deeper
			*)
				project_template_recurse "$srcdir" "$outdir" "$dir/$subdir"
				;;
		esac
	done
}



print_verbose "creating new project at '$command_arg_path'..."

if [ -d "$command_arg_path" ] && ! rmdir "$command_arg_path"
then
	print_error "Cannot create new project in existing folder '$command_arg_path' because it is not empty."
	print_message "Maybe you are looking to do a 'cccmk migrate' command instead ?"
	print_message "Try 'cccmk --help' for more info."
	exit 1
fi

# prompt the user for the project_author
echo "Who is the author of this project ?"
prompt_text response
project_author="$response"
if [ -z "$response" ]
then
	print_error "Invalid author name: should be a non-empty string."
	exit 1
fi

# prompt the user for the project_type
echo "Is the project a program, or library ?"
prompt_text response "[program/library/cancel]"
project_type=""
response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
case $response in
	program|library)
		project_type=$response
		;;
	cancel)
		print_message "Operation cancelled."
		exit 1
		;;
	*)	print_error "Invalid answer, should be either 'program' or 'library'."
		exit 1
		;;
esac

(
	# create project folder and cd inside it
	mkdir "$command_arg_path"
	cd    "$command_arg_path"

	# create '.cccmk' project tracker file
	echo '#!/bin/sh -e' > "./$project_cccmkfile"
	chmod 755 "./$project_cccmkfile"
	{	echo ""
		echo "project_author='$project_author'"
		echo "project_name='$command_arg_name'"
		echo "project_year='`date "+%Y"`'"
		echo "project_type='$project_type'"
		echo "project_cccmk='$project_cccmk'"
		echo "project_mkfile='$project_mkfile'"
		echo "project_mkpath='$project_mkpath'"
		echo "project_versionfile='$project_versionfile'"
		echo "project_packagefile='$project_packagefile'"
	} >> "$project_cccmkfile"
	# parse the newly created .cccmk prpject tracker file
	. "./$project_cccmkfile"

	# add tracked files to the '.cccmk' file (with their respective cccmk template git revisions)
	echo "project_track='" >> "$project_cccmkfile"
	project_template_recurse "$CCCMK_PATH_PROJECT" "." "."
	echo "'" >> "$project_cccmkfile"
	# parse the newly created .cccmk prpject tracker file
	. "./$project_cccmkfile"

	# create initial project version file
	echo "$command_arg_name@0.0.0-?" > "$project_versionfile"
	# set up git repo for new project
	git init
	git branch -m master
	git add --all
	git commit -m "initial commit"
	# set up other git/version management things
	make init
	make version

	if $verbose
	then
		print_verbose "Here is the folder tree of the newly created project:"
		if tree --version > /dev/null
		then tree -a -I '.git' .
		else print_warning "This computer has no 'tree' command installed, cannot display project folder tree."
		fi
		print_verbose "Here are the contents of the '$project_cccmkfile' file:"
		cat "$project_cccmkfile"
	fi
)
print_success "Created new project '$command_arg_name' at '$command_arg_path'"
