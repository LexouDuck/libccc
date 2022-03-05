#! This file holds project-specific rules to check whether prerequisite programs are correctly installed/available



.PHONY:\
prereq #! Checks all prerequisite tools/programs and their versions
prereq: \
init \
prereq-build \
%%if tracked(_if_ask_mkfile/mkfile/_if_ask_testsuite/rules/test.mk)   :prereq-tests \
%%if tracked(_if_ask_mkfile/mkfile/rules/_if_multiselect/coverage.mk) :prereq-coverage \
%%if tracked(_if_ask_mkfile/mkfile/rules/_if_multiselect/format.mk)   :prereq-format \
%%if tracked(_if_ask_mkfile/mkfile/rules/_if_multiselect/lint.mk)     :prereq-lint \
%%if tracked(_if_ask_mkfile/mkfile/rules/_if_multiselect/doc.mk)      :prereq-doc \
