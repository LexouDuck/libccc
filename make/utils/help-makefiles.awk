BEGIN {
	printed = 0;
}

{
	if (/^#!/)
	{
		print "#" substr($0, 2);
		printed += 1;
	}
	else if (/^#/)
	{}
	else if (printed > 0)
	{
		exit 0;
	}
	else
	{
		print "";
		exit 0;
	}
}
