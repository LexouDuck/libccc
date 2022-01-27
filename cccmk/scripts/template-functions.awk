#!/bin/awk

# This script contains custom functions for the `template.awk` script



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
		if (array[i] ~ "^[^:]*:" filepath ":(.*)$")
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
	else if (funcname == "is"     ) { return _if_is(arguments[1], arguments[2]); }
	else if (funcname == "matches") { return _if_matches(arguments[1], arguments[2]); }
	else if (funcname == "tracked") { return _if_tracked(arguments[1]); }
}
