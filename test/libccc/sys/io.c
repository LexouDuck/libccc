
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/sys/io.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                           Test Fixtures (Helpers)                          ||
\*============================================================================*/

/*
**	The pure string-manipulation functions of this header (the `IO_Path_*`
**	functions) are tested directly, with hardcoded expected values.
**	The filesystem-manipulating functions (which have side-effects) are
**	exercised within a temporary "sandbox" folder, and are tested in two ways:
**	- their return values are checked directly by the test framework machinery
**	- their side-effects upon the filesystem are verified independently, using
**	  raw libc calls (`stat()`,`fopen()`, etc), via self-contained "scenario"
**	  helper functions, each of which reduces its observable outcome to a
**	  single comparable value (this way, the fixture/verification logic never
**	  depends on any of the libccc functions which are under test here).
*/

//! The name of the temporary sandbox folder, in which all filesystem tests are performed
#define SANDBOX	"libccc_test_io_sandbox"
//! Expands to a string literal path for the given `PATH`, inside the sandbox folder
#define SB(PATH)	SANDBOX "/" PATH

//! The platform-specific path separator, as a string literal (to construct expected test results)
#ifdef _WIN32
#define SEP	"\\"
#else
#define SEP	"/"
#endif

//! The content of the basic fixture text file
#define FIXTURE_TEXT	"Hello, World!"
//! The size of a "large" fixture file: multiple IO_BUFFER_SIZE chunks, plus a small remainder
#define FIXTURE_LARGE_SIZE	((size_t)(2 * IO_BUFFER_SIZE + 3))

// platform-specific mkdir/rmdir wrappers, for fixture setup/teardown
#ifdef _WIN32
#define fixture_mkdir(PATH)	_mkdir(PATH)
#define fixture_rmdir(PATH)	_rmdir(PATH)
#else
#define fixture_mkdir(PATH)	mkdir((PATH), 0755)
#define fixture_rmdir(PATH)	rmdir(PATH)
#endif

#ifndef S_IFMT
#define S_IFMT	0170000
#endif
#ifndef S_IFREG
#define S_IFREG	0100000
#endif
#ifndef S_IFDIR
#define S_IFDIR	0040000
#endif



//! FIXTURE: checks (using raw libc) whether a regular file exists at `path`
static
t_bool	fixture_isfile(char const* path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (FALSE);
	return ((info.st_mode & S_IFMT) == S_IFREG);
}

//! FIXTURE: checks (using raw libc) whether a directory exists at `path`
static
t_bool	fixture_isdir(char const* path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (FALSE);
	return ((info.st_mode & S_IFMT) == S_IFDIR);
}

//! FIXTURE: creates (using raw libc) a file at `path`, containing `size` bytes of `content`
static
t_bool	fixture_create_file(char const* path, char const* content, size_t size)
{
	FILE*	file;
	size_t	written = 0;

	file = fopen(path, "wb");
	if (file == NULL)
		return (FALSE);
	if (size > 0)
		written = fwrite(content, 1, size, file);
	fclose(file);
	return (written == size);
}

//! FIXTURE: checks (using raw libc) that the file at `path` contains exactly `size` bytes of `content`
static
t_bool	fixture_check_file(char const* path, char const* content, size_t size)
{
	FILE*	file;
	char	buffer[512];
	size_t	total = 0;
	size_t	chunk;
	size_t	i;

	file = fopen(path, "rb");
	if (file == NULL)
		return (FALSE);
	while ((chunk = fread(buffer, 1, sizeof(buffer), file)) > 0)
	{
		for (i = 0; i < chunk; ++i)
		{
			if (total + i >= size || buffer[i] != content[total + i])
			{
				fclose(file);
				return (FALSE);
			}
		}
		total += chunk;
	}
	fclose(file);
	return (total == size);
}

//! FIXTURE: allocates a `FIXTURE_LARGE_SIZE` buffer, filled with a non-repeating-per-chunk byte pattern
static
char*	fixture_large_pattern(void)
{
	char*	result = (char*)malloc(FIXTURE_LARGE_SIZE);
	size_t	i;

	if (result == NULL)
		return (NULL);
	for (i = 0; i < FIXTURE_LARGE_SIZE; ++i)
	{
		result[i] = (char)((i * 31 + i / IO_BUFFER_SIZE) & 0xFF);
	}
	return (result);
}

//! FIXTURE: creates the sandbox folder, and the basic fixture files/folders used by several tests
static
t_bool	fixture_setup(void)
{
	if (fixture_mkdir(SANDBOX) != 0 && !fixture_isdir(SANDBOX))
		return (FALSE);
	if (!fixture_create_file(SB("hello.txt"), FIXTURE_TEXT, strlen(FIXTURE_TEXT)))
		return (FALSE);
	if (!fixture_create_file(SB("empty.txt"), "", 0))
		return (FALSE);
	if (fixture_mkdir(SB("subdir")) != 0 && !fixture_isdir(SB("subdir")))
		return (FALSE);
	return (TRUE);
}

//! FIXTURE: deletes every file/folder which may have been created by this test suite
static
void	fixture_cleanup(void)
{
	static char const*	files[] =
	{
		SB("hello.txt"),
		SB("empty.txt"),
		SB("copy.txt"),
		SB("copy_over.txt"),
		SB("large.bin"),
		SB("large_copy.bin"),
		SB("move_src.txt"),
		SB("move_dst.txt"),
		SB("remove_me.txt"),
		SB("full_dir/file.txt"),
		NULL
	};
	static char const*	folders[] = // NB: deepest folders first
	{
		SB("deep/a/b/c"),
		SB("deep/a/b"),
		SB("deep/a"),
		SB("deep"),
		SB("trail/x"),
		SB("trail"),
		SB("mkdir_new"),
		SB("rmdir_target"),
		SB("full_dir"),
		SB("subdir"),
		SANDBOX,
		NULL
	};
	int	i;

	for (i = 0; files[i]; ++i)
		remove(files[i]);
	for (i = 0; folders[i]; ++i)
		fixture_rmdir(folders[i]);
}



/*============================================================================*\
||                        Tests: Filesystem Path Functions                    ||
\*============================================================================*/



#ifndef c_pathcombine
void test_pathcombine(void)	{}
#warning "pathcombine() test suite function defined, but the function isn't defined."
#else
void	print_test_pathcombine(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* path1,
		char const* path2)
{
	TEST_INIT(str)
	TEST_PERFORM(	pathcombine, path1, path2)
	TEST_PRINT(str,	pathcombine, "path1=\"%s\", path2=\"%s\"", path1, path2)
	TEST_FREE()
}
void	test_pathcombine(void)
{
/*	| TEST FUNCTION       | TEST NAME                       | TESTFLAGS     | EXPECTING           | TEST ARGS			*/
	print_test_pathcombine("pathcombine                     ",	FALSE,        "foo" SEP "bar",      "foo",  "bar");
	print_test_pathcombine("pathcombine (trailing sep)      ",	FALSE,        "foo" SEP "bar",      "foo/", "bar");
	print_test_pathcombine("pathcombine (redundant seps)    ",	FALSE,        "foo" SEP "bar",      "foo//", "bar");
	print_test_pathcombine("pathcombine (multi-level)       ",	FALSE,        "a/b" SEP "c/d",      "a/b",  "c/d");
	print_test_pathcombine("pathcombine (absolute rhs)      ",	FALSE,        "/bar",               "foo",  "/bar");
	print_test_pathcombine("pathcombine (empty lhs)         ",	FALSE,        "bar",                "",     "bar");
	print_test_pathcombine("pathcombine (empty rhs)         ",	FALSE,        "foo",                "foo",  "");
	print_test_pathcombine("pathcombine (both empty)        ",	FALSE,        "",                   "",     "");
	print_test_pathcombine("pathcombine (root lhs)          ",	FALSE,        SEP "bar",            "/",    "bar");
	print_test_pathcombine("pathcombine (null path1)        ",	ALLOW_SIGSEGV, NULL,                NULL,   "bar");
	print_test_pathcombine("pathcombine (null path2)        ",	ALLOW_SIGSEGV, NULL,                "foo",  NULL);
	print_test_pathcombine("pathcombine (both null)         ",	ALLOW_SIGSEGV, NULL,                NULL,   NULL);
}
#endif



#ifndef c_pathdir
void test_pathdir(void)	{}
#warning "pathdir() test suite function defined, but the function isn't defined."
#else
void	print_test_pathdir(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* filepath)
{
	TEST_INIT(str)
	TEST_PERFORM(	pathdir, filepath)
	TEST_PRINT(str,	pathdir, "filepath=\"%s\"", filepath)
	TEST_FREE()
}
void	test_pathdir(void)
{
/*	| TEST FUNCTION   | TEST NAME                       | TESTFLAGS     | EXPECTING  | TEST ARGS			*/
	print_test_pathdir("pathdir                         ",	FALSE,        "/usr/lib",  "/usr/lib/file.txt");
	print_test_pathdir("pathdir (relative path)         ",	FALSE,        "foo/bar",   "foo/bar/file.txt");
	print_test_pathdir("pathdir (no separator)          ",	FALSE,        ".",         "file.txt");
	print_test_pathdir("pathdir (file at root)          ",	FALSE,        "/",         "/file.txt");
	print_test_pathdir("pathdir (redundant separators)  ",	FALSE,        "a",         "a//b");
	print_test_pathdir("pathdir (trailing separator)    ",	FALSE,        "a/b/c",     "a/b/c/"); // NB: matches C#/python semantics (POSIX `dirname` would return "a/b" here)
	print_test_pathdir("pathdir (empty string)          ",	FALSE,        ".",         "");
	print_test_pathdir("pathdir (null)                  ",	ALLOW_SIGSEGV, NULL,       NULL);
}
#endif



#ifndef c_pathfile
void test_pathfile(void)	{}
#warning "pathfile() test suite function defined, but the function isn't defined."
#else
void	print_test_pathfile(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* filepath)
{
	TEST_INIT(str)
	TEST_PERFORM(	pathfile, filepath)
	TEST_PRINT(str,	pathfile, "filepath=\"%s\"", filepath)
	TEST_FREE()
}
void	test_pathfile(void)
{
/*	| TEST FUNCTION    | TEST NAME                       | TESTFLAGS     | EXPECTING   | TEST ARGS			*/
	print_test_pathfile("pathfile                        ",	FALSE,        "file.txt",   "/usr/lib/file.txt");
	print_test_pathfile("pathfile (relative path)        ",	FALSE,        "file.txt",   "foo/file.txt");
	print_test_pathfile("pathfile (no separator)         ",	FALSE,        "file.txt",   "file.txt");
	print_test_pathfile("pathfile (trailing separator)   ",	FALSE,        "",           "/usr/lib/");
	print_test_pathfile("pathfile (hidden file)          ",	FALSE,        ".gitignore", "repo/.gitignore");
	print_test_pathfile("pathfile (empty string)         ",	FALSE,        "",           "");
	print_test_pathfile("pathfile (null)                 ",	ALLOW_SIGSEGV, NULL,        NULL);
}
#endif



#ifndef c_pathext
void test_pathext(void)	{}
#warning "pathext() test suite function defined, but the function isn't defined."
#else
void	print_test_pathext(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* filepath)
{
	TEST_INIT(str)
	TEST_PERFORM(	pathext, filepath)
	TEST_PRINT(str,	pathext, "filepath=\"%s\"", filepath)
	TEST_FREE()
}
void	test_pathext(void)
{
/*	| TEST FUNCTION   | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_pathext("pathext                         ",	FALSE,        ".txt",     "/usr/lib/file.txt");
	print_test_pathext("pathext (multiple extensions)   ",	FALSE,        ".gz",      "archive.tar.gz");
	print_test_pathext("pathext (no extension)          ",	FALSE,        "",         "/usr/lib.d/file");
	print_test_pathext("pathext (hidden file)           ",	FALSE,        "",         ".gitignore");
	print_test_pathext("pathext (hidden file with ext)  ",	FALSE,        ".yml",     ".travis.yml");
	print_test_pathext("pathext (trailing dot)          ",	FALSE,        ".",        "file.");
	print_test_pathext("pathext (empty string)          ",	FALSE,        "",         "");
	print_test_pathext("pathext (null)                  ",	ALLOW_SIGSEGV, NULL,      NULL);
}
#endif



#ifndef c_pathisabs
void test_pathisabs(void)	{}
#warning "pathisabs() test suite function defined, but the function isn't defined."
#else
void	print_test_pathisabs(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* filepath)
{
	TEST_INIT(bool)
	TEST_PERFORM(	pathisabs, filepath)
	TEST_PRINT(bool,pathisabs, "filepath=\"%s\"", filepath)
}
void	test_pathisabs(void)
{
/*	| TEST FUNCTION     | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_pathisabs("pathisabs (absolute)            ",	FALSE,        TRUE,      "/usr/lib");
	print_test_pathisabs("pathisabs (root)                ",	FALSE,        TRUE,      "/");
	print_test_pathisabs("pathisabs (relative)            ",	FALSE,        FALSE,     "usr/lib");
	print_test_pathisabs("pathisabs (relative with dot)   ",	FALSE,        FALSE,     "./usr/lib");
	print_test_pathisabs("pathisabs (relative parent)     ",	FALSE,        FALSE,     "../usr/lib");
	print_test_pathisabs("pathisabs (empty string)        ",	FALSE,        FALSE,     "");
#ifdef _WIN32
	print_test_pathisabs("pathisabs (win32: drive letter) ",	FALSE,        TRUE,      "C:\\Windows");
	print_test_pathisabs("pathisabs (win32: drive, fwd)   ",	FALSE,        TRUE,      "C:/Windows");
	print_test_pathisabs("pathisabs (win32: UNC path)     ",	FALSE,        TRUE,      "\\\\host\\share");
	print_test_pathisabs("pathisabs (win32: drive only)   ",	FALSE,        FALSE,     "C:");
	print_test_pathisabs("pathisabs (win32: backslash)    ",	FALSE,        TRUE,      "\\folder");
#endif
	print_test_pathisabs("pathisabs (null)                ",	ALLOW_SIGSEGV, FALSE,    NULL);
}
#endif



/*============================================================================*\
||                        Tests: Filesystem Operations                        ||
\*============================================================================*/



#ifndef c_fexists
void test_fexists(void)	{}
#warning "fexists() test suite function defined, but the function isn't defined."
#else
void	print_test_fexists(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* filepath)
{
	TEST_INIT(bool)
	TEST_PERFORM(	fexists, filepath)
	TEST_PRINT(bool,fexists, "filepath=\"%s\"", filepath)
}
void	test_fexists(void)
{
/*	| TEST FUNCTION   | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_fexists("fexists (existing file)         ",	FALSE,        TRUE,      SB("hello.txt"));
	print_test_fexists("fexists (existing empty file)   ",	FALSE,        TRUE,      SB("empty.txt"));
	print_test_fexists("fexists (missing file)          ",	FALSE,        FALSE,     SB("missing.txt"));
	print_test_fexists("fexists (directory, not file)   ",	FALSE,        FALSE,     SB("subdir"));
	print_test_fexists("fexists (empty string)          ",	FALSE,        FALSE,     "");
	print_test_fexists("fexists (null)                  ",	ALLOW_SIGSEGV, FALSE,    NULL);
}
#endif



#ifndef c_direxists
void test_direxists(void)	{}
#warning "direxists() test suite function defined, but the function isn't defined."
#else
void	print_test_direxists(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* path)
{
	TEST_INIT(bool)
	TEST_PERFORM(	direxists, path)
	TEST_PRINT(bool,direxists, "path=\"%s\"", path)
}
void	test_direxists(void)
{
/*	| TEST FUNCTION     | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_direxists("direxists (existing directory) ",	FALSE,        TRUE,      SANDBOX);
	print_test_direxists("direxists (existing subdir)    ",	FALSE,        TRUE,      SB("subdir"));
	print_test_direxists("direxists (current directory)  ",	FALSE,        TRUE,      ".");
	print_test_direxists("direxists (missing directory)  ",	FALSE,        FALSE,     SB("missing_dir"));
	print_test_direxists("direxists (file, not directory)",	FALSE,        FALSE,     SB("hello.txt"));
	print_test_direxists("direxists (empty string)       ",	FALSE,        FALSE,     "");
	print_test_direxists("direxists (null)               ",	ALLOW_SIGSEGV, FALSE,    NULL);
}
#endif



#ifndef c_fsize
void test_fsize(void)	{}
#warning "fsize() test suite function defined, but the function isn't defined."
#else
void	print_test_fsize(char const* test_name, t_testflags flags,
		t_sintmax expecting,
		char const* filepath)
{
	TEST_INIT(sintmax)
	TEST_PERFORM(	fsize, filepath)
	TEST_PRINT(sintmax,	fsize, "filepath=\"%s\"", filepath)
}
void	test_fsize(void)
{
	fixture_create_file(SB("large.bin"), "", 0); // will be filled by the fcopy test fixture below; here, just ensure a 0-size file
/*	| TEST FUNCTION | TEST NAME                       | TESTFLAGS     | EXPECTING                        | TEST ARGS			*/
	print_test_fsize("fsize                           ",	FALSE,        (t_sintmax)strlen(FIXTURE_TEXT), SB("hello.txt"));
	print_test_fsize("fsize (empty file)              ",	FALSE,        0,                               SB("empty.txt"));
	print_test_fsize("fsize (missing file)            ",	FALSE,        -1,                              SB("missing.txt"));
	print_test_fsize("fsize (empty string)            ",	FALSE,        -1,                              "");
	print_test_fsize("fsize (null)                    ",	ALLOW_SIGSEGV, -1,                             NULL);
}
#endif



#ifndef c_mkdir
void test_mkdir(void)	{}
#warning "mkdir() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: creates a directory with mkdir(), then verifies (using raw libc) that it truly exists on disk
static
t_bool	scenario_mkdir(char const* path)
{
	if (c_mkdir(path, 0755) != ERROR_NONE)
		return (FALSE);
	return (fixture_isdir(path));
}
void	print_test_mkdir(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* path)
{
	TEST_INIT(sint)
	TEST_PERFORM(	mkdir, path, 0755)
	TEST_PRINT(sint,mkdir, "path=\"%s\", mode=0755", path)
}
void	print_test_mkdir_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* path)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_mkdir, path)
	test.expect = expecting;
	TEST_PRINT(bool,mkdir, "path=\"%s\", mode=0755 (verifying side-effect on disk)", path)
}
void	test_mkdir(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS     | EXPECTING        | TEST ARGS			*/
	print_test_mkdir_scenario("mkdir (new directory)           ",	FALSE,        TRUE,             SB("mkdir_new"));
	print_test_mkdir         ("mkdir (already existing dir)    ",	FALSE,        ERROR_NONE,       SB("mkdir_new"));
	print_test_mkdir         ("mkdir (already existing file)   ",	FALSE,        ERROR_SYSTEM,     SB("hello.txt"));
	print_test_mkdir         ("mkdir (missing parent dirs)     ",	FALSE,        ERROR_SYSTEM,     SB("no_parent/child"));
	print_test_mkdir         ("mkdir (empty string)            ",	FALSE,        ERROR_SYSTEM,     "");
	print_test_mkdir         ("mkdir (null)                    ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



#ifndef c_mkdir_p
void test_mkdir_p(void)	{}
#warning "mkdir_p() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: creates nested directories with mkdir_p(), then verifies (using raw libc) that every level truly exists on disk
static
t_bool	scenario_mkdir_p(char const* path, char const* level1, char const* level2, char const* level3)
{
	if (c_mkdir_p(path, 0755) != ERROR_NONE)
		return (FALSE);
	if (level1 && !fixture_isdir(level1))	return (FALSE);
	if (level2 && !fixture_isdir(level2))	return (FALSE);
	if (level3 && !fixture_isdir(level3))	return (FALSE);
	return (TRUE);
}
void	print_test_mkdir_p(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* path)
{
	TEST_INIT(sint)
	TEST_PERFORM(	mkdir_p, path, 0755)
	TEST_PRINT(sint,mkdir_p, "path=\"%s\", mode=0755", path)
}
void	print_test_mkdir_p_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* path, char const* level1, char const* level2, char const* level3)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_mkdir_p, path, level1, level2, level3)
	test.expect = expecting;
	TEST_PRINT(bool,mkdir_p, "path=\"%s\", mode=0755 (verifying side-effect on disk)", path)
}
void	test_mkdir_p(void)
{
/*	| TEST FUNCTION            | TEST NAME                       | TESTFLAGS     | EXPECTING  | TEST ARGS			*/
	print_test_mkdir_p_scenario("mkdir_p (nested directories)    ",	FALSE,        TRUE,
		SB("deep/a/b/c"),	SB("deep/a"),	SB("deep/a/b"),	SB("deep/a/b/c"));
	print_test_mkdir_p_scenario("mkdir_p (trailing separator)    ",	FALSE,        TRUE,
		SB("trail/x/"),		SB("trail"),	SB("trail/x"),	NULL);
	print_test_mkdir_p         ("mkdir_p (already existing dirs) ",	FALSE,        ERROR_NONE,   SB("deep/a/b/c"));
	print_test_mkdir_p         ("mkdir_p (single level)          ",	FALSE,        ERROR_NONE,   SB("subdir"));
	print_test_mkdir_p         ("mkdir_p (already existing file) ",	FALSE,        ERROR_SYSTEM, SB("hello.txt"));
	print_test_mkdir_p         ("mkdir_p (null)                  ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



#ifndef c_rmdir
void test_rmdir(void)	{}
#warning "rmdir() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: creates a directory (using raw libc), deletes it with rmdir(), then verifies that it is truly gone from disk
static
t_bool	scenario_rmdir(char const* path)
{
	if (fixture_mkdir(path) != 0)
		return (FALSE);
	if (c_rmdir(path) != ERROR_NONE)
		return (FALSE);
	return (!fixture_isdir(path));
}
//! SCENARIO: attempts to rmdir() a non-empty directory: checks that the call fails, AND that the directory and its contents were left untouched
static
t_bool	scenario_rmdir_nonempty(char const* path, char const* innerfile)
{
	if (c_rmdir(path) == ERROR_NONE)
		return (FALSE); // deleting a non-empty directory should not succeed
	return (fixture_isdir(path) && fixture_isfile(innerfile));
}
void	print_test_rmdir(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* path)
{
	TEST_INIT(sint)
	TEST_PERFORM(	rmdir, path)
	TEST_PRINT(sint,rmdir, "path=\"%s\"", path)
}
void	print_test_rmdir_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* path)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_rmdir, path)
	test.expect = expecting;
	TEST_PRINT(bool,rmdir, "path=\"%s\" (verifying side-effect on disk)", path)
}
void	print_test_rmdir_scenario_nonempty(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* path,
		char const* innerfile)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_rmdir_nonempty, path, innerfile)
	test.expect = expecting;
	TEST_PRINT(bool,rmdir, "path=\"%s\" (non-empty: should fail, and leave the directory untouched)", path)
}
void	test_rmdir(void)
{
	// fixture: a non-empty directory (should not be deletable by rmdir)
	fixture_mkdir(SB("full_dir"));
	fixture_create_file(SB("full_dir/file.txt"), FIXTURE_TEXT, strlen(FIXTURE_TEXT));
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_rmdir_scenario("rmdir (empty directory)         ",	FALSE,        TRUE,         SB("rmdir_target"));
	print_test_rmdir_scenario_nonempty("rmdir (non-empty directory)     ",	FALSE, TRUE,   SB("full_dir"), SB("full_dir/file.txt"));
	print_test_rmdir         ("rmdir (missing directory)       ",	FALSE,        ERROR_SYSTEM, SB("missing_dir"));
	print_test_rmdir         ("rmdir (file, not directory)     ",	FALSE,        ERROR_SYSTEM, SB("hello.txt"));
	print_test_rmdir         ("rmdir (null)                    ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



#ifndef c_fremove
void test_fremove(void)	{}
#warning "fremove() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: creates a file (using raw libc), deletes it with fremove(), then verifies that it is truly gone from disk
static
t_bool	scenario_fremove(char const* path)
{
	if (!fixture_create_file(path, FIXTURE_TEXT, strlen(FIXTURE_TEXT)))
		return (FALSE);
	if (c_fremove(path) != ERROR_NONE)
		return (FALSE);
	return (!fixture_isfile(path));
}
void	print_test_fremove(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* filepath)
{
	TEST_INIT(sint)
	TEST_PERFORM(	fremove, filepath)
	TEST_PRINT(sint,fremove, "filepath=\"%s\"", filepath)
}
void	print_test_fremove_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* filepath)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_fremove, filepath)
	test.expect = expecting;
	TEST_PRINT(bool,fremove, "filepath=\"%s\" (verifying side-effect on disk)", filepath)
}
void	test_fremove(void)
{
/*	| TEST FUNCTION            | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_fremove_scenario("fremove (existing file)         ",	FALSE,        TRUE,         SB("remove_me.txt"));
	print_test_fremove         ("fremove (missing file)          ",	FALSE,        ERROR_SYSTEM, SB("missing.txt"));
	print_test_fremove         ("fremove (empty string)          ",	FALSE,        ERROR_SYSTEM, "");
	print_test_fremove         ("fremove (null)                  ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



#ifndef c_fcopy
void test_fcopy(void)	{}
#warning "fcopy() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: copies a file with fcopy(), then verifies (using raw libc) that both files exist, and that the copy's content is identical
static
t_bool	scenario_fcopy(char const* srcpath, char const* dstpath, char const* content, size_t size)
{
	if (c_fcopy(srcpath, dstpath) != ERROR_NONE)
		return (FALSE);
	if (!fixture_isfile(srcpath)) // the source file should be untouched
		return (FALSE);
	return (fixture_check_file(dstpath, content, size));
}
//! SCENARIO: creates a multi-chunk file (larger than IO_BUFFER_SIZE), copies it, and verifies the copy's content is identical
static
t_bool	scenario_fcopy_large(char const* srcpath, char const* dstpath)
{
	char*	pattern;
	t_bool	result;

	pattern = fixture_large_pattern();
	if (pattern == NULL)
		return (FALSE);
	if (!fixture_create_file(srcpath, pattern, FIXTURE_LARGE_SIZE))
	{
		free(pattern);
		return (FALSE);
	}
	result = scenario_fcopy(srcpath, dstpath, pattern, FIXTURE_LARGE_SIZE);
	free(pattern);
	return (result);
}
void	print_test_fcopy(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* srcpath,
		char const* dstpath)
{
	TEST_INIT(sint)
	TEST_PERFORM(	fcopy, srcpath, dstpath)
	TEST_PRINT(sint,fcopy, "srcpath=\"%s\", dstpath=\"%s\"", srcpath, dstpath)
}
void	print_test_fcopy_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* srcpath,
		char const* dstpath,
		char const* content,
		size_t size)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_fcopy, srcpath, dstpath, content, size)
	test.expect = expecting;
	TEST_PRINT(bool,fcopy, "srcpath=\"%s\", dstpath=\"%s\" (verifying side-effect on disk)", srcpath, dstpath)
}
void	print_test_fcopy_scenario_large(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* srcpath,
		char const* dstpath)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_fcopy_large, srcpath, dstpath)
	test.expect = expecting;
	TEST_PRINT(bool,fcopy, "srcpath=\"%s\", dstpath=\"%s\" (multi-chunk file, verifying side-effect on disk)", srcpath, dstpath)
}
void	test_fcopy(void)
{
	// fixture: a pre-existing destination file, with different content (to test overwriting)
	fixture_create_file(SB("copy_over.txt"), "pre-existing different content, which is longer", 48);
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_fcopy_scenario("fcopy                           ",	FALSE,        TRUE,
		SB("hello.txt"), SB("copy.txt"), FIXTURE_TEXT, strlen(FIXTURE_TEXT));
	print_test_fcopy_scenario("fcopy (overwrite existing file) ",	FALSE,        TRUE,
		SB("hello.txt"), SB("copy_over.txt"), FIXTURE_TEXT, strlen(FIXTURE_TEXT));
	print_test_fcopy_scenario_large("fcopy (multi-chunk large file)  ",	FALSE,  TRUE,
		SB("large.bin"), SB("large_copy.bin"));
	print_test_fcopy         ("fcopy (missing source)          ",	FALSE,        ERROR_SYSTEM, SB("missing.txt"), SB("copy2.txt"));
	print_test_fcopy         ("fcopy (invalid dest folder)     ",	FALSE,        ERROR_SYSTEM, SB("hello.txt"), SB("no_such_dir/copy.txt"));
	print_test_fcopy         ("fcopy (null src)                ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL, SB("copy.txt"));
	print_test_fcopy         ("fcopy (null dst)                ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, SB("hello.txt"), NULL);
}
#endif



#ifndef c_fmove
void test_fmove(void)	{}
#warning "fmove() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: creates a file (using raw libc), moves it with fmove(), then verifies that the source is gone, and the destination content is identical
static
t_bool	scenario_fmove(char const* oldpath, char const* newpath)
{
	if (!fixture_create_file(oldpath, FIXTURE_TEXT, strlen(FIXTURE_TEXT)))
		return (FALSE);
	if (c_fmove(oldpath, newpath) != ERROR_NONE)
		return (FALSE);
	if (fixture_isfile(oldpath)) // the source file should no longer exist
		return (FALSE);
	return (fixture_check_file(newpath, FIXTURE_TEXT, strlen(FIXTURE_TEXT)));
}
void	print_test_fmove(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* oldpath,
		char const* newpath)
{
	TEST_INIT(sint)
	TEST_PERFORM(	fmove, oldpath, newpath)
	TEST_PRINT(sint,fmove, "oldpath=\"%s\", newpath=\"%s\"", oldpath, newpath)
}
void	print_test_fmove_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* oldpath,
		char const* newpath)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_fmove, oldpath, newpath)
	test.expect = expecting;
	TEST_PRINT(bool,fmove, "oldpath=\"%s\", newpath=\"%s\" (verifying side-effect on disk)", oldpath, newpath)
}
void	test_fmove(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_fmove_scenario("fmove                           ",	FALSE,        TRUE,         SB("move_src.txt"), SB("move_dst.txt"));
	print_test_fmove         ("fmove (missing source)          ",	FALSE,        ERROR_SYSTEM, SB("missing.txt"), SB("move_dst2.txt"));
	print_test_fmove         ("fmove (null oldpath)            ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL, SB("move_dst.txt"));
	print_test_fmove         ("fmove (null newpath)            ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, SB("move_src.txt"), NULL);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_sys_io(void)
{
	print_suite_title("libccc/sys/io");

	// pure functions (path string manipulation)
	test_pathcombine();
	test_pathdir();
	test_pathfile();
	test_pathext();
	test_pathisabs();

	// filesystem functions (side-effects, performed within a temporary sandbox folder)
	fixture_cleanup(); // in case a previous test run was interrupted
	if (fixture_setup())
	{
		test_fexists();
		test_direxists();
		test_fsize();
		test_mkdir();
		test_mkdir_p();
		test_rmdir();
		test_fremove();
		test_fcopy();
		test_fmove();
		fixture_cleanup();
	}
	else
	{
		print_error("Could not create the sandbox folder \"" SANDBOX "\" for the libccc/sys/io test suite.");
		fixture_cleanup();
		return (ERROR);
	}

	return (OK);
}
