# This script parses a makefile for any '#!' doc comments for any defined variables

BEGIN {
	doc = "";
	docblock = 0;
}

{
	if (match($0, /^#! /) != 0)
	{
		doc = substr($0, RSTART + 3);
	}

	if (/^#{/ || /^#!{/)	{ docblock = 1; }
	if (/^#}/ || /^#!}/)	{ docblock = 0; }

	if ($0 == "")
	{
		if (docblock == 0) doc = "";
	}
	else if (/=/)
	{
		if (match($0, /#!< /) != 0)
		{
			doc = substr($0, RSTART + 4);
		}
		if (doc != "")
		{
			sub(/=/, " ");
			print $1 "\t" color "#! " doc reset;
		}
		if (docblock == 0) doc = "";
	}
}
