#!/bin/awk

# This script is used to print summary diffs of folders
# It expects to receive a brief diff command's output as input, and two variables: the folderpaths
# For greater clarity, here is an example of how this script should be called:
#	$ diff -qrs -U-1 "$old" "$new" \
#		| awk \
#		-v path_old="$old" \
#		-v path_new="$new" \
#		-f util.awk
#		-f diff.awk



function diffcmd(file_old, file_new)
{
	# execute diff over both files
	result = command("diff " file_old " " file_new);
	# escape all single-quotes in diff
	gsub(/'/, "'\"'\"'", result);
	# get total amount of additions/deletions in the diff
	result_del = trim(command("echo '" result "' | grep '^[<] ' | wc -l"));
	result_add = trim(command("echo '" result "' | grep '^[>] ' | wc -l"));
	# display additions/deletions as red/green numbers respectively
	return " (" io_red "-" result_del io_reset ";" io_green "+" result_add io_reset ")" ;
}



BEGIN {
	io_reset  = "\033[0m";
	io_red    = "\033[31m";
	io_green  = "\033[32m";
	io_yellow = "\033[33m";
}

{
	diffchar = " ";
	filepath = "";
	details = "";
	if (/^Files /)
	{
		filepath = substr($2, length(path_old) + 1);
		if (/ differ$/) {
			details = diffcmd(path_old filepath, path_new filepath);
			diffchar = io_yellow "!";
		}
		else if (/ identical$/)
		{ diffchar = io_reset  " "; }
		else
		{ diffchar = io_reset  "?"; }
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
	print diffchar " " filepath io_reset details;
}