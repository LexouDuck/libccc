#!/bin/sh -e



if ! [ -z "$project_missing" ]
then print_error "The current folder is not a valid cccmk project folder (needed for command 'cccmk diff')"
exit 1
fi

print_message "folder differences:"
(
	cd "$command_arg_path"
	. "$project_cccmkfile"
	#! temporary folder used to check differences with source cccmk templates
	diffchk_oldpath=".cccmk_diff_old"
	diffchk_newpath=".cccmk_diff_new"
	mkdir "$diffchk_oldpath"
	mkdir "$diffchk_newpath"
	# copy over files to diffchk folders
	for i in $project_track
	do
		trackedfile_src_rev="`echo "$i" | cut -d':' -f 1 `"
		trackedfile_oldpath="`echo "$i" | cut -d':' -f 2 `"
		trackedfile_newpath="`echo "$i" | cut -d':' -f 3 `"
		mkdir -p "` dirname "$diffchk_oldpath/$trackedfile_newpath" `"
		mkdir -p "` dirname "$diffchk_newpath/$trackedfile_newpath" `"
		# replace %[vars]% in newly copied-over file
		cccmk_template \
			"$CCCMK_PATH_PROJECT/$trackedfile_oldpath" "$diffchk_oldpath/$trackedfile_newpath"
		cp -p                 "./$trackedfile_newpath" "$diffchk_newpath/$trackedfile_newpath"
	done

	# show mkfile folder tree differences
	if tree --version > /dev/null
	then
		tree -a "$diffchk_oldpath" > .cccmk_diff_tree_old.txt
		tree -a "$diffchk_newpath" > .cccmk_diff_tree_new.txt
		diff -U-1 \
			.cccmk_diff_tree_old.txt \
			.cccmk_diff_tree_new.txt \
		>	.cccmk_diff_tree.txt \
		&&	cat .cccmk_diff_tree.txt
		awk \
		-v path_old="$diffchk_oldpath/" \
		-v path_new="$diffchk_newpath/" \
		'BEGIN {
			io_reset  = "\033[0m";
			io_red    = "\033[31m";
			io_green  = "\033[32m";
			io_yellow = "\033[33m";
		}
		{
			if (/[└├](── )/)
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
		}' .cccmk_diff_tree.txt
		rm .cccmk_diff_tree*.txt
	else
		print_warning "This computer has no 'tree' command installed, cannot display folder tree diff"
		diff -qrs -U-1 "$diffchk_oldpath" "$diffchk_newpath" || print_message "There are differences, see above."
	fi
	# if verbose, show diffs for each non-identical file
	if $verbose
	then
		for i in $project_track
		do
			trackedfile_src_rev="`echo "$i" | cut -d':' -f 1 `"
			trackedfile_oldpath="`echo "$i" | cut -d':' -f 2 `"
			trackedfile_newpath="`echo "$i" | cut -d':' -f 3 `"
			if [ -f "./$trackedfile_newpath" ]
			then
				print_message "mkfile differences: '$trackedfile_newpath'"
				cccmk_diff \
					"$diffchk_oldpath/$trackedfile_newpath" \
					"$diffchk_newpath/$trackedfile_newpath"
			fi
		done
	fi
	# cleanup diff folders
	rm -rf "$diffchk_oldpath"
	rm -rf "$diffchk_newpath"
)
print_verbose "finished checking differences."
