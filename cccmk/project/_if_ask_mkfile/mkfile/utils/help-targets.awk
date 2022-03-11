# This script parses a makefile for any '#!' doc comments for any .PHONY makefile targets

BEGIN {
	phony = 0;
}

{
	if (phony)
	{
		# TODO: make this spot documentation comments: `#!` and `#!<`
		sub(/#/, "\t" color "#");
		phony = 0;
		print "make " $0 reset;
	}
	else if (/^\.(PHONY|INTERMEDIATE):\\/)
	{
		phony = 1;
	}
}
# TODO: implement special "block doc comments": `#!{` and `#!}`
