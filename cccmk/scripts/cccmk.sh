#!/bin/sh -e

#! This is the main entry-point script for cccmk



#! important variables
version=0.1

debug=false
verbose=$debug

command=help
command_arg_name=
command_arg_path=

project_mkfile=Makefile
project_mkpath=make
project_versionfile=VERSION



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
	CCCMK_PATH="./cccmk"
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

. "$CCCMK_PATH_SCRIPTS/utils.sh"



show_help()
{
	echo 'USAGE:'
	echo '    cccmk [OPTIONS...] new PROJECT_NAME [PROJECT_DIR]'
	echo '    cccmk [OPTIONS...] diff [PROJECT_DIR]'
	echo ''
	echo 'OPTIONS:'
	echo '    Here is the list of accepted options, both in '-c' short form, and '--string' long form'
	echo '    -h, --help      If provided, display this short help message and exit'
	echo '    -V, --version   If provided, display the cccmk version number info and exit'
	echo '    -v, --verbose   If provided, show additional log messages for detailed info/debugging'
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
	echo "cccmk - version $version"
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
			-V|--version)	print_verbose "parsed arg: '--version'"
				show_version
				exit 0
				;;
			-v|--verbose)	print_verbose "parsed arg: '--verbose'"
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
				if [ $# -gt 1 ]
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
		print_verbose "creating new project at '$command_arg_path'..."
		mkdir "$command_arg_path"
		cd "$command_arg_path"
		mkdir "./$project_mkpath"
		mkdir "./$project_mkpath/config"
		mkdir "./$project_mkpath/utils"
		mkdir "./$project_mkpath/rules"
		mkdir "./$project_mkpath/lists"
		mkdir "./$project_mkpath/packages"
		touch "./$project_mkfile"
		chmod 755 "./$project_mkfile"
		echo "$command_arg_name@0.0.0-?" "./$project_versionfile"
		git init
		cd -
		print_success "Created new project '$command_arg_name' at '$command_arg_path'"
		;;
	diff)
		diff "$CCCMK_PATH_MKFILES" "$command_arg_path/$project_mkpath"
		print_verbose "finished checking differences."
		;;
esac
