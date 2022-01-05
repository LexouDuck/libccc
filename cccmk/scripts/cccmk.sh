#!/bin/sh -e

#! This is the main entry-point script for cccmk



#! important variables
cccmk_version=0.1
cccmk_install=~/Projects/libccc/cccmk
#cccmk_diffcmd="diff --color"
cccmk_diffcmd="git --no-pager diff --color --no-index"
cccmk_diff()
{
	$cccmk_diffcmd "$1" "$2" || echo ''
}

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



cccmk_commands='
help
version
new
diff
update
'

cccmk_doc_args_help='cccmk [<OPTIONS>...] help'
cccmk_doc_text_help='
    Displays this brief help message (same as the -h/--help option).
'
cccmk_doc_args_version='cccmk [<OPTIONS>...] version'
cccmk_doc_text_version='
    Displays the cccmk version number info (same as the -v/--version option).
'
cccmk_doc_args_new='cccmk [<OPTIONS>...] new <PROJECT_NAME> [<PROJECT_DIR>]'
cccmk_doc_text_new='
    Creates a new project, filling the newly created project with various mkfile scripts,
    prompting the user to specify which mkfile scripts/rules they would like to use.
    - <PROJECT_NAME> is the name to give to the project.
    - <PROJECT_DIR> (optional) is the folder in which to create the project.
      If not specified, the new project will be created in the current folder,
      and the newly created project folder will be named using <PROJECT_NAME>.
'
cccmk_doc_args_diff='cccmk [<OPTIONS>...] diff [<PROJECT_DIR>]'
cccmk_doc_text_diff='
    Checks for differences between the given project and the template mkfiles.
    - <PROJECT_DIR> (optional) is the project folder for which to check differences.
      If not specified, the project folder to check is assumed to be "./", the current dir.
'
cccmk_doc_args_update='cccmk [<OPTIONS>...] update [<MKFILE_PATH>...]'
cccmk_doc_text_update='
    Overwrites the given file with the latest cccmk template equivalent.
    - <MKFILE_PATH> (optional) is the filepath of one or more mkfile scripts to update.
      If no path is specfied, then all mkfile script files will be updated.
'


cccmk_options='
h
v
V
'
cccmk_doc_flag_h='-h, --help       If provided, display this brief help message and exit.'
cccmk_doc_flag_v='-v, --version    If provided, display the cccmk version number info and exit.'
cccmk_doc_flag_V='-V, --verbose    If provided, show additional log messages for detailed info/debugging.'

show_help()
{
	echo 'USAGE:'
	for i in $cccmk_commands
	do
		line="cccmk_doc_args_$i" ; echo "    ${!line}"
	done
	echo ''
	echo 'OPTIONS:'
	echo '    Here is the list of accepted options, both in "-c" short form, and "--string" long form'
	for i in $cccmk_options
	do
		line="cccmk_doc_flag_$i" ; echo "    ${!line}"
	done
	echo ''
	echo 'COMMANDS:'
	for i in $cccmk_commands
	do
		line="cccmk_doc_args_$i" ; printf "  \$ ${!line}"
		line="cccmk_doc_text_$i" ; printf  "    ${!line}\n"
	done
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
			update)	print_verbose "parsed command: 'update'"
				command=$1
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
		diff -qsr "$CCCMK_PATH_MKFILES" "$command_arg_path/$project_mkpath" || echo ''
		if tree --version > /dev/null
		then
			tree -a   "$CCCMK_PATH_MKFILES"             > ./tree_ccc.txt
			tree -a "$command_arg_path/$project_mkpath" > ./tree_pwd.txt
			cccmk_diff "./tree_ccc.txt" "./tree_pwd.txt"
			rm ./tree_*.txt
		else
			print_warning "This computer has no 'tree' command installed, cannot display folder tree diff"
		fi
		if $verbose
		then
			mkfiles=`( cd "$CCCMK_PATH_MKFILES" ; find . -name '*.mk' -o -name '*.awk' )`
			for i in $mkfiles
			do
				if [ -f $command_arg_path/$project_mkpath/$i ]
				then
					print_message "mkfile differences: '$i'"
					cccmk_diff "$CCCMK_PATH_MKFILES/$i" "$command_arg_path/$project_mkpath/$i"
				fi
			done
		fi
		print_verbose "finished checking differences."
		;;

	update)
		for i in $command_arg_path
		do
			if ! [ -f "./$project_mkpath/$i" ]
			then
				print_error "Invalid filepath for 'cccmk update': ./$project_mkpath/$i"
				print_error "The path should be relative to the '$project_mkpath' folder"
				exit 1
			fi
			if ! cmp "$CCCMK_PATH_MKFILES/$i" "./$project_mkpath/$i"
			then
				cccmk_diff "$CCCMK_PATH_MKFILES/$i" "./$project_mkpath/$i"
				print_message "The file './$project_mkpath/$i' differs from the cccmk template (see diff above)"
				print_message "Your file is shown as old/red, and the latest cccmk template is shown as new/green."
				read -p "Are you sure you wish to overwrite './$project_mkpath/$i' ? [y/N]" response
				response=`echo "$response" | tr [:upper:] [:lower:]` # force lowercase
				case $response in
					y|ye|yes) response=true ;;
					n|no|'')  print_message "Operation cancelled." ; continue ;;
					*)        print_error "Invalid answer, should be either 'y'/'yes' or 'n'/'no'." ; exit 1 ;;
				esac
			else
				response=false
				print_message "The file './$project_mkpath/$i' is identical to the latest cccmk template."
			fi
			if $response
			then
				print_message "Updating file './$project_mkpath/$i'..."
				cp "$CCCMK_PATH_MKFILES/$i" "./$project_mkpath/$i"
			fi
		done
		;;

esac
