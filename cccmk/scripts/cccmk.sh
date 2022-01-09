#!/bin/sh -e

#! This is the main entry-point script for cccmk
#! It sets some key variables, and processes commandline arguments



# fundamental cccmk variables

#! The git revision (can also be branch name) of the currently installed cccmk
cccmk_git_rev="dev"
#! The git repo URL from which to get any cccmk templates
cccmk_git_url="https://raw.githubusercontent.com/LexouDuck/libccc/$cccmk_git_rev/cccmk/"
#! The installation folder path of cccmk
cccmk_install=~/Projects/libccc/cccmk
#! The shell command (and arguments) used to perform and display file text diffs
cccmk_diffcmd="git --no-pager diff --no-index --color"
#cccmk_diffcmd="diff --color"
cccmk_diff()
{
	$cccmk_diffcmd "$1" "$2" || echo ''
}

if [ -z $debug ]
then debug=false
fi
if $debug
then set -x
fi

#! If set to `true`, then cccmk will display any `print_verbose` messages
verbose=$debug



command=help
command_arg_name=
command_arg_path=



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
	print_error "Bad install? The CCCMK_PATH variable does not point to a valid folder: '$CCCMK_PATH'"
	exit 1
fi
#! The path which stores cccmk source sh scripts
CCCMK_PATH_SCRIPTS="$CCCMK_PATH/scripts"
if ! [ -d "$CCCMK_PATH_SCRIPTS" ]
then
	print_error "Bad install? The CCCMK_PATH folder does not contain a 'scripts' folder: '$CCCMK_PATH_SCRIPTS'"
	exit 1
fi
#! The path which stores cccmk template files for new projects
CCCMK_PATH_PROJECT="$CCCMK_PATH/project"
if ! [ -d "$CCCMK_PATH_PROJECT" ]
then
	print_error "Bad install? The CCCMK_PATH folder does not contain a 'project' folder: '$CCCMK_PATH_PROJECT'"
	exit 1
fi
#! The path which stores cccmk template mkfiles
CCCMK_PATH_MKFILES="$CCCMK_PATH_PROJECT/mkfile"
if ! [ -d "$CCCMK_PATH_MKFILES" ]
then
	print_error "Bad install? The CCCMK_PATH folder does not contain a 'mkfile' folder: '$CCCMK_PATH_MKFILES'"
	exit 1
fi



. $CCCMK_PATH_SCRIPTS/util.sh
. $CCCMK_PATH_SCRIPTS/help.sh



# project configuration variables

#! The filepath of a project's project-tracker file
project_cccmkfile=".cccmk"

#! Parsed from the .cccmk file: The filepath of a project's main makefile
project_mkfile="Makefile"
#! Parsed from the .cccmk file: The filepath of a project's makefile scripts folder
project_mkpath="mkfile"
#! Parsed from the .cccmk file: The filepath of a project's versioning info file
project_versionfile="VERSION"
#! Parsed from the .cccmk file: The filepath of a project's package dependency list file
project_packagefile="$project_mkpath/lists/packages.txt"

#! Parsed from the .cccmk file: the type of the current project
project_type=
#! Parsed from the .cccmk file: the cccmk commit revision
project_cccmk=
#! Parsed from the .cccmk file: the list of mkfile scripts to track
project_scripts=

#! The list of absent files which are necessary for any project using cccmk
project_missing=

if ! [ -f "./$project_cccmkfile" ]
then print_warning "The current folder is not a valid cccmk project folder - missing '$project_cccmkfile'"
	project_missing="$project_missing\n- missing project tracker file: '$project_cccmkfile'"
fi

if ! [ -f "./$project_mkfile" ]
then project_missing="$project_missing\n- missing project main makefile: '$project_mkfile'"
fi
if ! [ -d "./$project_mkpath" ]
then project_missing="$project_missing\n- missing makefile scripts folder: '$project_mkpath'"
fi
if ! [ -f "./$project_versionfile" ]
then project_missing="$project_missing\n- missing versioning info file: '$project_versionfile'"
fi
if ! [ -f "./$project_packagefile" ]
then project_missing="$project_missing\n- missing packages dependency list file: '$project_packagefile'"
fi



#! Parses program arguments, assessing which command is called, handling arg errors etc
parse_args()
{
	if [ $# -eq 0 ]
	then print_warning "No command/arguments given to cccmk, displaying help..."
	else while [ $# -gt 0 ]
	do
		case "$1" in
			-h|--help|help)
				command="$1"
				print_verbose "parsed command: '$command'"
				show_help
				exit 0
				;;
			-v|--version|version)
				command="$1"
				print_verbose "parsed command: '$command'"
				show_version
				exit 0
				;;
			-V|--verbose)
				verbose=true
				print_verbose "parsed argument: '$1'"
				;;
			-*)	print_error "Unknown option: '$1' (try 'cccmk --help')"
				exit 1
				;;
			create)
				command="$1"
				print_verbose "parsed command: '$command'"
				if [ $# -le 1 ]
				then print_error "The 'create' command expects a <PROJECT_NAME> argument (try 'cccmk --help')"
					exit 1
				fi
				command_arg_name="$2"
				if [ $# -gt 2 ]
				then command_arg_path="$3" ; shift
				else command_arg_path="./$2"
				fi
				shift
				;;
			migrate)
				command="$1"
				print_verbose "parsed command: '$command'"
				if [ $# -gt 1 ]
				then command_arg_path="$2" ; shift
				else command_arg_path="."
				fi
				;;
			diff)
				command="$1"
				print_verbose "parsed command: '$command'"
				if [ $# -gt 1 ]
				then command_arg_path="$2" ; shift
				else command_arg_path="."
				fi
				;;
			update)
				command="$1"
				print_verbose "parsed command: '$command'"
				shift
				if [ $# -ge 1 ]
				then command_arg_path="$@"
				else command_arg_path=""
				fi
				while [ $# -gt 1 ]
				do shift
				done
				;;
			*)	print_error "Invalid argument: '$1' (try 'cccmk --help')"
				exit 1
				;;
		esac
		shift # go to next argument
	done
	fi
	print_verbose "finished parsing args."
	print_verbose "verbose = $verbose"
	print_verbose "command = '$command'"
	print_verbose "command_arg_name = '$command_arg_name'"
	print_verbose "command_arg_path = '$command_arg_path'"
}

parse_args "$@"



# display warning if current folder is missing any necessary project files
if ! [ -z "$project_missing" ]
then print_warning "The current cccmk project folder is missing important files:$project_missing"
else
	. "./$project_cccmkfile"
	print_verbose "parsed project_type:        '$project_type'"
	print_verbose "parsed project_cccmk:       '$project_cccmk'"
	print_verbose "parsed project_mkfile:      '$project_mkfile'"
	print_verbose "parsed project_mkpath:      '$project_mkpath'"
	print_verbose "parsed project_versionfile: '$project_versionfile'"
	print_verbose "parsed project_packagefile: '$project_packagefile'"
	print_verbose "parsed project_scripts:     '$project_scripts'"
fi



# perform action, according to parsed arguments
case "$command" in
	help)    show_help    ;;
	version) show_version ;;
	create)  . $CCCMK_PATH_SCRIPTS/cccmk_create.sh  ;;
	migrate) . $CCCMK_PATH_SCRIPTS/cccmk_migrate.sh ;;
	diff)    . $CCCMK_PATH_SCRIPTS/cccmk_diff.sh    ;;
	update)  . $CCCMK_PATH_SCRIPTS/cccmk_update.sh  ;;
esac
