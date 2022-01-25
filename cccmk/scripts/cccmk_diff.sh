#!/bin/sh -e



if ! [ -z "$project_missing" ]
then
	print_error "The current folder is not a valid cccmk project folder (needed for command 'cccmk diff')"
	exit 1
else . "$project_cccmkfile"
fi

#! current project folder
path_pwd="."
#! local cccmk install folder which stores the project template
path_ccc="$CCCMK_PATH_PROJECT"

#! list of files to be diff-checked
request_files=""


#! list of all tracked files in the current project
tracked_files=""

for i in $project_track
do
#	trackedfile_ccc_rev="`echo "$i" | cut -d':' -f 1 `"
#	trackedfile_cccpath="`echo "$i" | cut -d':' -f 2 `"
	trackedfile_pwdpath="`echo "$i" | cut -d':' -f 3 `"
	tracked_files="$tracked_files $trackedfile_pwdpath"
done

if [ -z "$command_arg_path" ]
then
	print_verbose "No scripts filepath(s) given, so all tracked mkfile scripts will be updated."
	request_files="$tracked_files"
else
	# iterate over all user-specified files, to populate 'request_files'
	for i in $command_arg_path
	do
		if ! [ -z "` echo $tracked_files | grep "$i" `" ]
		then
			if [ -d "$i" ] # if this is a folder, recursively add any tracked files inside
			then
				for f in $tracked_files
				do
					if ! [ -z "` echo $f | grep "^$i/" `" ]
					then request_files="$request_files $f"
					fi
				done
			elif [ -f "$i" ] # if this is a regular file, add it
			then
				request_files="$request_files $i"
			else # the file/folder doesnt exist
				request_files="$request_files $i"
			fi
		else print_warning "File is not tracked by '$project_cccmkfile' file: '$i'"
		fi
	done
fi



print_message "Overview of differences:"
(
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
		if ! [ -z "$command_arg_path" ]
		then
			if [ -z "` echo $request_files | grep -w "$trackedfile_pwdpath" `" ]
			then continue # user did not ask for this file
			fi
		fi
		mkdir -p "` dirname "$diffchk_cccpath/$trackedfile_pwdpath" `"
		mkdir -p "` dirname "$diffchk_pwdpath/$trackedfile_pwdpath" `"
		actual_cccpath="$CCCMK_PATH_PROJECT"
		actual_pwdpath="."
		# replace %[vars]% in newly copied-over file
		if [ -f             "$actual_cccpath/$trackedfile_cccpath" ]
		then cccmk_template "$actual_cccpath/$trackedfile_cccpath" "$diffchk_cccpath/$trackedfile_pwdpath"
		fi
		if [ -f             "$actual_pwdpath/$trackedfile_pwdpath" ]
		then cp -p          "$actual_pwdpath/$trackedfile_pwdpath" "$diffchk_pwdpath/$trackedfile_pwdpath"
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
			if ! [ -z "$command_arg_path" ]
			then
				if [ -z "` echo $request_files | grep -w "$trackedfile_pwdpath" `" ]
				then continue # user did not ask for this file
				fi
			fi
			# show full file diff
			if [ -f "./$trackedfile_pwdpath" ]
			then
				print_message "Tracked file differences: '$trackedfile_pwdpath'"
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
