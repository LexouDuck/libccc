#!/bin/awk

# This script creates a text file from a project template text file
# Essentially three syntaxes are accepted:
# 1. variable (string expansion): is replaced with the content of the variable named 'varname'
# 	%[varname]%
# 2. loop (array expansion): is replaced with 'n' lines, for each element of the 'array' variable
#	%%[varname]: 
# 3. conditional: is put into the output only if the condition evaluates to true
#	%%if[myfunc(foo,bar)]: ? TODO

function print_message(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[34m""message" "\033[0m: " message > "/dev/stderr"; }
function print_warning(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[33m""warning" "\033[0m: " message > "/dev/stderr"; }
function print_success(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[32m""success" "\033[0m: " message > "/dev/stderr"; }
function print_failure(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[31m""failure" "\033[0m: " message > "/dev/stderr"; }
function print_error(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[31m""error"   "\033[0m: " message > "/dev/stderr"; exit 1; }

function trim_l(str)	{ sub(/^[ \t\r\n]+/ , "", str); return str; }
function trim_r(str)	{ sub( /[ \t\r\n]+$/, "", str); return str; }
function trim(  str)	{ return trim_l(trim_r(str)); }



#! replaces variables in the given 'str', returns a new string
function template_variable(str)
{
	result = str;
	while (match(result, /%\[([a-zA-Z_]+)\]%/, matchvar))
	{
		if (matchvar[1] in vars)
		{
			sub("%\\[" matchvar[1] "\\]%", vars[matchvar[1]], result);
		}
		else
		{
			print_error("unknown variable used: " matchvar[1]);
			break;
		}
	}
	return result;
}



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
	# condition directive
	if (match($0, /^%%if[ \t]+([a-zA-Z_]+)\(([^\)]*)\)[ \t]*:/, matched))
	{
		if_function = matched[1];
		split(matched[2], if_arguments, /,[ \t]*/);
		if (_if(if_function, if_arguments))
		{
			print template_variable(substr($0, RSTART + RLENGTH));
		}
	}
	else if (/^%%if[ \t]+([a-zA-Z_]+)[^\(]/)
	{ print_error("expected parentheses after function for '%%if *():' condition directive"); }
	else if (/^%%if/)
	{ print_error("expected function name for '%%if *():' condition directive"); }
	else if (/%%if/)
	{ print_error("bad syntax - '%%if *():' condition directive should be at the beginning of the line"); }

	# loop directive
	else if (match($0, /^%%\[([a-zA-Z_]+)\]:/, matched))
	{
		if (matched[1] in vars)
		{
			split(vars[matched[1]], array, /[ \t\n]/);
			for (i in array)
			{
				line = substr($0, 1 + length(matched[0]));
				gsub(/%%/, array[i], line);
				print template_variable(line);
			}
		}
		else { print_error("unknown variable in loop directive: " matched[0]); }
	}
	else if (/^%%\[(.*)\]:/)
	{ print_error("expected array variable name for '%%[*]:' loop directive"); }
	else if (/^%%/)
	{ print_error("expected array variable name and brackets for '%%[*]:' loop directive"); }
	else if (/%%/)
	{ print_error("bad syntax - '%%[*]:' loop directive should be at the beginning of the line"); }

	# variable expansion
	else
	{
		print template_variable($0);
	}
}
