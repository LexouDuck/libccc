#!/bin/sh -e



list_subfolders()
{
	( cd "$1" && ls -d */ 2> /dev/null || echo '' ) | tr '/' ' ' | xargs
}

print_verbose "creating new project at '$command_arg_path'..."

# prompt the user for the project type
echo "Is the project a program, or library ? [program/library/cancel]"
read -p "> " response
response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
project_type=program
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
	# TODO LICENSE logic ?
	echo "# $command_arg_name" > ./README.md
	echo "# TODO list"         > ./TODO.md
	# create mkfile folder for the new project
	mkdir "./$project_mkpath"
	# create '.cccmk' tracking file
	echo '#!/bin/sh -e' > "./$project_cccmkfile"
	chmod 755 "./$project_cccmkfile"
	echo "project_type=$project_type"   >> "$project_cccmkfile"
	echo "project_cccmk=$project_cccmk" >> "$project_cccmkfile"
	echo "project_scripts='"            >> "$project_cccmkfile"
	# iterate over all mkfile folders
	for dir in `list_subfolders "$CCCMK_PATH_MKFILES"`
	do
		# copy over all files
		cp -r "$CCCMK_PATH_MKFILES/$dir" "./$project_mkpath/$dir"
		# prepare multiselect prompt
		if [ "$dir" == "packages" ]
		then prompt_message="Select which packages you like to include as dependencies, among the common ones:"
		else prompt_message="Select which utility scripts you wish to include in your project:"
		fi
		# iterate over all subfolders, and check '_if_*' folders to conditionally copy certain scripts
		for subdir in `list_subfolders "$project_mkpath/$dir"`
		do
			case "$subdir" in
				_if_selected) # prompt the user to select which scripts they want
					proposed_scripts=`ls "$project_mkpath/$dir/$subdir/" | sort --ignore-case | xargs`
					selected_scripts=
					echo "$prompt_message"
					prompt_multiselect selected_scripts `echo "$proposed_scripts" | tr [:space:] ';' `
					for i in ${selected_scripts[@]}
					do
						mv "$project_mkpath/$dir/$subdir/$i" "./$project_mkpath/$dir/$i"
					done
					;;
				_if_type_*) # only copy over files if $project_type matches folder name part after '_if_type_'
					if [ "$subdir" == "_if_type_$project_type" ]
					then mv "./$project_mkpath/$dir/$subdir/"*.mk "./$project_mkpath/$dir/"
					fi
					;;
				*)	break;;
			esac
		done
		# cleanup up leftover '_if_*' folders
		rm -rf "./$project_mkpath/$dir/"_if_*
		# add mkfile scripts to the '.cccmk' file
		for file in `find "$project_mkpath/$dir" -type f`
		do
			echo "$file" >> "$project_cccmkfile"
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
