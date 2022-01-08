#!/bin/sh -e



if ! [ -z "$project_missing" ]
then print_error "The current folder is not a valid cccmk project folder (needed for command 'cccmk diff')"
exit 1
fi

print_message "folder differences:"
#folder_diff=`diff -qsr "$CCCMK_PATH_MKFILES" "$command_arg_path/$project_mkpath" || echo ''`
if tree --version > /dev/null
then
	tree -L 2 -a   "$CCCMK_PATH_MKFILES"             > ./cccmk_tree_ccc.txt
	tree -L 2 -a "$command_arg_path/$project_mkpath" > ./cccmk_tree_pwd.txt
	diff -U-1 ./cccmk_tree_ccc.txt ./cccmk_tree_pwd.txt > ./cccmk_tree_diff.txt && cat ./cccmk_tree_diff.txt
	awk \
	-v path_old="$CCCMK_PATH_MKFILES/" \
	-v path_new="$command_arg_path/$project_mkpath/" \
	'BEGIN {
		io_reset  = "\033[0m";
		io_red    = "\033[31m";
		io_green  = "\033[32m";
		io_yellow = "\033[33m";
	}
	{
		if (!/\.[a-z]+$/ && !/_[a-zA-Z_]+$/)
		{
			folder = $NF "/";
		}
		else if (/^ /)
		{
			file_old = path_old folder $NF;
			file_new = path_new folder $NF;
			if (system("cmp -s " file_old " " file_new))
			{ $0 = "~" substr($0, 2); }
		}
		     if (/^ /)  { print io_reset  $0; }
		else if (/^~/)  { print io_yellow $0 io_reset; }
		else if (/^\+/) { print io_green  $0 io_reset; }
		else if (/^\-/) { print io_red    $0 io_reset; }
		else { print; }
	}' ./cccmk_tree_diff.txt
	rm ./cccmk_tree_*.txt
else
	print_warning "This computer has no 'tree' command installed, cannot display folder tree diff"
fi
if $verbose
then
	mkfiles=`( cd "$CCCMK_PATH_MKFILES" ; find . -name '*.mk' -o -name '*.awk' )`
	for i in $mkfiles
	do
		if [ -f "$command_arg_path/$project_mkpath/$i" ]
		then
			print_message "mkfile differences: '$i'"
			cccmk_diff "$CCCMK_PATH_MKFILES/$i" "$command_arg_path/$project_mkpath/$i"
		fi
	done
fi
print_verbose "finished checking differences."
