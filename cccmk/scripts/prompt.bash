#!/bin/bash -e



#! prompts the user to input some text
#! @param $1	retval: name of the return value variable
#! @param $2	helpmsg: message to display to explain the text to type (typically in brackets)
prompt_text()
{
	local retval=$1
	local answer
	local helpmsg="$2"
	if ! [ -z "$helpmsg" ]
	then echo "$helpmsg"
	fi
	echo "[<ENTER> to confirm and proceed]"
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
ESC=`printf "\033"`
cursor_show()    { if tput -V > /dev/null ; then tput cnorm ; else printf "$ESC[?25h"; fi ; }
cursor_hide()    { if tput -V > /dev/null ; then tput civis ; else printf "$ESC[?25l"; fi ; }
cursor_to()      { printf "$ESC[$1;${2:-1}H"; }
print_inactive() { printf "$1  %-20s  %s"                "$2" "$3" ; }
print_active()   { printf "$1 $ESC[7m %-20s $ESC[27m %s" "$2" "$3" ; }
get_cursor_row() { IFS=';' read -sdR -p $'\E[6n' ROW COL; echo ${ROW#*[}; }
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
		(q) echo q ;;
		($'\x1B'|^[)
			read -rsn2 key
			case "$key" in
				([A|OA) echo up    ;;
				([B|OB) echo down  ;;
				([C|OC) echo right ;;
				([D|OD) echo left  ;;
				(*) echo "" >&2 ; print_warning "Bad input key: '$key'" ;;
			esac
			;;
		(*) echo "" >&2 ; print_warning "Bad input key: '$key'" ;;
	esac
}

#! Presents a single-select list prompt to the user
#! @param $1	retval: return value variable name
#! @param $2	options: list of selectable values (semicolon-separated string)
#! @param $3 ?	default: initially selected value
#! @param $4 ?	descriptions: list of value descriptions (semicolon-separated string)
prompt_select()
{
	echo "Select one item in the list below. The controls are:"
	echo "[<Q> to cancel/abort operation]"
	echo "[<UP>/<DOWN> to move selection cursor]"
	echo "[<ENTER> or <SPACE> to select and proceed]"

	local retval=$1

	local options
	IFS=';' read -r -a options <<< "$2"

	local default="$3"

	local descriptions
	if [[ -z "$4" ]]
	then descriptions=()
	else IFS=';' read -r -a descriptions <<< "` echo "$4" | tr '[:space:]' ' ' `"
	fi

	local selected="$default"

	for ((i=0; i<=${#options[@]}; i++))
	do
		printf "\n"
	done

	# determine current screen position for overwriting the options
	local endrow=`get_cursor_row`
	local lastrow=$(($endrow - 1))
	local startrow=$(($lastrow - ${#options[@]}))

	# ensure cursor and input echoing back on upon a ctrl+c during read -s
	trap "cursor_to $endrow ; cursor_show ; exit " 2
	cursor_hide

	local active=0
	while true
	do
		# print options by overwriting the last lines
		for ((i=0; i<${#options[@]}; i++))
		do
			cursor_to $(($startrow + $i))
			if [ $i -eq $active ]
			then print_active   "> " "${options[i]}" "${descriptions[i]}"
			else print_inactive "  " "${options[i]}" "${descriptions[i]}"
			fi
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
				active=$((active - 1))
				if [ $active -lt 0 ]
				then active=$((${#options[@]} - 1))
				fi
				;;
			(down)
				active=$((active + 1))
				if [ $active -ge ${#options[@]} ]
				then active=0
				fi
				;;
			(q) echo "" >&2 ; print_message "Operation cancelled."
				# cursor position back to normal
				cursor_to $endrow
				cursor_show
				exit 1
				;;
		esac
	done
	# cursor position back to normal
	cursor_to $endrow
	cursor_show

	eval $retval='${selected}'
}



#! Presents a multi-select list prompt to the user
#! @param $1	retval: return value variable name
#! @param $2	options: list of selectable values (semicolon-separated string)
#! @param $3 ?	defaults: list of default values (space-separated, true/false)
#! @param $4 ?	descriptions: list of value descriptions (semicolon-separated string)
prompt_multiselect()
{
	echo "Select any items in the list below. The controls are:"
	echo "[<Q> to cancel/abort operation]"
	echo "[<UP>/<DOWN> to move selection cursor]"
	echo "[<SPACE> to toggle selected checkbox]"
	echo "[<ENTER> to confirm and proceed]"

	local retval=$1

	local options
	IFS=';' read -r -a options <<< "$2"

	local defaults
	if [[ -z "$3" ]]
	then defaults=()
	else IFS=';' read -r -a defaults <<< "$3"
	fi

	local descriptions
	if [[ -z "$4" ]]
	then descriptions=()
	else IFS=';' read -r -a descriptions <<< "` echo "$4" | tr '[:space:]' ' ' `"
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
	local endrow=`get_cursor_row`
	local lastrow=$(($endrow - 1))
	local startrow=$(($lastrow - ${#options[@]}))

	# ensure cursor and input echoing back on upon a ctrl+c during read -s
	trap "cursor_to $endrow ; cursor_show ; exit " 2
	cursor_hide

	local active=0
	while true
	do
		# print options by overwriting the last lines
		for ((i=0; i<${#options[@]}; i++))
		do
			local prefix="[ ]"
			if [ "${selected[i]}" == "${options[i]}" ]
			then prefix="[x]"
			fi
			cursor_to $(($startrow + $i))
			if [ $i -eq $active ]
			then print_active   "> $prefix" "${options[i]}" "${descriptions[i]}"
			else print_inactive "  $prefix" "${options[i]}" "${descriptions[i]}"
			fi
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
				active=$((active - 1))
				if [ $active -lt 0 ]
				then active=$((${#options[@]} - 1))
				fi
				;;
			(down)
				active=$((active + 1))
				if [ $active -ge ${#options[@]} ]
				then active=0
				fi
				;;
			(q) echo "" >&2 ; print_message "Operation cancelled."
				# cursor position back to normal
				cursor_to $endrow
				cursor_show
				exit 1
				;;
		esac
	done

	# cursor position back to normal
	cursor_to $endrow
	cursor_show

	selected=`echo "${selected[@]}" | xargs`
	eval $retval='$selected'
}
