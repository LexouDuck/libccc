#!/bin/sh -e

#! This is the main entry-point script for cccmk



#! important variables
cccmk_version=0.1
cccmk_install=~/Projects/libccc/cccmk

if [ -z $debug ]
then debug=false
fi
verbose=$debug
if $debug
then set -x
fi

command=help
command_arg_name=
command_arg_path=

project_versionfile=VERSION
project_mkfile=Makefile
project_mkpath=mkfile
project_mkpath_dirs='
config
utils
rules
lists
packages
'



# utility functions for logging/io

print_verbose() {
if $verbose; then printf "cccmk: ""\033[34m""verbose" >&2 ; printf "\033[0m: $1\n" >&2 ; fi ; }
print_message() { printf "cccmk: ""\033[34m""message" >&2 ; printf "\033[0m: $1\n" >&2 ; }
print_warning() { printf "cccmk: ""\033[33m""warning" >&2 ; printf "\033[0m: $1\n" >&2 ; }
print_success() { printf "cccmk: ""\033[32m""success" >&2 ; printf "\033[0m: $1\n" >&2 ; }
print_error()   { printf "cccmk: ""\033[31m""error"   >&2 ; printf "\033[0m: $1\n" >&2 ; }



#! The path which stores all cccmk data
if [ -z "$CCCMK_PATH" ]
then
	CCCMK_PATH="$cccmk_install"
	#print_warning "No value provided for CCCMK_PATH, using default: '$CCCMK_PATH'"
fi
if ! [ -d "$CCCMK_PATH" ]
then
	print_error "The CCCMK_PATH variable does not point to a valid folder: '$CCCMK_PATH'"
	exit 1
fi
#! The path which stores cccmk source sh scripts
CCCMK_PATH_SCRIPTS="$CCCMK_PATH/scripts"
if ! [ -d "$CCCMK_PATH_SCRIPTS" ]
then
	print_error "The CCCMK_PATH folder does not contain a 'scripts' folder: '$CCCMK_PATH_SCRIPTS'"
	exit 1
fi
#! The path which stores cccmk template mkfiles
CCCMK_PATH_MKFILES="$CCCMK_PATH/mkfiles"
if ! [ -d "$CCCMK_PATH_MKFILES" ]
then
	print_error "The CCCMK_PATH folder does not contain a 'mkfiles' folder: '$CCCMK_PATH_MKFILES'"
	exit 1
fi
#! The path which stores cccmk template files for new projects
CCCMK_PATH_PROJECT="$CCCMK_PATH/project"
if ! [ -d "$CCCMK_PATH_PROJECT" ]
then
	print_error "The CCCMK_PATH folder does not contain a 'project' folder: '$CCCMK_PATH_PROJECT'"
	exit 1
fi



show_help()
{
	echo 'USAGE:'
	echo '    cccmk [OPTIONS...] new PROJECT_NAME [PROJECT_DIR]'
	echo '    cccmk [OPTIONS...] diff [PROJECT_DIR]'
	echo ''
	echo 'OPTIONS:'
	echo '    Here is the list of accepted options, both in "-c" short form, and "--string" long form'
	echo '    -h, --help      If provided, display this short help message and exit'
	echo '    -v, --version   If provided, display the cccmk version number info and exit'
	echo '    -V, --verbose   If provided, show additional log messages for detailed info/debugging'
	echo ''
	echo 'COMMANDS:'
	echo ''
	echo '  $ cccmk new PROJECT_NAME [PROJECT_DIR]'
	echo '    Creates a new project, filling the newly created project with various mkfile scripts,'
	echo '    prompting the user to specify which mkfile scripts/rules they would like to use.'
	echo '    - PROJECT_NAME is the name to give to the project.'
	echo '    - PROJECT_DIR (optional) is the folder in which to create the project.'
	echo '      If not specified, the new project will be created in the current folder,'
	echo '      and the newly created project folder will be named using PROJECT_NAME.'
	echo ''
	echo '  $ cccmk diff [PROJECT_DIR]'
	echo '    Checks for differences between the given project and the template mkfiles.'
	echo '    - PROJECT_DIR (optional) is the project folder for which to check differences.'
	echo '      If not specified, the project folder to check is assumed to be "./", the current dir.'
	echo ''
}

show_version()
{
	echo "cccmk - version $cccmk_version"
}



parse_args()
{
	while [ $# -gt 0 ]
	do
		print_verbose "parsing arg: '$1'"
		case "$1" in
			-h|--help)	print_verbose "parsed arg: '--help'"
				show_help
				exit 0
				;;
			-v|--version)	print_verbose "parsed arg: '--version'"
				show_version
				exit 0
				;;
			-V|--verbose)	print_verbose "parsed arg: '--verbose'"
				verbose=true
				;;
			-*)	print_error "Unknown option: '$1' (try 'cccmk --help')"
				exit 1
				;;
			new)	print_verbose "parsed command: 'new'"
				command=$1
				if [ $# -le 1 ]
				then print_error "The 'new' command expects a PROJECT_NAME argument" ; exit 1
				fi
				command_arg_name="$2"
				if [ $# -gt 2 ]
				then command_arg_path="$3" ; shift
				else command_arg_path="./$2"
				fi
				shift
				;;
			diff)	print_verbose "parsed command: 'diff'"
				command=$1
				if [ $# -gt 1 ]
				then command_arg_path="$2" ; shift
				else command_arg_path="."
				fi
				;;
			*)	print_error "Invalid argument: '$1' (try 'cccmk --help')"
				exit 1
				;;
		esac
		shift # go to next argument
	done
	print_verbose "finished parsing args."
	print_verbose "verbose = $verbose"
	print_verbose "command = '$command'"
	print_verbose "command_arg_name = '$command_arg_name'"
	print_verbose "command_arg_path = '$command_arg_path'"
}



parse_args "$@"



case "$command" in
	new)
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
		;;

	diff)
		print_message "folder differences:"
		diff "$CCCMK_PATH_MKFILES" "$command_arg_path/$project_mkpath"
		#tree "$CCCMK_PATH_MKFILES"               | expand -t 4 > mkfile_tree_ccc.txt
		#tree "$command_arg_path/$project_mkpath" | expand -t 4 > mkfile_tree_cwd.txt
		#diff --side-by-side "mkfile_tree_ccc.txt" "mkfile_tree_cwd.txt"
		#rm mkfile_tree_ccc.txt
		#rm mkfile_tree_cwd.txt
		mkfiles=`( cd "$CCCMK_PATH_MKFILES" ; find . -name '*.mk' -o -name '*.awk' )`
		for i in $mkfiles
		do
			if [ -f $command_arg_path/$project_mkpath/$i ]
			then
				print_message "mkfile differences: '$i'"
				diff "$CCCMK_PATH_MKFILES/$i" "$command_arg_path/$project_mkpath/$i" || continue
			fi
		done
		print_verbose "finished checking differences."
		;;

esac
