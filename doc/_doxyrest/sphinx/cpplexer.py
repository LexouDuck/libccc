#...............................................................................
#
#  This file is part of the Doxyrest toolkit.
#
#  Doxyrest is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/doxyrest/license.txt
#
#...............................................................................

# -*- coding: utf-8 -*-
"""
    pygments.lexers.c_cpp
    ~~~~~~~~~~~~~~~~~~~~~

    Lexers for C/C++ languages.

    :copyright: Copyright 2006-2015 by the Pygments team, see AUTHORS.
    :license: BSD, see LICENSE for details.
"""

import re

from pygments.lexer import RegexLexer, include, bygroups, using, this, inherit, default, words
from pygments.util import get_bool_opt
from pygments.token import Text, Comment, Operator, Keyword, Name, String, Number, Punctuation, Error
from sphinx.highlighting import lexers


class CFamilyLexer(RegexLexer):
    """
    For C family source code.
    This is used as a base class to avoid repetitious definitions.
    """

    #: optional Comment or Whitespace
    c_ws = r'(?:\s|//.*?\n|/[*].*?[*]/)+'
    # The trailing ?, rather than *, avoids a geometric performance drop here. : only one /* */ style comment
    c_ws1 = r'\s*(?:/[*].*?[*]/\s*)?'
    # The regex for a user-defined symbol in any C-like language
    c_symbol = r'([a-zA-Z_]\w*)'

    tokens = {
        'whitespace': [
            # preprocessor directives: without whitespace
            (r'^#\s*if\s+0', Comment.Preproc, 'if0'),
            (r'^#\s*',       Comment.Preproc, 'macro'),
            # or with whitespace
            (r'^(' + c_ws1 + r')(#\s*if\s+0)', bygroups(using(this), Comment.Preproc), 'if0'),
            (r'^(' + c_ws1 + r')(#\s*)',       bygroups(using(this), Comment.Preproc), 'macro'),
            (r'\n',   Text),
            (r'\s+',  Text),
            (r'\\\n', Text),  # line continuation
            (r'//(\n|(.|\n)*?[^\\](\n|$))',     Comment.Single),
            (r'/(\\\n)?[*](.|\n)*?[*](\\\n)?/', Comment.Multiline),
        ],
        'statements': [
            (r'(L|u|U|u8)?(\")', bygroups(Keyword.Type, String), 'string'),
            (r'(L|u|U|u8)?(\')', bygroups(Keyword.Type, String.Char), 'char'),
            (r'([0-9]+\.[0-9]*|\.[0-9]+|[0-9]+)([eE])([+-]?)([0-9]+)([LlFf]?)\b',                         bygroups(Number.Float, Keyword.Constant, Operator, Number, Keyword.Type)),
            (r'([0-9]+\.[0-9]*|\.[0-9]+)([LlFf]?)\b',                                                     bygroups(Number.Float, Keyword.Type)),
            (r'([0-9]+)([LlFf])\b',                                                                       bygroups(Number.Float, Keyword.Type)),
            (r'(0x[0-9a-fA-F]+\.[0-9a-fA-F]*|\.[0-9a-fA-F]+|[0-9a-fA-F]+)([pP])([+-]?)([0-9]+)([LlFf]*)', bygroups(Number.Float, Keyword.Constant, Operator, Number, Keyword.Type)),
            (r'(0x[0-9a-fA-F]+)([LlUu]*)', bygroups(Number.Hex,     Keyword.Type)),
            (r'(0b[01]+)([LlUu]*)',        bygroups(Number.Bin,     Keyword.Type)), # GNU extension: binary literals
            (r'(0[0-7]+)([LlUu]*)',        bygroups(Number.Oct,     Keyword.Type)),
            (r'([0-9]+)([LlUu]*)',         bygroups(Number.Integer, Keyword.Type)),
            (r'\*/', Error),
            (r'[~!%^&*+=|?:<>/-]', Operator),
            (words((
                'sizeof',
                'typeof',
                'alignof',
                'alignas',
                'offsetof'),
                prefix=r'\b',
                suffix=r'\b'), Operator.Word),
            (words((
                'extern',
                'static',
                'const',
                'restricted',
                'auto',
                'register',
                'volatile',
                'return',
                'goto',
                'if',
                'else',
                'while',
                'do',
                'for',
                'break',
                'continue',
                'switch',
                'case',
                'default',
                'typedef'),
                prefix=r'\b',
                suffix=r'\b'), Keyword),
            (words((
                'unsigned',
                'signed',
                'void',
                'bool',
                'char',
                'short',
                'int',
                'long',
                'float',
                'double'),
                prefix=r'\b',
                suffix=r'\b'), Keyword.Type),
            (words((
                'struct',
                'union',
                'enum'),
                prefix=r'\b',
                suffix=r'\b'), Keyword.Declaration),
            (words((
                'inline', '_inline', '__inline',
                'naked',
                'restrict',
                'thread',
                'typename',
                '__asm__',
                '__attribute__'), suffix=r'\b'), Keyword.Reserved),
            #(r'\b__attribute__\s*\(\s*\((alias|aligned|delete|format|malloc|packed|pure|unused|always_inline)', Name.Attribute),
            # Vector intrinsics
            (r'(__m(128i|128d|128|64))\b', Keyword.Reserved),
            # Microsoft-isms
            (words((
                'asm',
                'int8',
                'int16',
                'int32',
                'int64',
                'w64',
                'cdecl',
                'stdcall',
                'fastcall',
                'declspec',
                'unaligned',
                'identifier',
                'forceinline',
                'based',
                'noop',
                'try',
                'catch',
                'except',
                'finally',
                'raise',
                'leave',
                'assume'),
                prefix=r'__',
                suffix=r'\b'), Keyword.Reserved),
            (words((
                'true',
                'TRUE',
                'false',
                'FALSE',
                'null',
                'NULL',
                'EXIT_FAILURE',
                'EXIT_SUCCESS',
                '__func__'),
                prefix=r'\b',
                suffix=r'\b'), Name.Constant),
            (r'[()\[\],.]', Punctuation),
            (c_symbol + r'(\s*)(:)(?!:)', bygroups(Name.Label, Text, Punctuation)),
            (c_symbol, Name),
        ],
        'root': [
            include('whitespace'),
            # functions
            (r'((?:[\w*\s])+?(?:\s|[*]))'  # return type
             + c_symbol +                  # function name
             r'(\s*\([^;]*?\))'            # function args
             r'([^;{]*)(\{)',
             bygroups(using(this), Name.Function, using(this), using(this), Punctuation),
             'function'),
            # function declarations
            (r'((?:[\w*\s])+?(?:\s|[*]))'  # return type
             + c_symbol +                  # function name
             r'(\s*\([^;]*?\))'            # function args
             r'([^;]*)(;)',
             bygroups(using(this), Name.Function, using(this), using(this), Punctuation)),
            default('statement'),
        ],
        'statement': [
            include('whitespace'),
            include('statements'),
            ('[{}]', Punctuation),
            (';', Punctuation, '#pop'),
        ],
        'function': [
            include('whitespace'),
            include('statements'),
            (';', Punctuation),
            (r'\{', Punctuation, '#push'),
            (r'\}', Punctuation, '#pop'),
        ],
        'string': [
            (r'"', String, '#pop'),
            (r'\\([\\abefnrtv"\']|x[a-fA-F0-9]{2,4}|'
             r'u[a-fA-F0-9]{4}|U[a-fA-F0-9]{8}|[0-7]{1,3})', String.Escape),
            (r'[^\\"\n]+', String),  # all other characters
            (r'\\\n', String),  # line continuation
            (r'\\', String),  # stray backslash
        ],
        'char': [
            (r"'", String.Char, '#pop'),
            (r'\\([\\abefnrtv"\']|x[a-fA-F0-9]{2,4}|u[a-fA-F0-9]{4}|U[a-fA-F0-9]{8}|[0-7]{1,3})', String.Escape),
            (r"[^\\'\n]+", String.Char),  # all other characters
            (r'\\\n', String.Char),  # line continuation
            (r'\\', String.Char),  # stray backslash
        ],
        'macro': [
            (r'(include)(' + c_ws1 + r')([^\n]+)',
                bygroups(Comment.Preproc, Text, Comment.PreprocFile)),
            (r'(define)(' + c_ws1 + r')(\w+)(\([^)]*\))?(\s+)',
                bygroups(Comment.Preproc, Text, Name.Function.Magic, Text, Text), '#pop'),
            (r'[^/\n]+', Comment.Preproc),
            (r'/[*](.|\n)*?[*]/', Comment.Multiline),
            (r'//.*?\n',          Comment.Single, '#pop'),
            (r'/',                Comment.Preproc),
            (r'(?<=\\)\n',        Comment.Preproc),
            (r'\n',               Comment.Preproc, '#pop'),
        ],
        'if0': [
            (r'^\s*#\s*if.*?(?<!\\)\n',    Comment.Preproc, '#push'),
            (r'^\s*#\s*el(?:se|if).*\n',   Comment.Preproc, '#pop'),
            (r'^\s*#\s*endif.*?(?<!\\)\n', Comment.Preproc, '#pop'),
            (r'.*?\n', Comment),
        ]
    }

    stdlib_types = set((
        'size_t',
        'ssize_t',
        'fpos_t',
        'off_t',
        'ptrdiff_t',
        'sig_atomic_t',
        'clock_t',
        'time_t',
        'va_list',
        'jmp_buf',
        'div_t',
        'ldiv_t',
        'mbstate_t',
        'wint_t',
        'wchar_t',
        'wctrans_t',
        'wctype_t',
        'FILE',
        'DIR'))
    c99_types = set((
        '_Bool', '_Complex', '_Imaginary',
        'int8_t',   'int_least8_t',   'int_fast8_t',
        'int16_t',  'int_least16_t',  'int_fast16_t',
        'int32_t',  'int_least32_t',  'int_fast32_t',
        'int64_t',  'int_least64_t',  'int_fast64_t',
        'uint8_t',  'uint_least8_t',  'uint_fast8_t',
        'uint16_t', 'uint_least16_t', 'uint_fast16_t',
        'uint32_t', 'uint_least32_t', 'uint_fast32_t',
        'uint64_t', 'uint_least64_t', 'uint_fast64_t',
        'intptr_t',
        'uintptr_t',
        'intmax_t',
        'uintmax_t'))
    linux_types = set((
        'cpu_set_t',
        'cpumask_t',
        'dev_t',
        'id_t',
        'ino_t',
        'key_t',
        'mode_t',
        'nfds_t',
        'gid_t',
        'pid_t',
        'uid_t',
        'rlim_t',
        'sig_t',
        'sighandler_t',
        'siginfo_t',
        'sigset_t',
        'sigval_t',
        'socklen_t',
        'timer_t',
        'clockid_t'))

    def __init__(self, **options):
        self.stdlibhighlighting = get_bool_opt(options, 'stdlibhighlighting', True)
        self.c99highlighting = get_bool_opt(options, 'c99highlighting', True)
        self.platformhighlighting = get_bool_opt(options, 'platformhighlighting', True)
        RegexLexer.__init__(self, **options)

    def get_tokens_unprocessed(self, text):
        for index, token, value in \
                RegexLexer.get_tokens_unprocessed(self, text):
            if token is Name:
                if self.stdlibhighlighting and value in self.stdlib_types:
                    token = Keyword.Type
                elif self.c99highlighting and value in self.c99_types:
                    token = Keyword.Type
                elif self.platformhighlighting and value in self.linux_types:
                    token = Keyword.Type
                elif re.match(r'\b([tseufpi]_\w+)\b', value):
                    token = Keyword.Type # libccc typedef
                elif re.match(r'\b([A-Z])\b', value):
                    token = Keyword.Type # libccc generic type macro
            yield index, token, value


class CLexer(CFamilyLexer):
    """
    For C source code with preprocessor directives.
    """
    name = 'C'
    aliases = ['c']
    filenames = ['*.c', '*.h', '*.idc']
    mimetypes = ['text/x-chdr', 'text/x-csrc']
    priority = 0.1

    def __init__(self, **options):
        CFamilyLexer.__init__(self, **options)

    def analyse_text(text):
        if re.search(r'^\s*#include [<"]', text, re.MULTILINE):
            return 0.1
        if re.search(r'^\s*#ifn?def ', text, re.MULTILINE):
            return 0.1


class CppLexer(CFamilyLexer):
    """
    For C++ source code with preprocessor directives.
    """
    name = 'C++'
    aliases = ['cpp', 'c++']
    filenames = [
        '*.cpp', '*.hpp',
        '*.c++', '*.h++',
        '*.cc',  '*.hh',
        '*.cxx', '*.hxx',
        '*.C',   '*.H',
        '*.cp',  '*.hp',
        '*.CPP', '*.HPP']
    mimetypes = ['text/x-c++hdr', 'text/x-c++src']
    priority = 0.1

    tokens = {
        'statements': [
            (words((
                'asm', 'catch', 'class', 'const_cast', 'delete', 'dynamic_cast', 'explicit',
                'export', 'friend', 'mutable', 'namespace', 'new', 'operator',
                'private', 'protected', 'public', 'reinterpret_cast',
                'restrict', 'static_cast', 'template', 'this', 'throw', 'throws',
                'try', 'typeid', 'typename', 'using', 'virtual',
                'constexpr', 'nullptr', 'decltype', 'thread_local',
                'alignas', 'alignof', 'static_assert', 'noexcept', 'override',
                'final'), suffix=r'\b'), Keyword),
            (r'char(16_t|32_t)\b', Keyword.Type),
            # C++11 raw strings
            (r'R"\(', String, 'rawstring'),
            inherit,
        ],
        'root': [
            inherit,
            # C++ Microsoft-isms
            (words(('virtual_inheritance', 'uuidof', 'super', 'single_inheritance',
                    'multiple_inheritance', 'interface', 'event'),
                   prefix=r'__', suffix=r'\b'), Keyword.Reserved),
            # Offload C++ extensions, http://offload.codeplay.com/
            (r'__(offload|blockingoffload|outer)\b', Keyword.Pseudo),
        ],
        'rawstring': [
            (r'\)"', String, '#pop'),
            (r'[^)]+', String),
            (r'\)', String),
        ],
    }

    def __init__(self, **options):
        CFamilyLexer.__init__(self, **options)

    def analyse_text(text):
        if re.search('#include <[a-z_]+>', text):
            return 0.2
        if re.search('using namespace ', text):
            return 0.4


class IdlLexer(CppLexer):
    """
    For Interface Definition Language source code.
    """
    name = 'IDL'
    aliases = ['idl']
    filenames = ['*.idl']
    mimetypes = ['text/x-idl']
    priority = 0.1

    tokens = {
        'statements': [
            (words((
                'interface', 'protocol', 'exception', 'service', 'singleton', 'module',
                'any', 'boolean', 'string', 'sequence'), suffix=r'\b'), Keyword),
            inherit,
        ],
        'root': [
            inherit,
        ],
    }

    def __init__(self, **options):
        CppLexer.__init__(self, **options)


def setup(app):
    options = {}
    options['stripnl'] = False
    options['ensurenl'] = False

    c_lexer = CLexer(**options)
    cpp_lexer = CppLexer(**options)
    idl_lexer = IdlLexer(**options)

    lexers['c'] = c_lexer
    lexers['cpp'] = cpp_lexer
    lexers['cxx'] = cpp_lexer
    lexers['c++'] = cpp_lexer
    lexers['c++'] = cpp_lexer
    lexers['idl'] = idl_lexer

    return {
        'version': 'builtin',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }
