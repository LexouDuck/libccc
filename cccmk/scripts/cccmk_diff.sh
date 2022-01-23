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
	diffchk_cccpath=".cccmk_diff_old"
	diffchk_pwdpath=".cccmk_diff_new"
	mkdir "$diffchk_cccpath"
	mkdir "$diffchk_pwdpath"
	# copy over files to diffchk folders
	for i in $project_track
	do
		trackedfile_ccc_rev="`echo "$i" | cut -d':' -f 1 `"
		trackedfile_cccpath="`echo "$i" | cut -d':' -f 2 `"
		trackedfile_pwdpath="`echo "$i" | cut -d':' -f 3 `"
		mkdir -p "` dirname "$diffchk_cccpath/$trackedfile_pwdpath" `"
		mkdir -p "` dirname "$diffchk_pwdpath/$trackedfile_pwdpath" `"
		# replace %[vars]% in newly copied-over file
		cccmk_template \
			"$CCCMK_PATH_PROJECT/$trackedfile_cccpath" "$diffchk_cccpath/$trackedfile_pwdpath"
		if [ -f "./$trackedfile_pwdpath" ]
		then cp -p "./$trackedfile_pwdpath" "$diffchk_pwdpath/$trackedfile_pwdpath"
		fi
	done

	# show mkfile folder tree differences
	{
		diff -qrs -U-1 "$diffchk_cccpath" "$diffchk_pwdpath" \
		| awk \
		-v path_old="$diffchk_cccpath" \
		-v path_new="$diffchk_pwdpath" \
		'BEGIN {
			io_reset  = "\033[0m";
			io_red    = "\033[31m";
			io_green  = "\033[32m";
			io_yellow = "\033[33m";
		}
		{
			diffchar = " ";
			filepath = "";
			if (/^Files /)
			{
				filepath = substr($2, length(path_old) + 1);
				if (/ identical$/)   { diffchar = io_reset  " "; }
				else if (/ differ$/) { diffchar = io_yellow "!"; }
				else                 { diffchar = io_reset  "?"; }
			}
			else if (/^Only in /)
			{
				filepath = substr($3, 0, length(path_old));
				if (filepath == path_old) { diffchar = io_red   "-"; }
				if (filepath == path_new) { diffchar = io_green "+"; }
				filepath = substr($3, length(path_old) + 1);
				filepath = substr(filepath, 0, length(filepath) - 1);
				filepath = filepath "/" $4;
			}
			print diffchar " " filepath io_reset;
		}'
		echo ''
	}
	# if verbose, show diffs for each non-identical file
	if $verbose
	then
		for i in $project_track
		do
			trackedfile_ccc_rev="`echo "$i" | cut -d':' -f 1 `"
			trackedfile_cccpath="`echo "$i" | cut -d':' -f 2 `"
			trackedfile_pwdpath="`echo "$i" | cut -d':' -f 3 `"
			if [ -f "./$trackedfile_pwdpath" ]
			then
				print_message "mkfile differences: '$trackedfile_pwdpath'"
				cccmk_diff \
					"$diffchk_cccpath/$trackedfile_pwdpath" \
					"$diffchk_pwdpath/$trackedfile_pwdpath"
			fi
		done
	fi
	# cleanup diff folders
	rm -rf "$diffchk_cccpath"
	rm -rf "$diffchk_pwdpath"
)
print_verbose "finished checking differences."
