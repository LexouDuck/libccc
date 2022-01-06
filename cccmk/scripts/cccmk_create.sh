#!/bin/sh -e



# prompt the user for the project type
read -p "Is the project a program, or library ? [program/library/cancel] " response
response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
case $response in
	program|library) project_type=$response ;;
	cancel)	print_message "Operation cancelled." ; exit 1 ;;
	*)	print_error "Invalid answer, should be either 'program' or 'library'." ; exit 1 ;;
esac

# prompt the user for the project packages
echo "Please select which packages you like to include as dependencies, among the common ones:"
echo "(UP/DOWN to move cursor; SPACE to toggle selected checkbox; ENTER to confirm and proceed)"
common_packages=`ls "$CCCMK_PATH_MKFILES/packages" | sort --ignore-case | xargs`
chosen_packages=
prompt_multiselect chosen_packages `echo "$common_packages" | tr [:space:] ';' `
#print_verbose "selected packages: ${response[@]}"

print_verbose "creating new project at '$command_arg_path'..."
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
	# copy over template mkfile scripts to new project folder
	mkdir "./$project_mkpath"
	for dir in $project_mkpath_dirs
	do
		if [ "$dir" == "packages" ]
		then # only copy over selected packages
			mkdir "./$project_mkpath/$dir"
			for i in ${chosen_packages[@]}
			do
				cp "$CCCMK_PATH_MKFILES/$dir/$i" "./$project_mkpath/$dir/$i"
			done
		else # copy over all files, and check leading-underscore folders to conditionally copy
			cp -r "$CCCMK_PATH_MKFILES/$dir" "./$project_mkpath/$dir"
			if [ -d "./$project_mkpath/$dir/_$response/" ]
			then mv "./$project_mkpath/$dir/_$response/"*.mk "./$project_mkpath/$dir/"
			fi
		fi
		rm -rf "./$project_mkpath/$dir/"_*
	done
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
)
print_success "Created new project '$command_arg_name' at '$command_arg_path'"
