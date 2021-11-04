BEGIN {
	doc = "";
	prevline = "";
}

match($0, /#!</)	{ doc = substr($0, RSTART + 4); }
match($0, /#![^<]/)	{ doc = substr($0, RSTART + 3); }

{
	if (!$0)
	{
		doc = "";
	}
	else if (/=/)
	{
		if (doc != "")
		{
			print $1 "\t" color "# " doc reset;
		}
		doc = "";
	}
	prevline = $0;
}
# TODO: implement special "block doc comments": `#!{` and `#!}`
