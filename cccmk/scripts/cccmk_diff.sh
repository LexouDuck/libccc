#!/bin/sh -e



if ! [ -z "$project_missing" ]
then print_error "The current folder is not a valid cccmk project folder (needed for command 'cccmk diff')"
exit 1
fi

print_message "folder differences:"

#! temporary folder used to check differences with source cccmk templates
diffchk_mkpath="$project_mkpath.tmp"
mkdir "$command_arg_path/$diffchk_mkpath"
# iterate over all mkfile folders
for dir in `list_subfolders "$CCCMK_PATH_MKFILES"`
do
	# copy over all files
	cp -r "$CCCMK_PATH_MKFILES/$dir" "$command_arg_path/$diffchk_mkpath/$dir"
	# iterate over all subfolders, and check '_if_*' folders to conditionally copy certain scripts
	for subdir in `list_subfolders "$command_arg_path/$diffchk_mkpath/$dir"`
	do
		case "$subdir" in
			_if_selected) # prompt the user to select which scripts they want
				proposed_scripts=`ls "$command_arg_path/$diffchk_mkpath/$dir/$subdir/" | sort --ignore-case | xargs`
				for i in $proposed_scripts
				do
					if contains "$project_scriptfiles" "$project_mkpath/$dir/$i"
					then
						mv  "$command_arg_path/$diffchk_mkpath/$dir/$subdir/$i" \
							"$command_arg_path/$diffchk_mkpath/$dir/$i"
					fi
				done
				;;
			_if_type_*) # only copy over files if $project_type matches folder name part after '_if_type_'
				if [ "$subdir" == "_if_type_$project_type" ]
				then
					mv  "$command_arg_path/$diffchk_mkpath/$dir/$subdir/"* \
						"$command_arg_path/$diffchk_mkpath/$dir/"
				fi
				;;
			*)	break
				;;
		esac
	done
	# cleanup up leftover '_if_*' folders
	rm -rf "$command_arg_path/$diffchk_mkpath/$dir/"_if_*
done

# show mkfile folder tree differences
if tree --version > /dev/null
then
	tree -L 2 -a "$command_arg_path/$diffchk_mkpath" > ./cccmk_tree_ccc.txt
	tree -L 2 -a "$command_arg_path/$project_mkpath" > ./cccmk_tree_cwd.txt
	diff -U-1 \
		./cccmk_tree_ccc.txt \
		./cccmk_tree_cwd.txt \
	>	./cccmk_tree_diff.txt \
	&&	cat ./cccmk_tree_diff.txt
	awk \
	-v path_old="$command_arg_path/$diffchk_mkpath/" \
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

# if verbose, show diffs for each non-identical file
if $verbose
then
	for i in $project_scripts
	do
		script_rev="`echo "$i" | cut -d':' -f 1 `"
		scriptfile="`echo "$i" | cut -d':' -f 2 `"
		script_if_="`echo "$i" | cut -d':' -f 3 `"
		if [ -f "$command_arg_path/$scriptfile" ]
		then
			print_message "mkfile differences: '$scriptfile'"
			templatefile=`echo "$diffchk_mkpath/$scriptfile" | sed "s|$project_mkpath/||"`
			cccmk_diff "$command_arg_path/$templatefile" "$command_arg_path/$scriptfile"
		fi
	done
fi

rm -rf "$command_arg_path/$diffchk_mkpath"
print_verbose "finished checking differences."
