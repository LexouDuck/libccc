
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
	#include <direct.h>
#else
	#include <unistd.h>
#endif
#if (!defined(_WIN32) || defined(__CYGWIN__))
	#include <sys/wait.h>
	#define FORK_SCENARIOS	1
#else
	#define FORK_SCENARIOS	0
#endif

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/string.h"
#include "libccc/sys/program.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                           Test Fixtures (Helpers)                          ||
\*============================================================================*/

/*
**	The program termination functions (`exit()` and friends) obviously cannot
**	be called within the test runner process itself: so, on POSIX platforms,
**	they are exercised in a fork()ed child process, whose exit status (and
**	output, sent through a pipe) is then verified by the parent test runner.
**	The other, non-terminating functions are tested either directly, or via
**	self-contained "scenario" helpers (verifying with raw libc, so that the
**	fixture/verification logic never depends on the functions under test).
*/

// platform-portable fixture wrappers, using raw libc (independent from the functions under test)
#ifdef _WIN32
#define fixture_mkdir(PATH)	_mkdir(PATH)
#define fixture_rmdir(PATH)	_rmdir(PATH)
#define fixture_chdir(PATH)	_chdir(PATH)
#define fixture_setenv(NAME, VALUE)	_putenv(NAME "=" VALUE)
#else
#define fixture_mkdir(PATH)	mkdir((PATH), 0755)
#define fixture_rmdir(PATH)	rmdir(PATH)
#define fixture_chdir(PATH)	chdir(PATH)
#define fixture_setenv(NAME, VALUE)	setenv((NAME), (VALUE), 1)
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

//! FIXTURE: checks whether the string `str` ends with the given `suffix`
static
t_bool	fixture_endswith(char const* str, char const* suffix)
{
	size_t	len_str;
	size_t	len_suffix;

	if (str == NULL || suffix == NULL)
		return (FALSE);
	len_str = strlen(str);
	len_suffix = strlen(suffix);
	if (len_suffix > len_str)
		return (FALSE);
	return (strcmp(str + (len_str - len_suffix), suffix) == 0);
}



#if FORK_SCENARIOS

//! FIXTURE: the write-end pipe file descriptor, for a forked child process to send its output to the parent
static int	child_pipe = -1;

//! FIXTURE: an exit-handler function which reports its execution to the parent process, through the pipe
static
void	fixture_exithandler(void)
{
	if (child_pipe >= 0)
		write(child_pipe, "handler", 7);
}

//! FIXTURE: runs the given `child` function in a fork()ed process, and returns its outcome:
//! the exit status code if the child exited normally, `256 + signal` if it was terminated
//! by a signal, or `-1` if an error occurred. Anything the child writes to the #child_pipe
//! is stored into `output` (which must be at least 64 chars large).
static
int	scenario_fork(void (*child)(void), char* output)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	output[0] = '\0';
	if (pipe(fd) != 0)
		return (-1);
	fflush(NULL); // avoid duplicated buffered output in the forked child
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{	// child process
		close(fd[0]);
		child_pipe = fd[1];
		child();
		_exit(111); // should never be reached (the child function is expected to terminate the process)
	}
	// parent process
	close(fd[1]);
	ssize_t length = read(fd[0], output, 63);
	output[(length > 0) ? length : 0] = '\0';
	close(fd[0]);
	if (waitpid(pid, &status, 0) < 0)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (256 + WTERMSIG(status));
	return (-1);
}

// the child functions, for each program termination scenario:
static void	child_exit(void)		{ atexit(fixture_exithandler); Program_Exit(5); }
static void	child_exitnow(void)		{ atexit(fixture_exithandler); Program_ExitNow(7); }
static void	child_quickexit(void)	{ Program_OnExitQuick(fixture_exithandler); Program_ExitQuick(9); }
static void	child_onexit(void)		{ Program_OnExit(fixture_exithandler); Program_Exit(0); }
static void	child_abort(void)
{
	// NB: the test framework's own SIGABRT handler was inherited by this child
	// process: reset it, so that abort() terminates the child normally
	signal(SIGABRT, SIG_DFL);
	Program_Abort();
}

//! SCENARIO: runs `child` in a forked process; checks its exit outcome, and whether the exit-handler was called
static
t_bool	scenario_termination(void (*child)(void), int expected_outcome, t_bool expecting_handler)
{
	char	output[64];
	int		outcome;

	outcome = scenario_fork(child, output);
	if (outcome != expected_outcome)
		return (FALSE);
	return ((strcmp(output, "handler") == 0) == expecting_handler);
}

#endif



/*============================================================================*\
||                       Tests: Program Termination                           ||
\*============================================================================*/



#ifndef c_exit
void test_exit(void)	{}
#warning "exit() test suite function defined, but the function isn't defined."
#else
#if FORK_SCENARIOS
void	print_test_exit_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		void (*child)(void), int expected_outcome, t_bool expecting_handler, char const* description)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_termination, child, expected_outcome, expecting_handler)
	test.expect = expecting;
	TEST_PRINT(bool,exit, "%s", description)
}
#endif
void	test_exit(void)
{
#if FORK_SCENARIOS
/*	| TEST FUNCTION         | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_exit_scenario("exit (status code, in fork)     ",	FALSE,    TRUE,
		child_exit,      5, TRUE,  "exit_code=5 (atexit handlers should run)");
	print_test_exit_scenario("exitnow (skips atexit handlers) ",	FALSE,    TRUE,
		child_exitnow,   7, FALSE, "exit_code=7 (atexit handlers should NOT run)");
	print_test_exit_scenario("quick_exit (runs quick handlers)",	FALSE,    TRUE,
		child_quickexit, 9, TRUE,  "exit_code=9 (at_quick_exit handlers should run)");
	print_test_exit_scenario("atexit (handler runs on exit)   ",	FALSE,    TRUE,
		child_onexit,    0, TRUE,  "exit_code=0 (atexit handler should run)");
	print_test_exit_scenario("abort (terminates with SIGABRT) ",	FALSE,    TRUE,
		child_abort,     256 + SIGABRT, FALSE, "(child should be terminated by SIGABRT)");
#endif
}
#endif



/*============================================================================*\
||                          Tests: Non-local Jumps                            ||
\*============================================================================*/



#ifndef c_setjmp
void test_setjmp(void)	{}
#warning "setjmp() test suite function defined, but the function isn't defined."
#else
static t_jmpbuf	jump_context;

//! FIXTURE: performs a non-local jump back to the context saved by scenario_jump()
static
void	fixture_do_jump(int status)
{
	Program_RestoreContext(jump_context, status);
}
//! SCENARIO: saves the context, jumps back to it (from within another function's stack frame) with `status`, and checks the value received
static
t_bool	scenario_jump(int status, int expected)
{
	int	received;

	received = Program_SaveContext(jump_context);
	if (received == 0)
	{
		fixture_do_jump(status);
		return (FALSE); // should never be reached
	}
	return (received == expected);
}
void	print_test_setjmp_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		int status, int expected)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_jump, status, expected)
	test.expect = expecting;
	TEST_PRINT(bool,setjmp, "status=%i (expecting setjmp to return %i)", status, expected)
}
void	test_setjmp(void)
{
/*	| TEST FUNCTION           | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_setjmp_scenario("setjmp/longjmp (round-trip)     ",	FALSE,    TRUE,      42, 42);
	print_test_setjmp_scenario("setjmp/longjmp (negative status)",	FALSE,    TRUE,      -1, -1);
	print_test_setjmp_scenario("setjmp/longjmp (status 0 -> 1)  ",	FALSE,    TRUE,      0,  1);
}
#endif



/*============================================================================*\
||                     Tests: Environment Communication                       ||
\*============================================================================*/



#ifndef c_getenv
void test_getenv(void)	{}
#warning "getenv() test suite function defined, but the function isn't defined."
#else
void	print_test_getenv(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* name)
{
	TEST_INIT(str)
	TEST_PERFORM(	getenv, name)
	TEST_PRINT(str,	getenv, "name=\"%s\"", name)
	TEST_FREE() // NB: the string returned by Program_GetEnv() is a newly allocated duplicate
}
void	test_getenv(void)
{
	fixture_setenv("LIBCCC_TEST_GETENV", "some value");
/*	| TEST FUNCTION   | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_getenv("getenv                          ",	FALSE,        "some value", "LIBCCC_TEST_GETENV");
	print_test_getenv("getenv (missing variable)       ",	FALSE,        NULL,         "LIBCCC_TEST_NO_SUCH_VARIABLE");
	print_test_getenv("getenv (empty name)             ",	FALSE,        NULL,         "");
	print_test_getenv("getenv (null name)              ",	ALLOW_SIGSEGV, NULL,        NULL);
}
#endif



#ifndef c_setenv
void test_setenv(void)	{}
#warning "setenv() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: sets an environment variable with setenv(), then verifies its value independently, with a raw libc getenv() call
static
t_bool	scenario_setenv(char const* name, char const* value, t_bool overwrite, char const* expected)
{
	char*	result;

	if (Program_SetEnv(name, value, overwrite) != ERROR_NONE)
		return (FALSE);
	result = getenv(name);
	return (result != NULL && strcmp(result, expected) == 0);
}
void	print_test_setenv(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* name, char const* value, t_bool overwrite)
{
	TEST_INIT(sint)
	TEST_PERFORM(	setenv, name, value, overwrite)
	TEST_PRINT(sint,setenv, "name=\"%s\", value=\"%s\", overwrite=%s", name, value, overwrite ? "TRUE" : "FALSE")
}
void	print_test_setenv_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* name, char const* value, t_bool overwrite, char const* expected)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_setenv, name, value, overwrite, expected)
	test.expect = expecting;
	TEST_PRINT(bool,setenv, "name=\"%s\", value=\"%s\", overwrite=%s (verifying with raw getenv)", name, value, overwrite ? "TRUE" : "FALSE")
}
void	test_setenv(void)
{
	fixture_setenv("LIBCCC_TEST_SETENV_PRE", "initial");
/*	| TEST FUNCTION            | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_setenv_scenario ("setenv (new variable)           ",	FALSE,        TRUE,
		"LIBCCC_TEST_SETENV_NEW", "hello", TRUE,  "hello");
	print_test_setenv_scenario ("setenv (overwrite existing)     ",	FALSE,        TRUE,
		"LIBCCC_TEST_SETENV_PRE", "changed", TRUE,  "changed");
	print_test_setenv_scenario ("setenv (no overwrite: keeps old)",	FALSE,        TRUE,
		"LIBCCC_TEST_SETENV_PRE", "ignored", FALSE, "changed");
	print_test_setenv          ("setenv (null name)              ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL, "value", TRUE);
	print_test_setenv          ("setenv (null value)             ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, "LIBCCC_TEST_SETENV_NEW", NULL, TRUE);
}
#endif



#ifndef c_unsetenv
void test_unsetenv(void)	{}
#warning "unsetenv() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: deletes an environment variable with unsetenv(), then verifies independently (raw libc) that it is truly gone
static
t_bool	scenario_unsetenv(char const* name)
{
	if (Program_UnsetEnv(name) != ERROR_NONE)
		return (FALSE);
	return (getenv(name) == NULL);
}
void	print_test_unsetenv(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* name)
{
	TEST_INIT(sint)
	TEST_PERFORM(	unsetenv, name)
	TEST_PRINT(sint,unsetenv, "name=\"%s\"", name)
}
void	print_test_unsetenv_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* name)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_unsetenv, name)
	test.expect = expecting;
	TEST_PRINT(bool,unsetenv, "name=\"%s\" (verifying with raw getenv)", name)
}
void	test_unsetenv(void)
{
	fixture_setenv("LIBCCC_TEST_UNSETENV", "to be deleted");
/*	| TEST FUNCTION              | TEST NAME                       | TESTFLAGS     | EXPECTING  | TEST ARGS			*/
	print_test_unsetenv_scenario ("unsetenv (existing variable)    ",	FALSE,        TRUE,       "LIBCCC_TEST_UNSETENV");
	print_test_unsetenv          ("unsetenv (missing variable)     ",	FALSE,        ERROR_NONE, "LIBCCC_TEST_NO_SUCH_VARIABLE");
	print_test_unsetenv          ("unsetenv (null name)            ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



/*============================================================================*\
||                      Tests: Working Directory & Process                    ||
\*============================================================================*/



#ifndef c_getcwd
void test_getcwd(void)	{}
#warning "getcwd() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: gets the current working directory, and verifies (with raw libc) that it is a real, existing directory
static
t_bool	scenario_getcwd(void)
{
	char*	cwd;
	t_bool	result;

	cwd = Program_GetCWD();
	if (cwd == NULL || cwd[0] == '\0')
		return (FALSE);
	result = fixture_isdir(cwd);
	free(cwd);
	return (result);
}
void	print_test_getcwd_scenario(char const* test_name, t_testflags flags,
		t_bool expecting)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_getcwd)
	test.expect = expecting;
	TEST_PRINT(bool,getcwd, "(verifying that the returned path is a real directory)")
}
void	test_getcwd(void)
{
/*	| TEST FUNCTION           | TEST NAME                       | TESTFLAGS | EXPECTING	*/
	print_test_getcwd_scenario("getcwd (is a real directory)    ",	FALSE,    TRUE);
}
#endif



#ifndef c_chdir
void test_chdir(void)	{}
#warning "chdir() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: creates a folder, changes the working directory into it, verifies, then restores the previous working directory
static
t_bool	scenario_chdir(void)
{
	char*	cwd_before;
	char*	cwd_after;
	t_bool	result = TRUE;

	cwd_before = Program_GetCWD();
	if (cwd_before == NULL)
		return (FALSE);
	fixture_mkdir("libccc_test_chdir_tmp");
	if (Program_SetCWD("libccc_test_chdir_tmp") != ERROR_NONE)
		result = FALSE;
	cwd_after = Program_GetCWD();
	if (!fixture_endswith(cwd_after, "libccc_test_chdir_tmp"))
		result = FALSE;
	// CRITICAL: restore the previous working directory (other test suites depend on it)
	if (fixture_chdir(cwd_before) != 0)
		result = FALSE;
	fixture_rmdir("libccc_test_chdir_tmp");
	free(cwd_before);
	free(cwd_after);
	return (result);
}
void	print_test_chdir(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* path)
{
	TEST_INIT(sint)
	TEST_PERFORM(	chdir, path)
	TEST_PRINT(sint,chdir, "path=\"%s\"", path)
}
void	print_test_chdir_scenario(char const* test_name, t_testflags flags,
		t_bool expecting)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_chdir)
	test.expect = expecting;
	TEST_PRINT(bool,chdir, "(chdir into a new folder, verify, restore)")
}
void	test_chdir(void)
{
/*	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_chdir_scenario("chdir (round-trip)              ",	FALSE,        TRUE);
	print_test_chdir         ("chdir (missing directory)       ",	FALSE,        ERROR_SYSTEM, "libccc_test_no_such_directory");
	print_test_chdir         ("chdir (null path)               ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



#ifndef c_getpid
void test_getpid(void)	{}
#warning "getpid() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: checks that the returned PID is strictly positive (and, on POSIX, that it matches the raw libc getpid())
static
t_bool	scenario_getpid(void)
{
	t_sint	pid = Program_GetPID();

	if (pid <= 0)
		return (FALSE);
#if (!defined(_WIN32) || defined(__CYGWIN__))
	if (pid != (t_sint)getpid())
		return (FALSE);
#endif
	return (TRUE);
}
void	print_test_getpid_scenario(char const* test_name, t_testflags flags,
		t_bool expecting)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_getpid)
	test.expect = expecting;
	TEST_PRINT(bool,getpid, "(verifying against the raw libc getpid)")
}
void	test_getpid(void)
{
/*	| TEST FUNCTION           | TEST NAME                       | TESTFLAGS | EXPECTING	*/
	print_test_getpid_scenario("getpid                          ",	FALSE,    TRUE);
}
#endif



#ifndef c_getexepath
void test_getexepath(void)	{}
#warning "getexepath() test suite function defined, but the function isn't defined."
#else
//! SCENARIO: checks that the returned executable path is absolute, and refers to a real, existing file
static
t_bool	scenario_getexepath(void)
{
	char*	path;
	t_bool	result;

	path = Program_GetExecutablePath();
	if (path == NULL)
		return (FALSE);
	result = (fixture_isfile(path)
#ifdef _WIN32
		&& (path[1] == ':' || path[0] == '\\')
#else
		&& (path[0] == '/')
#endif
	);
	free(path);
	return (result);
}
void	print_test_getexepath_scenario(char const* test_name, t_testflags flags,
		t_bool expecting)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_getexepath)
	test.expect = expecting;
	TEST_PRINT(bool,getexepath, "(verifying that the path is absolute, and a real file)")
}
void	test_getexepath(void)
{
/*	| TEST FUNCTION               | TEST NAME                       | TESTFLAGS | EXPECTING	*/
	print_test_getexepath_scenario("getexepath (absolute real file) ",	FALSE,    TRUE);
}
#endif



/*============================================================================*\
||                          Tests: Running Commands                           ||
\*============================================================================*/



#ifndef c_system
void test_system(void)	{}
#warning "system() test suite function defined, but the function isn't defined."
#else
void	print_test_system(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		char const* command)
{
	TEST_INIT(sint)
	TEST_PERFORM(	system, command)
	TEST_PRINT(sint,system, "command=\"%s\"", command)
}
void	test_system(void)
{
	fflush(NULL); // avoid duplicated buffered output in the command processor subprocess
/*	| TEST FUNCTION   | TEST NAME                       | TESTFLAGS     | EXPECTING    | TEST ARGS			*/
	print_test_system("system (successful command)     ",	FALSE,        ERROR_NONE,   "exit 0");
	print_test_system("system (failing command)        ",	FALSE,        ERROR_SYSTEM, "exit 1");
	print_test_system("system (null command)           ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, NULL);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_sys_program(void)
{
	print_suite_title("libccc/sys/program");

	test_exit();
	test_setjmp();
	test_getenv();
	test_setenv();
	test_unsetenv();
	test_getcwd();
	test_chdir();
	test_getpid();
	test_getexepath();
	test_system();

	return (OK);
}
