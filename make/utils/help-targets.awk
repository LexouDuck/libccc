BEGIN {
	phony = 0;
}

{
	if (phony)
	{
		# TODO: make this spot documentation comments: `#!` and `#!<`
		sub(/#/,"\t#");
		phony = 0;
		print "make " $0;
	}
	else if (/^\.PHONY:\\/)
	{
		phony = 1;
	}
}
# TODO: implement special "block doc comments": `#!{` and `#!}`
