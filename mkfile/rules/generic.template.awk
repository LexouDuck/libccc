#!/bin/awk

# This script creates a text file from a project template text file
# Here is an example of how this script should be called:
#	$ awk \
#		-v variables=" foo=FOO; bar=BAR; " \
#		-f "util.awk" \
#		-f "template-functions.awk" \
#		-f "template.awk" \
#		"$inputfile"
#
# As for the syntax of the template file's contents, essentially 3 directives are accepted:
#
# 1. variable (string expansion): is replaced with the content of the variable named 'varname'
#	%[varname]%
#
# 2. loop (array expansion): is replaced with 'n' lines, for each element of the 'array' variable
#	%%for (varname): // (single-line version) some code here
#	%%for (varname)
#	// (multi-line version - note the absence of ':') some code here
#	%%end for
#
# 3. conditional: is put into the output only if the condition evaluates to true
#	%%if myfunc(foo,bar): // (single-line version) some code here
#	%%if myfunc(foo,bar)
#	// (multi-line version - note the absence of ':') some code here
#	%%end if



###
### String manipulation
###

#! Removes any whitespace characters from the right end of a string
function trim_l(str)
{
	sub(/^[ \t\r\n]+/ , "", str);
	return str;
}

#! Removes any whitespace characters from the left end of a string
function trim_r(str)
{
	sub(/[ \t\r\n]+$/, "", str);
	return str;
}

#! Removes any whitespace characters from both ends of string
function trim(str)
{
	return trim_l(trim_r(str));
}



###
### IO/logging
###

function print_message(message)	{ print "cccmk-awk["FILENAME":"NR"]: ""\033[34m""message" "\033[0m: " message > "/dev/stderr"; }
function print_warning(message)	{ print "cccmk-awk["FILENAME":"NR"]: ""\033[33m""warning" "\033[0m: " message > "/dev/stderr"; }
function print_success(message)	{ print "cccmk-awk["FILENAME":"NR"]: ""\033[32m""success" "\033[0m: " message > "/dev/stderr"; }
function print_failure(message)	{ print "cccmk-awk["FILENAME":"NR"]: ""\033[31m""failure" "\033[0m: " message > "/dev/stderr"; }
function print_error(message)	{ print "cccmk-awk["FILENAME":"NR"]: ""\033[31m""error"   "\033[0m: " message > "/dev/stderr";
	exit 1;
}



###
### Shell commands
###

#! This function executes a shell command, and returns the stdout output as a string
function command(cmd)
{
	output = "";
	line = "";
	while (( cmd | getline line ) > 0)
	{
		output = output "\n" line;
	}
	close(cmd);
	return (output);
}



###
### Custom template functions
###

#! checks if the given 'varname' contains a string value which is identical to 'str'
function _if_is(varname, str)
{
	return (vars[varname] == str);
}

#! checks if the given 'varname' contains a string value which is matched by the given 'regexp'
function _if_matches(varname, regexp)
{
	return (vars[varname] ~ regexp);
}

#! checks if the given 'filepath' is tracked by the cccmk 'project_track' variable
function _if_tracked(filepath)
{
	split(vars["track"], array, /[ \t\n]/);
	for (i in array)
	{
		if (array[i] ~ "^[^:]*:" filepath)
		{
			return (1);
		}
	}
	return (0);
}



# entry point function, used to call all others
function _if(funcname, arguments)
{
	if (length(funcname) == 0) { return; }
	else if (funcname == "true"   ) { return (1); }
	else if (funcname == "false"  ) { return (0); }
	else if (funcname == "is"     ) { return _if_is(     arguments[1], arguments[2]); }
	else if (funcname == "matches") { return _if_matches(arguments[1], arguments[2]); }
	else if (funcname == "tracked") { return _if_tracked(arguments[1]); }
}



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
			print_warning("unknown variable used: " matchvar[1]);
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
	lines_if = "";
	scope_if = 0;
	lines_for = "";
	scope_for = 0;
}



{
	# loop directive
	if (scope_for != 0)
	{
		if (/^%%end[ \t]+for[ \t]*$/)
		{
			for (i in array)
			{
				line = substr(lines_for, 1, length(lines_for) - 1);
				gsub(/%%/, array[i], line);
				print template_variable(line);
			}
			lines_for = "";
			scope_for = 0;
		}
		else
		{
			line = $0;
			gsub(/%%/, array[i], line);
			lines_for = lines_for template_variable($0) "\n";
		}
		next;
	}
	else if (match($0, /^%%for[ \t]+\(([a-zA-Z_]+)\)[ \t]*/, matched))
	{
		if (matched[1] in vars)
		{
			split(vars[matched[1]], array, /[ \t\n]/);
			# single-line
			if (/^%%for[ \t]+\(([a-zA-Z_]+)\):/)
			{
				for (i in array)
				{
					line = substr($0, 2 + length(matched[0]));
					gsub(/%%/, array[i], line);
					print template_variable(line);
				}
			}
			else # multi-line
			{
				lines_for = "";
				scope_for = 1;
			}
			next;
		}
		else { print_error("unknown variable in loop directive: " matched[0]); }
	}
	else if (/^%%for[ \t]+\((.*)\):/)
	{ print_error("expected array variable name for '%%for(*):' loop directive"); }
	else if (/^%%for/)
	{ print_error("expected array variable name and brackets for '%%for(*):' loop directive"); }
	else if (/%%for/)
	{ print_error("bad syntax - '%%for(*):' loop directive should be at the beginning of the line"); }



	# condition directive
	if (scope_if != 0)
	{
		if (/^%%end[ \t]+if[ \t]*$/)
		{
			if (scope_if == 1)
			{
				line = substr(lines_if, 1, length(lines_if) - 1);
				print line;
			}
			lines_if = "";
			scope_if = 0;
		}
		else
		{
			lines_if = lines_if template_variable($0) "\n";
		}
		next;
	}
	else if (match($0, /^%%if[ \t]+([a-zA-Z_]+)\(([^\)]*)\)[ \t]*/, matched))
	{
		if_function = matched[1];
		split(matched[2], if_arguments, /,[ \t]*/);
		if (_if(if_function, if_arguments))
		{ scope_if = 1; }
		else
		{ scope_if = 2; }
		# single-line
		if (/^%%if[ \t]+([a-zA-Z_]+)\(([^\)]*)\)[ \t]*:/)
		{
			if (scope_if == 1)
			{ print template_variable(substr($0, RSTART + RLENGTH + 1)); }
			scope_if = 0;
		}
		else # multi-line
		{
			lines_if = "";
		}
		next;
	}
	else if (/^%%if[ \t]+([a-zA-Z_]+)[^\(]/)
	{ print_error("expected parentheses after function for '%%if *(*):' condition directive"); }
	else if (/^%%if/)
	{ print_error("expected function name for '%%if *(*):' condition directive"); }
	else if (/%%if/)
	{ print_error("bad syntax - '%%if *(*):' condition directive should be at the beginning of the line"); }



	# variable expansion
	if (/^%%end/)
	{ print_warning("found stray '" $0 "' command with no preceding multi-line directive"); }
	else if (/^%%/)
	{ print_warning("unknown template directive, found '%%' at the beginning of the line"); }
	else
	{
		print template_variable($0);
	}
}
