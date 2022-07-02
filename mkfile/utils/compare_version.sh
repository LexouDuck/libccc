#!/bin/sh -e

compare_version()
{
	if [ "$1" = "$2" ]
	then
		echo "eq"
		return 0
	fi
	local IFS=.
	local ver1=($1)
	local ver2=($2)
	local i
	# fill empty fields in ver1 with zeros
	for ((i=${#ver1[@]}; i<${#ver2[@]}; i++))
	do
		ver1[i]=0
	done
	for ((i=0; i<${#ver1[@]}; i++))
	do
		if [ -z "${ver2[i]}" ]
		then # fill any empty fields in ver2 with zeros
			ver2[i]=0
		fi
		if ((10#${ver1[i]} > 10#${ver2[i]}))
		then
			echo "gt"
			return 1
		fi
		if ((10#${ver1[i]} < 10#${ver2[i]}))
		then
			echo "lt"
			return 2
		fi
	done
	echo "eq"
	return 0
}

compare_version "$1" "$2"
exit $?
