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
#
# 1. variable (string expansion): is replaced with the content of the variable named 'varname'
#	%[varname]%
#
# 2. loop (array expansion): is replaced with 'n' lines, for each element of the 'array' variable
#	%%for (varname): // (single-line version) some code here
#	%%for (varname)
#	// (multi-line version) some code here
#	%%end for
#
# 3. conditional: is put into the output only if the condition evaluates to true
#	%%if myfunc(foo,bar): // (single-line version) some code here
#	%%if myfunc(foo,bar)
#	// (multi-line version) some code here
#	%%end if



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
	if (/^%%/)
	{ print_warning("unknown template directive, found '%%' at the beginning of the line"); }
	else
	{
		print template_variable($0);
	}
}
