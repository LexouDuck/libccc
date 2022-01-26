# This script creates a text file from a project template text file
# Essentially two syntaxes are accepted:
# 	%[varname]%	is replaced with the content of the variable named 'varname'
#	%%[array]:	is replaced with 'n' lines, for each element of the 'array' variable

function print_message(message)	{ print "cccmk-template: ""\033[34m""message" "\033[0m: " message > "/dev/stderr"; }
function print_warning(message)	{ print "cccmk-template: ""\033[33m""warning" "\033[0m: " message > "/dev/stderr"; }
function print_success(message)	{ print "cccmk-template: ""\033[32m""success" "\033[0m: " message > "/dev/stderr"; }
function print_error(  message)	{ print "cccmk-template: ""\033[31m""error"   "\033[0m: " message > "/dev/stderr"; }

function trim_l(str)	{ sub(/^[ \t\r\n]+/ , "", str); return str; }
function trim_r(str)	{ sub( /[ \t\r\n]+$/, "", str); return str; }
function trim(  str)	{ return trim_l(trim_r(str)); }

# This script expects some variables to be predefined via the `variables`
# `variables` should have keys/values separated with '=' symbols, and different assignements by ';'
# example: awk -v variables='foo="bar";hello="world";'
BEGIN {
	vars_amount = split(variables, vars, ";");
	for (i in vars)
	{
		var_name  = trim(substr(vars[i], 1, index(vars[i], "=") - 1));
		var_value = trim(substr(vars[i],    index(vars[i], "=") + 1));
		vars[var_name] = var_value;
		#print_message("template variable set: " var_name " = " var_value);
	}
}

{
	if (match($0, /^%%\[([a-zA-Z_]+)\]:/, matched))
	{
		if (matched[1] in vars)
		{
			split(vars[matched[1]], array, /[ \t\n]/);
			for (i in array)
			{
				line = substr($0, length(matched[0]) + 1);
				gsub(/%/, array[i], line);
				print line;
			}
		}
		else { print_error("unknown variable in loop directive: " matched[0]); }
	}
	else if (/^%%\[(.*)\]:/)
	{ print_error("expected variable name after '%%[_]:' loop directive"); }
	else if (/^%%/)
	{ print_error("expected variable name and colon for '%%[_]:' loop directive"); }
	else if (/%%/)
	{ print_error("bad syntax - '%%[_]:' loop directive should be at the beginning of the line"); }
	else
	{
		while (match($0, /%\[([a-zA-Z_]+)\]%/, matched))
		{
			if (matched[1] in vars)
			{
				sub("%\\[" matched[1] "\\]%", vars[matched[1]], $0);
			}
			else
			{
				print_error("unknown variable used: " matched[1]);
				break;
			}
		}
		print;
	}
}
