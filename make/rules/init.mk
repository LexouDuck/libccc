# This file holds rules which perform some initial project/repo setup



.PHONY:\
init # Should be executed once, after cloning the repo
init:
	@git config core.hooksPath ./.github/hooks
