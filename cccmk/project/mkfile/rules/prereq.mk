#! This file holds project-specific rules to check whether prerequisite programs are correctly installed/available



.PHONY:\
prereq #! Checks all prerequisite tools/programs and their versions
prereq: init \
	prereq-build \
%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)   :	prereq-tests \
%%if tracked(mkfile/rules/_if_multiselect/coverage.mk) :	prereq-coverage \
%%if tracked(mkfile/rules/_if_multiselect/format.mk)   :	prereq-format \
%%if tracked(mkfile/rules/_if_multiselect/lint.mk)     :	prereq-lint \
%%if tracked(mkfile/rules/_if_multiselect/doc.mk)      :	prereq-doc \
