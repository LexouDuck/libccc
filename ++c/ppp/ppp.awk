# This is an initial prototype version of the ++C transpiler

# util functions

function trim_l(str)	{ sub(/^[ \t\r\n]+/, "", str); return str; }
function trim_r(str)	{ sub(/[ \t\r\n]+$/, "", str); return str; }
function trim(str)	{ return trim_l(trim_r(str)); }

function arraylength(array)
{
	n = 0;
	for (i in array)
	{
		n++;
	}
	return n;
}

# shell utils


function print_info(str)	{ print FILENAME ":" NR ": " str >> "/dev/stderr"; }
function print_warn(str)	{ print_info("\033[0;33m" "WARNING" "\033[0m" ": " str); }
function print_error(str)	{ print_info("\033[0;31m" "ERROR"   "\033[0m" ": " str); }



BEGIN {
	context_stack = "global";
	context_namespace = "";
}

{
	# pointer dereference
	gsub(/\$/, "*");
	# pointer get_address
	gsub(/@/, "&");

	# number literal: octal
	gensub(/\<0o([01234567]+)\>/, "0\\1", "g");
	# number literal: binary
	if (match($0, /\<0b([01]+)\>/))
	{
		number = substr($0, RSTART + 2, RLENGTH - 2);
		gensub(/\<0b([01]+)\>/, sprintf("0x%X", 0+number), "g");
	}

	# cross-platform keywords
	gsub(/\<asm\>/,      "__asm__");
	gsub(/\<inline\>/,   "__inline__");
	gsub(/\<restrict\>/, "__restrict__");

	if (/^\s*#\s*/) # preprocessor directive
	{
		ppline = $0;
		sub(/^\s*#\s*/, "");
		if (length($0) == 0)
		{
			print_error("empty preprocessor directive line");
		}
		else if (/header/)
		{
			sub(/header/, "");
			header = trim($0);
			if (header ~ /[^a-zA-Z0-9_]/)
				print_error("ppp directive 'header' should have one token argument, instead found: " header);
			print_warn("found header: " header);
			$0 = "#ifndef " header "\n" "#define " header;
		}
		else if (/namespace/)
		{
			sub(/namespace/, "");
			namespace_def = trim($0);
			namespace_generic = index(namespace_def, "<");
			namespace = (namespace_generic > 0) ?
				substr(namespace_def, 0, namespace_generic - 1) :
				namespace_def;
			print_warn("found namespace: " namespace);
			$0 = "";
		}
		else $0 = ppline;
	}
	print;
}

END {
	if (header != "")
	{
		print "\n" "#endif /* " header " */";
	}
}
