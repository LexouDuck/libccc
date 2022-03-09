# This script parses a makefile for to display a summary of what it contains

BEGIN {
	io_reset  = "\033[0m";
	io_red    = "\033[31m";
	io_green  = "\033[32m";
	io_yellow = "\033[33m";

	regex_token = "[a-zA-Z0-9_]+";
	regex_space = "[ \\t\\r\\n]*";
	regex_equal = "[:+?]?=";
	regex_variable_def = "^" regex_space regex_token regex_space regex_equal;
	regex_variable_use = "\\$\\(" "(call )?" regex_token "\\)";
}

{
	# update the line number string
	lineno = " line " NR ":\t";
	# display any makefiles included on this line
	if (/^-?include/)
	{
		for (i = 2; i <= NF; i++)
		{
			print lineno "includes: " $i;
		}
	}
	# display any variable defined on this line
	if ($0 ~ regex_variable_def)
	{
		sub(regex_equal, " ");
		key = $1;
		variables[key] = substr($0, index($0, $2));
		print lineno "defines: " key;
	}
	# display any variable used on this line
	remaining = $0;
	while (length(remaining) > 0)
	{
		if (match(remaining, regex_variable_use))
		{
			if (RLENGTH > 4) # skip 1-char variables like $(1) or $(i)
			{
				var = substr(remaining, RSTART, RLENGTH);
				key = substr(var, 3, length(var) - 3);
				sub(/call /, "", key);
				if (key in variables)
				{ print io_reset lineno "uses: " var io_reset; }
				else
				{ print io_yellow lineno "uses: " var " - undefined" io_reset; }
			}
			remaining = substr(remaining, RSTART + RLENGTH);
		}
		else remaining = "";
	}
}
