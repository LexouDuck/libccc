
#include <signal.h>

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/sys/signal.h"

#include "test.h"
#include "test_utils.h"

#if (!defined(_WIN32) || defined(__CYGWIN__))
	#include <unistd.h>
	#include <sys/wait.h>
	#define FORK_SCENARIOS	1
#else
	#define FORK_SCENARIOS	0
#endif



/*============================================================================*\
||                           Test Fixtures (Helpers)                          ||
\*============================================================================*/

/*
**	The signal-handling functions of this header are inherently stateful, so
**	(much like the `libccc/sys/network` suite) they are exercised through
**	self-contained "scenario" helper functions, each of which reduces its
**	observable outcome to a single comparable value.
**
**	NB: The libccc-test framework itself installs handlers for `SIGABRT`,
**	`SIGSEGV`, `SIGILL` and `SIGFPE` (to catch crashes during tests): so, the
**	scenarios below only ever manipulate the handling of signals which the
**	framework does not use (`SIGUSR1`/`SIGUSR2` on POSIX, `SIGINT`/`SIGTERM`
**	on Windows), and always restore default handling before returning.
*/

//! A signal which is safe for these tests to manipulate (ie: unused by the test framework)
#ifdef SIGUSR1
#define TEST_SIGNAL_1	SIGUSR1
#else
#define TEST_SIGNAL_1	SIGINT
#endif
//! Another signal which is safe for these tests to manipulate (ie: unused by the test framework)
#ifdef SIGUSR2
#define TEST_SIGNAL_2	SIGUSR2
#else
#define TEST_SIGNAL_2	SIGTERM
#endif

//! FIXTURE: stores the signal value most recently received by fixture_handler()
static volatile t_sigatomic	received_signal = 0;

//! FIXTURE: a basic signal handler, which simply stores the received signal value
static
void	fixture_handler(int signaltype)
{
	received_signal = signaltype;
}



//! SCENARIO: sets a handler for `signum`, raises it, checks that the handler truly received it, then restores default handling
static
t_bool	scenario_signal_handled(t_signal signum)
{
	t_bool	result = TRUE;

	received_signal = 0;
	if (Signal_SetHandler(signum, fixture_handler) != ERROR_NONE)
		return (FALSE);
	if (Signal_Raise(signum) != ERROR_NONE)
		result = FALSE;
	if (received_signal != signum) // the handler should have been called, with this exact signal value
		result = FALSE;
	if (Signal_Reset(signum) != ERROR_NONE)
		result = FALSE;
	return (result);
}

//! SCENARIO: sets `signum` to be ignored, raises it (the program should survive), then restores default handling
static
t_bool	scenario_signal_ignored(t_signal signum)
{
	t_bool	result = TRUE;

	received_signal = 0;
	if (Signal_Ignore(signum) != ERROR_NONE)
		return (FALSE);
	if (Signal_Raise(signum) != ERROR_NONE) // if the signal were not ignored, this would terminate the program
		result = FALSE;
	if (received_signal != 0) // no handler should have been called
		result = FALSE;
	if (Signal_Reset(signum) != ERROR_NONE)
		result = FALSE;
	return (result);
}

#if FORK_SCENARIOS
//! SCENARIO: checks that Signal_Reset() truly restores the default handling: a forked child process which raises `signum` should be terminated by it
static
t_bool	scenario_signal_reset(t_signal signum)
{
	pid_t	pid;
	int		status;

	// first, set a handler, then reset default handling: the default action for these signals is termination
	if (Signal_SetHandler(signum, fixture_handler) != ERROR_NONE)
		return (FALSE);
	if (Signal_Reset(signum) != ERROR_NONE)
		return (FALSE);
	fflush(NULL); // avoid duplicated buffered output in the forked child
	pid = fork();
	if (pid < 0)
		return (FALSE);
	if (pid == 0)
	{	// child process: raising the signal should terminate this process immediately
		Signal_Raise(signum);
		_exit(111); // should never be reached
	}
	if (waitpid(pid, &status, 0) < 0)
		return (FALSE);
	return (WIFSIGNALED(status) && WTERMSIG(status) == signum);
}
#endif



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#ifndef c_signal
void test_signal(void)	{}
#warning "signal() test suite function defined, but the function isn't defined."
#else
void	print_test_signal(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		t_signal signum,
		f_signalhandler handler)
{
	TEST_INIT(sint)
	TEST_PERFORM(	signal, signum, handler)
	TEST_PRINT(sint,signal, "signal=%i, handler=%p", signum, (void*)handler)
	// restore default handling, in case the tested call succeeded
	if (handler != NULL)
		Signal_Reset(signum);
}
void	print_test_signal_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_signal signum)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_signal_handled, signum)
	test.expect = expecting;
	TEST_PRINT(bool,signal, "signal=%s(%i) (set handler, raise, verify received, reset)", Signal_GetName(signum), signum)
}
void	test_signal(void)
{
/*	| TEST FUNCTION           | TEST NAME                       | TESTFLAGS     | EXPECTING | TEST ARGS			*/
	print_test_signal_scenario("signal (handler receives raise) ",	FALSE,        TRUE,      TEST_SIGNAL_1);
	print_test_signal_scenario("signal (other signal)           ",	FALSE,        TRUE,      TEST_SIGNAL_2);
	print_test_signal         ("signal (null handler)           ",	ALLOW_SIGSEGV, ERROR_NULLPOINTER, TEST_SIGNAL_1, NULL);
}
#endif



#ifndef c_sigignore
void test_sigignore(void)	{}
#warning "sigignore() test suite function defined, but the function isn't defined."
#else
void	print_test_sigignore_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_signal signum)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_signal_ignored, signum)
	test.expect = expecting;
	TEST_PRINT(bool,sigignore, "signal=%s(%i) (ignore, raise, verify survival, reset)", Signal_GetName(signum), signum)
}
void	test_sigignore(void)
{
/*	| TEST FUNCTION              | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_sigignore_scenario("sigignore (raise is survived)   ",	FALSE,    TRUE,      TEST_SIGNAL_1);
	print_test_sigignore_scenario("sigignore (other signal)        ",	FALSE,    TRUE,      TEST_SIGNAL_2);
}
#endif



#ifndef c_sigreset
void test_sigreset(void)	{}
#warning "sigreset() test suite function defined, but the function isn't defined."
#else
#if FORK_SCENARIOS
void	print_test_sigreset_scenario(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_signal signum)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, scenario_signal_reset, signum)
	test.expect = expecting;
	TEST_PRINT(bool,sigreset, "signal=%s(%i) (default action terminates a forked child)", Signal_GetName(signum), signum)
}
#endif
void	test_sigreset(void)
{
#if FORK_SCENARIOS
/*	| TEST FUNCTION             | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS			*/
	print_test_sigreset_scenario("sigreset (default is restored)  ",	FALSE,    TRUE,      TEST_SIGNAL_1);
	print_test_sigreset_scenario("sigreset (other signal)         ",	FALSE,    TRUE,      TEST_SIGNAL_2);
#endif
}
#endif



#ifndef c_raise
void test_raise(void)	{}
#warning "raise() test suite function defined, but the function isn't defined."
#else
void	print_test_raise(char const* test_name, t_testflags flags,
		e_cccerror expecting,
		t_signal signum)
{
	TEST_INIT(sint)
	TEST_PERFORM(	raise, signum)
	TEST_PRINT(sint,raise, "signal=%i", signum)
}
void	test_raise(void)
{
	// NB: the "successful raise" cases are already covered by the test_signal()/test_sigignore() scenarios above
	// (a raw raise call here, without a handler installed, would terminate the test runner program)
/*	| TEST FUNCTION  | TEST NAME                       | TESTFLAGS | EXPECTING    | TEST ARGS			*/
	print_test_raise("raise (invalid signal)          ",	FALSE,    ERROR_SYSTEM, -1);
	print_test_raise("raise (invalid signal, huge)    ",	FALSE,    ERROR_SYSTEM, 99999);
}
#endif



#ifndef c_signame
void test_signame(void)	{}
#warning "signame() test suite function defined, but the function isn't defined."
#else
void	print_test_signame(char const* test_name, t_testflags flags,
		char const* expecting,
		t_signal signum)
{
	TEST_INIT(str)
	TEST_PERFORM(	signame, signum)
	TEST_PRINT(str,	signame, "signal=%i", signum)
	// NB: no TEST_FREE() here: the string returned by Signal_GetName() is a constant literal
}
void	test_signame(void)
{
/*	| TEST FUNCTION    | TEST NAME                       | TESTFLAGS | EXPECTING  | TEST ARGS			*/
	print_test_signame("signame (SIGABRT)               ",	FALSE,    "SIGABRT",  SIGABRT);
	print_test_signame("signame (SIGFPE)                ",	FALSE,    "SIGFPE",   SIGFPE);
	print_test_signame("signame (SIGILL)                ",	FALSE,    "SIGILL",   SIGILL);
	print_test_signame("signame (SIGINT)                ",	FALSE,    "SIGINT",   SIGINT);
	print_test_signame("signame (SIGSEGV)               ",	FALSE,    "SIGSEGV",  SIGSEGV);
	print_test_signame("signame (SIGTERM)               ",	FALSE,    "SIGTERM",  SIGTERM);
#ifdef SIGKILL
	print_test_signame("signame (SIGKILL)               ",	FALSE,    "SIGKILL",  SIGKILL);
#endif
#ifdef SIGPIPE
	print_test_signame("signame (SIGPIPE)               ",	FALSE,    "SIGPIPE",  SIGPIPE);
#endif
#ifdef SIGWINCH
	print_test_signame("signame (SIGWINCH)              ",	FALSE,    "SIGWINCH", SIGWINCH);
#endif
	print_test_signame("signame (invalid signal)        ",	FALSE,    NULL,       -12345);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_sys_signal(void)
{
	print_suite_title("libccc/sys/signal");

	test_signal();
	test_sigignore();
	test_sigreset();
	test_raise();
	test_signame();

	return (OK);
}
