#!/bin/sh -e



read -p "Is the project a program, or library ? [program/library/cancel] " response
response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
case $response in
	program|library) project_type=$response ;;
	cancel)	print_message "Operation cancelled." ; exit 1 ;;
	*)	print_error "Invalid answer, should be either 'program' or 'library'." ; exit 1 ;;
esac

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
	for i in $project_mkpath_dirs
	do
		cp -r "$CCCMK_PATH_MKFILES/$i" "./$project_mkpath/$i"
		if [ -d "./$project_mkpath/$i/_$response/" ]
		then mv "./$project_mkpath/$i/_$response/"*.mk "./$project_mkpath/$i/"
		fi
		rm -rf "./$project_mkpath/$i/"_*
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
