#!/bin/sh -e

#! This is the main entry-point script for cccmk
#! It sets some key variables, and processes commandline arguments

if [ -z $debug ]
then debug=false
fi
if $debug
then set -x
fi

# check that necessary shell commands are installed and usable

# check the `diff` command
if ! diff --version > /dev/null
then print_error "cccmk requires the shell command 'diff' to be installed and accessible from the \$PATH."
	exit 1
fi
# check the `git` command
if ! git --version > /dev/null
then print_error "cccmk requires the shell command 'git' to be installed and accessible from the \$PATH."
	exit 1
fi
# check the `make` command
if ! make --version > /dev/null
then print_error "cccmk requires the shell command 'make' to be installed and accessible from the \$PATH."
	exit 1
fi

# set the initial values for important program variables

#! If set to `true`, then cccmk will display any `print_verbose` messages
verbose=$debug

command=help
command_arg_name=
command_arg_path=



# utility functions for logging/io

print_verbose() {
if $verbose; then { printf "cccmk: ""\033[34m""verbose""\033[0m: ""$@" ; echo "" ; } >&2 ; fi ; }
print_message() { { printf "cccmk: ""\033[34m""message""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_warning() { { printf "cccmk: ""\033[33m""warning""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_success() { { printf "cccmk: ""\033[32m""success""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_failure() { { printf "cccmk: ""\033[31m""failure""\033[0m: ""$@" ; echo "" ; } >&2 ; }
print_error() { print_failure "$@" ; exit 1 ; }



cccmk_install=~/Projects/libccc/cccmk
#cccmk_install=~/.cccmk

#! The path which stores all cccmk data
if [ -z "$CCCMK_PATH" ]
then
	CCCMK_PATH="$cccmk_install"
	#print_warning "No value provided for CCCMK_PATH, using default: '$CCCMK_PATH'"
fi
if ! [ -d "$CCCMK_PATH" ]
then print_error "Bad install? The CCCMK_PATH variable does not point to a valid folder: '$CCCMK_PATH'"
	exit 1
fi

cccmk_dir_scripts="scripts"
#! The path which stores cccmk source sh scripts
CCCMK_PATH_SCRIPTS="$CCCMK_PATH/$cccmk_dir_scripts"
if ! [ -d "$CCCMK_PATH_SCRIPTS" ]
then print_error "Bad install? The CCCMK_PATH folder does not contain a '$cccmk_dir_scripts' folder: '$CCCMK_PATH_SCRIPTS'"
	exit 1
fi

cccmk_dir_project="project"
#! The path which stores cccmk template files for new projects
CCCMK_PATH_PROJECT="$CCCMK_PATH/$cccmk_dir_project"
if ! [ -d "$CCCMK_PATH_PROJECT" ]
then print_error "Bad install? The CCCMK_PATH folder does not contain a '$cccmk_dir_project' folder: '$CCCMK_PATH_PROJECT'"
	exit 1
fi
cccmk_dir_mkfiles="$cccmk_dir_project/mkfile"
#! The path which stores cccmk template mkfiles
CCCMK_PATH_MKFILES="$CCCMK_PATH/$cccmk_dir_mkfiles"
if ! [ -d "$CCCMK_PATH_MKFILES" ]
then print_error "Bad install? The CCCMK_PATH folder does not contain a '$cccmk_dir_mkfiles' folder: '$CCCMK_PATH_MKFILES'"
	exit 1
fi



# set the fundamental cccmk variables

#! The installation folder path of cccmk
cccmk_install=~/Projects/libccc/cccmk
#! The version number of the currently installed cccmk
cccmk_version="`( cat "$cccmk_install/VERSION" )`"
#! The git revision of the currently installed cccmk
cccmk_git_rev="`( cd "$cccmk_install" ; git rev-parse HEAD )`"
#! The git repo URL from which to get any cccmk templates
cccmk_git_url="https://raw.githubusercontent.com/LexouDuck/libccc"
#! The git branch name/revision hash to use when doing a 'cccmk upgrade'
cccmk_upgrade=dev
#! The shell command (and arguments) used to perform and display file text diffs
cccmk_diffcmd="git --no-pager diff --no-index --color"
#cccmk_diffcmd="diff --color"
cccmk_diff()
{
	$cccmk_diffcmd "$1" "$2" || echo ''
}



. $CCCMK_PATH_SCRIPTS/util.sh
. $CCCMK_PATH_SCRIPTS/help.sh



#! Parses program arguments, assessing which command is called, handling arg errors etc
parse_args()
{
	if [ $# -eq 0 ]
	then print_warning "No command/arguments given to cccmk, displaying help..."
	else while [ $# -gt 0 ]
	do
		case "$1" in
			(-h|--help|help)
				command="$1"
				print_verbose "parsed command: '$command'"
				show_help
				exit 0
				;;
			(-v|--version|version)
				command="$1"
				print_verbose "parsed command: '$command'"
				show_version
				exit 0
				;;
			(-V|--verbose)
				verbose=true
				print_verbose "parsed argument: '$1'"
				;;
			(-*)
				print_error "Unknown option: '$1' (try 'cccmk --help')"
				exit 1
				;;
			(create)
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
			(migrate)
				command="$1"
				print_verbose "parsed command: '$command'"
				if [ $# -gt 1 ]
				then command_arg_path="$2" ; shift
				else command_arg_path="."
				fi
				;;
			(diff|update)
				command="$1"
				print_verbose "parsed command: '$command'"
				if [ $# -gt 1 ]
				then
					shift
					command_arg_path="$@"
					while [ $# -gt 1 ]
					do
						shift
					done
				fi
				;;
			(upgrade)
				command="$1"
				print_verbose "parsed command: '$command'"
				;;
			(*)
				print_error "Invalid argument: '$1' (try 'cccmk --help')"
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



# set the project configuration variables

#! The filepath of a project's project-tracker file
project_cccmkfile=".cccmk"

#! Parsed from the .cccmk file: The author of a project
project_author=
#! Parsed from the .cccmk file: The name of a project
project_name=
#! Parsed from the .cccmk file: The year of a project
project_year=
#! Parsed from the .cccmk file: The type (program/library) of a project
project_type=
#! Parsed from the .cccmk file: The cccmk commit revision
project_cccmk="dev"
#! Parsed from the .cccmk file: The filepath of a project's main makefile
project_mkfile="Makefile"
#! Parsed from the .cccmk file: The filepath of a project's makefile scripts folder
project_mkpath="mkfile"
#! Parsed from the .cccmk file: The filepath of a project's versioning info file
project_versionfile="VERSION"
#! Parsed from the .cccmk file: The filepath of a project's package dependency list file
project_packagefile="$project_mkpath/lists/packages.txt"

#! Parsed from the .cccmk file: the list of project files to track with cccmk
project_track=
project_scriptfiles=

#! The list of absent files which are necessary for any project using cccmk
project_missing=

if ! [ -f "./$project_cccmkfile" ]
then print_warning "The current folder is not a valid cccmk project folder - missing '$project_cccmkfile'"
	project_missing="$project_missing\n- missing project tracker file: '$project_cccmkfile'"
else
	# parse the .cccmk file (by simply running it as an inline shell script)
	. "./$project_cccmkfile"
	print_verbose "parsed project_author:      '$project_author'"
	print_verbose "parsed project_name:        '$project_name'"
	print_verbose "parsed project_year:        '$project_year'"
	print_verbose "parsed project_type:        '$project_type'"
	print_verbose "parsed project_cccmk:       '$project_cccmk'"
	print_verbose "parsed project_mkfile:      '$project_mkfile'"
	print_verbose "parsed project_mkpath:      '$project_mkpath'"
	print_verbose "parsed project_versionfile: '$project_versionfile'"
	print_verbose "parsed project_packagefile: '$project_packagefile'"
	print_verbose "parsed project_track:       '$project_track'"
	project_scriptfiles=''
	for i in $project_track
	do
		project_scriptfiles="$project_scriptfiles `echo "$i" | cut -d':' -f 2 `"
	done
	#print_verbose "parsed project_scriptfiles: '$project_scriptfiles'"
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
#if ! [ -f "./$project_packagefile" ]
#then project_missing="$project_missing\n- missing packages dependency list file: '$project_packagefile'"
#fi

# display warning if current folder is missing any necessary project files
if ! [ -z "$project_missing" ]
then print_warning "The current cccmk project folder is missing important files:$project_missing"
fi



#! Takes in a template text file, and creates a text file from the given variable values
#! @param $1	inputfile (filepath): the template text file used to generate our final file
#! @param $2	outputfile [optional] (filepath): if not specified, inputfile is modified in-place
#! @param $3	variables  [optional] (string): the list of variable names and their values
#!          	Each key/value pair has an '=' equal, and they are separated with ';' semi-colons.
#!          	'foo=a; bar=b; baz=c;' is a valid example. If nothing is specified, cccmk project variables are used.
cccmk_template()
{
	local inputfile="$1"
	local outputfile="$2"
	local variables="$3"
	if [ -z "$variables" ]
	then variables="
		author=$project_author;
		name=$project_name;
		year=$project_year;
		type=$project_type;
		cccmk=$project_cccmk;
		mkfile=$project_mkfile;
		mkpath=$project_mkpath;
		versionfile=$project_versionfile;
		packagefile=$project_packagefile;
		track=$project_track;
	"
	fi
	local functions="
		is(2)
		tracked(1)
	"
	if [ -z "$outputfile" ]
	then
		awk_inplace "$inputfile" \
		-v variables="$variables" \
		-v functions="$functions" \
		-f "$CCCMK_PATH_SCRIPTS/template-functions.awk" \
		-f "$CCCMK_PATH_SCRIPTS/template.awk"
	else
		awk \
		-v variables="$variables" \
		-v functions="$functions" \
		-f "$CCCMK_PATH_SCRIPTS/template-functions.awk" \
		-f "$CCCMK_PATH_SCRIPTS/template.awk" \
		"$inputfile" > "$outputfile"
	fi
}



# perform action, according to parsed arguments
case "$command" in
	help)    show_help    ;;
	version) show_version ;;
	create)  . $CCCMK_PATH_SCRIPTS/cccmk_create.sh  ;;
	migrate) . $CCCMK_PATH_SCRIPTS/cccmk_migrate.sh ;;
	diff)    . $CCCMK_PATH_SCRIPTS/cccmk_diff.sh    ;;
	update)  . $CCCMK_PATH_SCRIPTS/cccmk_update.sh  ;;
	upgrade) . $CCCMK_PATH_SCRIPTS/cccmk_upgrade.sh ;;
esac
