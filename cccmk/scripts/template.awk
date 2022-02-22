#!/bin/awk

# This script creates a text file from a project template text file
# Here is an example of how this script should be called:
#	$ awk \
#		-v variables=" foo=FOO; bar=BAR; " \
#		-v functions=" myfunc1(2) myfunc2(0) " \
#		-f "util.awk" \
#		-f "template-functions.awk" \
#		-f "template.awk" \
#		"$inputfile"
#
# As for the syntax of the template file's contents, essentially 3 directives are accepted:
# 1. variable (string expansion): is replaced with the content of the variable named 'varname'
# 	%[varname]%
# 2. loop (array expansion): is replaced with 'n' lines, for each element of the 'array' variable
#	%%[varname]: 
# 3. conditional: is put into the output only if the condition evaluates to true
#	%%if[myfunc(foo,bar)]: ? TODO



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
