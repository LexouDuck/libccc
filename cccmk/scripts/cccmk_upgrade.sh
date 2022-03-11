#!/bin/sh -e



(
	cd "$CCCMK_PATH"
	git checkout $cccmk_upgrade
	# check if upgrade is a fixed commit (if so, dont 'git pull' anything)
	if [ -z `echo "$cccmk_upgrade" | awk '/[0-9a-fA-F]{40}/ { print }'` ]
	then git pull
	fi
)
