BEGIN {
	doc = "";
}

{
	if (match($0, /^#! /) != 0)
	{
		doc = substr($0, RSTART + 3);
	}
	if ($0 == "")
	{
		doc = "";
	}
	else if (/=/)
	{
		if (match($0, /#!< /) != 0)
		{
			doc = substr($0, RSTART + 4);
		}
		if (doc != "")
		{
			print $1 "\t" color "#! " doc reset;
		}
		doc = "";
	}
}
# TODO: implement special "block doc comments": `#!{` and `#!}`
