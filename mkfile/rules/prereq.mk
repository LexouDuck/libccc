#! This file holds project-specific rules to check whether prerequisite programs are correctly installed/available



.PHONY:\
prereq #! Checks all prerequisite tools/programs and their versions
prereq: \
init \
prereq-build \
prereq-tests \
prereq-coverage \
prereq-format \
prereq-lint \
prereq-doc \
