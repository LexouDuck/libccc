#!/bin/sh -e



#! Check if a space-separated list contains a certain string
contains()
{
	if [ -t 0 ] && [ $# -gt 1 ]
	then
		echo "$1" | grep -w -q "$2"
	else
		while read line
		do
			echo "$1" | grep -w -q "$line"
		done
	fi
}

#! Keep only certain items from the space-separated list given as input
filter()
{
	filter_inner()
	(
		for i in $2
		do
			$1 "$i" && echo "$i"
		done
	)
	if [ -t 0 ] && [ $# -gt 1 ]
	then
		filter_inner $1 "$2"
	else
		while read line
		do
			filter_inner $1 "$line"
		done
	fi
}



#! Call AWK on a file, modifying it in-place
awk_inplace()
{
	local file="$1"
	local temp="$1.tmp"
	shift 1
	awk "$@" "$file" > "$temp"
	mv "$temp" "$file"
}



#! List all regular files contained inside the given folder (no hidden files, nor folders, nor symlinks etc)
list_onlyfiles()
{
	( cd "$1" && ls -ap 2> /dev/null || echo '' ) \
	| grep -v '/' \
	| xargs
}

#! List subfolders of a folder, with no leading prefix (just the name of each folder)
list_subfolders()
{
	( cd "$1" && ls -ap 2> /dev/null || echo '' ) \
	| grep '.*/' \
	| grep -v '^\.*/$' \
	| tr '/' ' ' \
	| xargs 
}



# user interface/prompting

#! prompts the user to input some text
#! @param $1	retval: name of the return value variable
#! @param $2	helpmsg: message to display to explain the text to type (typically in brackets)
prompt_text()
{
	local retval=$1
	local answer
	local helpmsg="$2"
	if [ -z "$helpmsg" ]
	then helpmsg="[<ENTER> to confirm and proceed]"
	fi
	echo "$helpmsg"
	read -p "> " answer
	eval $retval='${answer}'
}



#! prompts a yes/no question for the user
#! @param $1	retval: name of the return value variable
#! @param $2	default: default answer value ('y'/'n'/'')
prompt_question()
{
	local retval=$1
	local answer
	local default="`echo "$2" | tr [:upper:] [:lower:]`" # force lowercase
	if [ -z "$default" ]
	then echo '[y/n]'
	elif [ "$default" == 'y' ]
	then echo '[Y/n]'
	elif [ "$default" == 'n' ]
	then echo '[y/N]'
	else
		print_error "bad call to prompt_question(), 'default' arg should be 'y','n', or nothing"
		exit 1
	fi
	read -p "> " answer
	answer=`echo "$answer" | tr [:upper:] [:lower:]` # force lowercase
	case $answer in
		y|ye|yes|t|true)
			answer=true
			;;
		n|no|f|false)
			answer=false
			;;
		'')
			if [ -z "$default" ]
			then
				print_error "Invalid answer, should be either 'y'/'yes' or 'n'/'no'."
				exit 1
			elif [ "$default" == 'y' ]
			then answer=true
			elif [ "$default" == 'n' ]
			then answer=false
			fi
			print_message "Default option ('$default') selected."
			;;
		*)
			print_error "Invalid answer, should be either 'y'/'yes' or 'n'/'no'."
			exit 1
			;;
	esac
	eval $retval='${answer}'
}



# little helpers for terminal print control and key input
ESC=$(printf "\033")
cursor_blink_on()   { printf "$ESC[?25h"; }
cursor_blink_off()  { printf "$ESC[?25l"; }
cursor_to()         { printf "$ESC[$1;${2:-1}H"; }
print_inactive()    { printf "$1   $2 "; }
print_active()      { printf "$1  $ESC[7m $2 $ESC[27m"; }
get_cursor_row()    { IFS=';' read -sdR -p $'\E[6n' ROW COL; echo ${ROW#*[}; }
key_input()
{
	local key
	IFS= read -rsn1 key 2>/dev/null >&2
	case "$key" in
		(0) echo 0 ;;
		(1) echo 1 ;;
		(2) echo 2 ;;
		(3) echo 3 ;;
		(4) echo 4 ;;
		(5) echo 5 ;;
		(6) echo 6 ;;
		(7) echo 7 ;;
		(8) echo 8 ;;
		(9) echo 9 ;;
		("")      echo enter ;;
		($'\x20') echo space ;;
		($'\x1B') 
			read -rsn2 key
			case "$key" in
				('[A') echo up    ;;
				('[B') echo down  ;;
				('[C') echo left  ;;
				('[D') echo right ;;
			esac
			;;
	esac
}

#! Presents a single-select list prompt to the user
#! @param $1	retval: return value variable name
#! @param $2	options: list of selectable values (colon-separated string)
#! @param $3	default: initially selected value
prompt_select()
{
	echo "Select one item in the list below. The controls are:"
	echo "[<ESCAPE> to cancel/abort operation]"
	echo "[<UP>/<DOWN> to move selection cursor]"
	echo "[<ENTER> or <SPACE> to select and proceed]"
	local retval=$1
	local options
	local default

	IFS=';' read -r -a options <<< "$2"
	if [[ -z $3 ]]
	then default=
	else IFS=';' read -r -a default <<< "$3"
	fi
	local selected

	for ((i=0; i<${#options[@]}; i++))
	do
		printf "\n"
	done

	# determine current screen position for overwriting the options
	local lastrow=`get_cursor_row`
	local startrow=$(($lastrow - ${#options[@]}))

	# ensure cursor and input echoing back on upon a ctrl+c during read -s
	trap "cursor_blink_on; stty echo; printf '\n'; exit" 2
	cursor_blink_off

	local active=0
	while true; do
		# print options by overwriting the last lines
		local idx=0
		for option in "${options[@]}"
		do
			cursor_to $(($startrow + $idx))
			if [ $idx -eq $active ]
			then print_active   "> " "$option" "$description"
			else print_inactive "  " "$option" "$description"
			fi
			((idx++))
		done

		# user key control
		case `key_input` in
			(space)
				selected="${options[active]}"
				break
				;;
			(enter)
				selected="${options[active]}"
				break
				;;
			(up)
				((active--));
				if [ $active -lt 0 ]
				then active=$((${#options[@]} - 1))
				fi
				;;
			(down)
				((active++));
				if [ $active -ge ${#options[@]} ]
				then active=0
				fi
				;;
		esac
	done

	# cursor position back to normal
	cursor_to $lastrow
	printf "\n"
	cursor_blink_on

	eval $retval='${selected}'
}



#! Presents a multi-select list prompt to the user
#! @param $1	retval: return value variable name
#! @param $2	options: list of selectable values (colon-separated string)
#! @param $3	defaults: list of default values (space-separated, true/false)
prompt_multiselect()
{
	echo "Select any items in the list below. The controls are:"
	echo "[<ESCAPE> to cancel/abort operation]"
	echo "[<UP>/<DOWN> to move selection cursor]"
	echo "[<SPACE> to toggle selected checkbox]"
	echo "[<ENTER> to confirm and proceed]"
	local retval=$1
	local options
	local defaults

	IFS=';' read -r -a options <<< "$2"
	if [[ -z $3 ]]
	then defaults=()
	else IFS=';' read -r -a defaults <<< "$3"
	fi
	local selected=()

	for ((i=0; i<${#options[@]}; i++))
	do
		selected+=("${defaults[i]}")
		printf "\n"
	done

	toggle_option()
	{
		local arr_name=$1
		eval "local arr=(\"\${${arr_name}[@]}\")"
		local option=$2
		if [ -z ${arr[option]} ]
		then arr[option]=${options[$option]}
		else arr[option]=
		fi
		eval $arr_name='("${arr[@]}")'
	}

	# determine current screen position for overwriting the options
	local lastrow=`get_cursor_row`
	local startrow=$(($lastrow - ${#options[@]}))

	# ensure cursor and input echoing back on upon a ctrl+c during read -s
	trap "cursor_blink_on; stty echo; printf '\n'; exit" 2
	cursor_blink_off

	local active=0
	while true; do
		# print options by overwriting the last lines
		local idx=0
		for option in "${options[@]}"
		do
			local prefix="[ ]"
			if [[ ${selected[idx]} == $option ]]
			then prefix="[x]"
			fi
			cursor_to $(($startrow + $idx))
			if [ $idx -eq $active ]
			then print_active   "> $prefix" "$option" "$description"
			else print_inactive "  $prefix" "$option" "$description"
			fi
			((idx++))
		done

		# user key control
		case `key_input` in
			(space)
				toggle_option selected $active
				;;
			(enter)
				break
				;;
			(up)
				((active--));
				if [ $active -lt 0 ]
				then active=$((${#options[@]} - 1))
				fi
				;;
			(down)
				((active++));
				if [ $active -ge ${#options[@]} ]
				then active=0
				fi
				;;
		esac
	done

	# cursor position back to normal
	cursor_to $lastrow
	printf "\n"
	cursor_blink_on

	selected=`echo "${selected[@]}" | xargs`
	eval $retval='$selected'
}
