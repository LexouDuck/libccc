#!/bin/sh -e



print_verbose "creating new project at '$command_arg_path'..."

# prompt the user for the project type
echo "Is the project a program, or library ? [program/library/cancel]"
read -p "> " response
response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
project_type=
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
echo ''

(
	# create project folder and cd inside it
	mkdir "$command_arg_path"
	cd    "$command_arg_path"
	# copy over template project files
	cp -r "$CCCMK_PATH_PROJECT/.githooks" ./
	cp -r "$CCCMK_PATH_PROJECT/"* ./
	# TODO LICENSE file logic ?
	# TODO replace [[x]] logic ?
	# create mkfile folder for the new project
	mkdir "./$project_mkpath"
	# create '.cccmk' project tracker file
	echo '#!/bin/sh -e' > "./$project_cccmkfile"
	chmod 755 "./$project_cccmkfile"
	{	echo ""
		echo "project_type='$project_type'"
		echo "project_cccmk='$project_cccmk'"
		echo "project_mkfile='$project_mkfile'"
		echo "project_mkpath='$project_mkpath'"
		echo "project_versionfile='$project_versionfile'"
		echo "project_packagefile='$project_packagefile'"
		echo "project_scripts='"                 
	} >> "$project_cccmkfile"
	# replace [[vars]] in templates
	project_replace_name="$command_arg_path"
	project_replace_year="`date "+%Y"`"
	project_replace_author="???" # TODO prompt_text() function call ?
	# iterate over all mkfile folders
	for dir in `list_subfolders "$CCCMK_PATH_MKFILES"`
	do
		suffix=''
		# copy over all files
		cp -r "$CCCMK_PATH_MKFILES/$dir" "./$project_mkpath/$dir"
		# iterate over all subfolders, and check '_if_*' folders to conditionally copy certain scripts
		for subdir in `list_subfolders "$project_mkpath/$dir"`
		do
			case "$subdir" in
				# prompt the user to select which files they want
				_if_multiselect)
					if [ -f "$project_mkpath/$dir/$subdir/.cccmk" ]
					then  . "$project_mkpath/$dir/$subdir/.cccmk"
					else prompt_message="Select which files you wish to include in your project:"
					fi
					proposed_files=`ls "$project_mkpath/$dir/$subdir/" | sort --ignore-case | xargs`
					selected_files=
					echo "$prompt_message"
					prompt_multiselect selected_files `echo "$proposed_files" | tr [:space:] ';' `
					for i in ${selected_files[@]}
					do
						mv  "./$project_mkpath/$dir/$subdir/$i" \
							"./$project_mkpath/$dir/$i"
					done
					;;
				# prompt the user to select one out of several files
				_if_select)
					if [ -f "$project_mkpath/$dir/$subdir/.cccmk" ]
					then  . "$project_mkpath/$dir/$subdir/.cccmk"
					else prompt_message="Select the file you wish to include in your project:"
					fi
					echo "$prompt_message"
					prompt_select selected_file 
					mv  "./$project_mkpath/$dir/$subdir/$selected_file" \
						"./$project_mkpath/$dir/$selected_file"
					;;
				# only copy over files if player answers y/yes to the '_if_flag_*/.cccmk' question
				_if_flag_*)
					if [ -f "$project_mkpath/$dir/$subdir/.cccmk" ]
					then  . "$project_mkpath/$dir/$subdir/.cccmk"
					else prompt_message="Do you wish to include the following files ?""\n`ls "$project_mkpath/$dir/$subdir/"`"
					fi
					prompt_question response "$prompt_message"
					if $response
					then
						mv  "./$project_mkpath/$dir/$subdir/"* \
							"./$project_mkpath/$dir/"
					fi
					;;
				# only copy over files if $project_type matches folder name part after '_if_type_'
				_if_type_*)
					if [ "$subdir" == "_if_type_$project_type" ]
					then
						mv  "./$project_mkpath/$dir/$subdir/"* \
							"./$project_mkpath/$dir/"
					fi
					;;
				*)	break
					;;
			esac
		done
		# cleanup up leftover '_if_*' folders
		rm -rf "./$project_mkpath/$dir/"_if_*
		# add mkfile scripts to the '.cccmk' file (with their respective cccmk template git revisions)
		for file in `find "$project_mkpath/$dir" -type f`
		do
			echo "$file$suffix" >> "$project_cccmkfile"
		done
	done
	echo "'" >> "$project_cccmkfile"
	# set project's name in root makefile
	awk -v project_name="$command_arg_name" '
	{
		if (/^NAME =/)
		{ print "NAME = " project_name; }
		else print;
	}' "$CCCMK_PATH_PROJECT/Makefile" > "./$project_mkfile"
	chmod 755 "./$project_mkfile"
	# create project version file
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
