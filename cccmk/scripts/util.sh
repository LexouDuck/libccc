#!/bin/sh -e



prompt_multiselect()
{
	echo "(UP/DOWN to move cursor; SPACE to toggle selected checkbox; ENTER to confirm and proceed)"
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
		if [[ $key = ""      ]]; then echo enter; fi;
		if [[ $key = $'\x20' ]]; then echo space; fi;
		if [[ $key = $'\x1b' ]]
		then
			read -rsn2 key
			if [[ $key = [A ]]; then echo up;    fi;
			if [[ $key = [B ]]; then echo down;  fi;
		fi 
	}
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
		for option in "${options[@]}"; do
			local prefix="[ ]"
			if [[ ${selected[idx]} == $option ]]
			then prefix="[x]"
			fi

			cursor_to $(($startrow + $idx))
			if [ $idx -eq $active ]
			then print_active   "$prefix" "$option" "$description"
			else print_inactive "$prefix" "$option" "$description"
			fi
			((idx++))
		done

		# user key control
		case `key_input` in
			space)
				toggle_option selected $active
				;;
			enter)
				break
				;;
			up)
				((active--));
				if [ $active -lt 0 ]
				then active=$((${#options[@]} - 1))
				fi
				;;
			down)
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

	eval $retval='("${selected[@]}")'
}
