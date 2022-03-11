#!/bin/awk

# This file stores a set of general utility functions for awk scripts



###
### String manipulation
###

#! Removes any whitespace characters from the right end of a string
function trim_l(str)
{
	sub(/^[ \t\r\n]+/ , "", str);
	return str;
}

#! Removes any whitespace characters from the left end of a string
function trim_r(str)
{
	sub(/[ \t\r\n]+$/, "", str);
	return str;
}

#! Removes any whitespace characters from both ends of string
function trim(str)
{
	return trim_l(trim_r(str));
}



###
### IO/logging
###

function print_message(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[34m""message" "\033[0m: " message > "/dev/stderr"; }
function print_warning(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[33m""warning" "\033[0m: " message > "/dev/stderr"; }
function print_success(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[32m""success" "\033[0m: " message > "/dev/stderr"; }
function print_failure(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[31m""failure" "\033[0m: " message > "/dev/stderr"; }
function print_error(message)	{ print "cccmk-template["FILENAME":"NR"]: ""\033[31m""error"   "\033[0m: " message > "/dev/stderr";
	exit 1;
}



###
### Shell commands
###

#! This function executes a shell command, and returns the stdout output as a string
function command(cmd)
{
	output = "";
	line = "";
	while (( cmd | getline line ) > 0)
	{
		output = output "\n" line;
	}
	close(cmd);
	return (output);
}
