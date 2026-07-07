
#include "libccc/generic/tree.c"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

/*
**	NOTE: this test suite exercises the default instantiation of the generic
**	tree type (ie: `T` is `void*`, and `T_NAME` is `any`), which is included
**	just above. With this instantiation, the `T_EQUALS()` macro is a simple
**	pointer comparison: all of the value-based tree functions (Find, Contains,
**	Count, Remove, etc) match values by their pointer *identity*.
**
**	The values used are `char*` strings, so that expected results can be
**	written legibly: every tree-returning function is tested by serializing
**	the result tree into a nested string of the form `"(value (sub1) (sub2 (sub21)))"`
**	(sub-nodes in order, visited recursively), and comparing with `print_test_str`.
**
**	The standard test fixture is the following 4-node, 3-level tree:
**	        "Omae"
**	       /      \
**	   " wa "    "mou "
**	                |
**	          "shindeiru."
*/

//! The values used to build the test trees (matching values must be the same pointer)
static char* const	g_tree_val[4] =
{
	"Omae",
	" wa ",
	"mou ",
	"shindeiru.",
};
//! Has the same content as `g_tree_val[0]`, but is a different pointer
static char	g_tree_val_twin[] = "Omae";
//! An extra value, not present in the standard fixture
static char	g_tree_val_extra[] = "NANI";

//! (recursive part of gen_tree_tostr)
static
void	gen_tree_tostr_rec(s_tree(any) const* tree, char* buffer, size_t* offset, size_t capacity)
{
	char const*	val = (tree->value ? (char const*)tree->value : "NULL");
	*offset += snprintf(buffer + *offset, capacity - *offset, "(%s", val);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		*offset += snprintf(buffer + *offset, capacity - *offset, " ");
		gen_tree_tostr_rec(&tree->nodes[i], buffer, offset, capacity);
	}
	*offset += snprintf(buffer + *offset, capacity - *offset, ")");
}

//! Serializes the given tree into a newly allocated string: `"(value (sub1) (sub2 (sub21)))"`
static
char*	gen_tree_tostr(s_tree(any) const* tree)
{
	char	buffer[512];
	size_t	offset = 0;

	if (tree == NULL)
		return (strdup("(null)"));
	gen_tree_tostr_rec(tree, buffer, &offset, sizeof(buffer));
	return (strdup(buffer));
}

//! Serializes the given tree (like gen_tree_tostr()), and then deletes it
static
char*	gen_tree_consume(s_tree(any)* tree)
{
	char*	result = gen_tree_tostr(tree);
	if (tree)
		c_treefree(any)(tree);
	return (result);
}

//! Builds the standard 4-node test tree (see the diagram at the top of this file)
static
s_tree(any)*	gen_tree_fixture(void)
{
	s_tree(any)*	root = c_treenew(any)((void*)g_tree_val[0]);
	s_tree(any)*	mou;
	c_treeappend(any)(root, c_treeitem(any)((void*)g_tree_val[1]));
	mou = c_treeappend(any)(root, c_treeitem(any)((void*)g_tree_val[2]));
	c_treeappend(any)(mou, c_treeitem(any)((void*)g_tree_val[3]));
	return (root);
}

//! The expected serialization of the standard test tree fixture
#define GEN_TREE_FIXTURE_STR	"(Omae ( wa ) (mou  (shindeiru.)))"



/*============================================================================*\
||                           Tree: basic operations                           ||
\*============================================================================*/

#ifndef c_treeitem
void test_treeitem(void)	{}
#warning "treeitem() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeitem(void)
{
	s_tree(any)	node = c_treeitem(any)((void*)g_tree_val[0]);
	if (node.node_count != 0 || node.nodes != NULL)
		return (strdup("(not a leaf)"));
	return (gen_tree_tostr(&node));
}
void	print_test_treeitem(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeitem)
	TEST_PRINT(str,	treeitem, "value=\"Omae\"")
	TEST_FREE()
}
void	test_treeitem(void)
{
//	| TEST FUNCTION     | TEST NAME       |TESTFLAG| EXPECTING
	print_test_treeitem("treeitem       ",	FALSE,	"(Omae)");
}
#endif



#ifndef c_treenew
void test_treenew(void)	{}
#warning "treenew() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treenew(void)
{
	s_tree(any)*	node = c_treenew(any)((void*)g_tree_val[0]);
	if (node == NULL)
		return (strdup("(null)"));
	if (node->node_count != 0 || node->nodes != NULL)
	{
		c_treefree(any)(node);
		return (strdup("(not a leaf)"));
	}
	return (gen_tree_consume(node));
}
void	print_test_treenew(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treenew)
	TEST_PRINT(str,	treenew, "value=\"Omae\"")
	TEST_FREE()
}
void	test_treenew(void)
{
//	| TEST FUNCTION    | TEST NAME       |TESTFLAG| EXPECTING
	print_test_treenew("treenew        ",	FALSE,	"(Omae)");
}
#endif



#ifndef c_treecreate
void test_treecreate(void)	{}
#warning "treecreate() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treecreate(t_uint n)
{
	s_tree(any)*	tree = NULL;
	if (n == 0)
		tree = c_treecreate(any)((void*)g_tree_val[0], 0);
	else if (n == 2)
		tree = c_treecreate(any)((void*)g_tree_val[0], 2,
			(void*)g_tree_val[1], (void*)g_tree_val[2]);
	else if (n == 3)
		tree = c_treecreate(any)((void*)g_tree_val[0], 3,
			(void*)g_tree_val[1], (void*)g_tree_val[2], (void*)g_tree_val[3]);
	return (gen_tree_consume(tree));
}
void	print_test_treecreate(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint n)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treecreate, n)
	TEST_PRINT(str,	treecreate, "value=\"Omae\", n=%u", n)
	TEST_FREE()
}
void	test_treecreate(void)
{
//	| TEST FUNCTION       | TEST NAME              |TESTFLAG| EXPECTING                            | TEST ARGS
	print_test_treecreate("treecreate (leaf)    ",	FALSE,	"(Omae)",                              0);
	print_test_treecreate("treecreate (2 nodes) ",	FALSE,	"(Omae ( wa ) (mou ))",                2);
	print_test_treecreate("treecreate (3 nodes) ",	FALSE,	"(Omae ( wa ) (mou ) (shindeiru.))",   3);
}
#endif



#ifndef c_treedup
void test_treedup(void)	{}
#warning "treedup() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treedup(void)
{
	s_tree(any)*	original = gen_tree_fixture();
	s_tree(any)*	result = c_treedup(any)(original);
	c_treefree(any)(original); // the duplicate (a deep copy) must survive its original being freed
	return (gen_tree_consume(result));
}
void	print_test_treedup(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treedup)
	TEST_PRINT(str,	treedup, "tree=(fixture)")
	TEST_FREE()
}
void	test_treedup(void)
{
//	| TEST FUNCTION    | TEST NAME       |TESTFLAG| EXPECTING
	print_test_treedup("treedup        ",	FALSE,	GEN_TREE_FIXTURE_STR);
}
#endif



#ifndef c_treeclear
void test_treeclear(void)	{}
#warning "treeclear() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeclear(void)
{
	s_tree(any)*	tree = gen_tree_fixture();
	c_treeclear(any)(tree); // deletes every sub-node, but not the node itself
	if (tree->node_count != 0 || tree->nodes != NULL)
	{
		c_treefree(any)(tree);
		return (strdup("(not cleared)"));
	}
	return (gen_tree_consume(tree));
}
void	print_test_treeclear(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeclear)
	TEST_PRINT(str,	treeclear, "tree=(fixture)")
	TEST_FREE()
}
void	test_treeclear(void)
{
//	| TEST FUNCTION      | TEST NAME        |TESTFLAG| EXPECTING
	print_test_treeclear("treeclear       ",	FALSE,	"(Omae)");
}
#endif



#ifndef c_treefclear
void test_treefclear(void)	{}
#warning "treefclear() test suite function defined, but the function isn't defined."
#else
static t_uint	g_treefclear_count = 0;
static void	gen_treefclear_delete(void* value)
{
	(void)value;
	g_treefclear_count += 1;
}
static t_uint	c_gen_treefclear(void)
{
	s_tree(any)*	tree = gen_tree_fixture();
	g_treefclear_count = 0;
	c_treefclear(any)(tree, gen_treefclear_delete);
	c_treefree(any)(tree);
	return (g_treefclear_count); // del() must be called for every DESCENDANT value (3), but not the root's
}
void	print_test_treefclear(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_treefclear)
	TEST_PRINT(uint,	treefclear, "tree=(fixture), del=(counting function)")
}
void	test_treefclear(void)
{
//	| TEST FUNCTION       | TEST NAME         |TESTFLAG| EXPECTING
	print_test_treefclear("treefclear       ",	FALSE,	3);
}
#endif



#ifndef c_treefdel
void test_treefdel(void)	{}
#warning "treefdel() test suite function defined, but the function isn't defined."
#else
static t_uint	g_treefdel_count = 0;
static void	gen_treefdel_delete(void* value)
{
	(void)value;
	g_treefdel_count += 1;
}
static t_uint	c_gen_treefdel(t_bool leaf_only)
{
	s_tree(any)*	tree = (leaf_only ? c_treenew(any)((void*)g_tree_val[0]) : gen_tree_fixture());
	g_treefdel_count = 0;
	c_treefdel(any)(&tree, gen_treefdel_delete);
	if (tree != NULL) // the given pointer must have been set to NULL
		return ((t_uint)-1);
	return (g_treefdel_count); // del() must be called for EVERY value of the tree, including the root's
}
void	print_test_treefdel(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_bool leaf_only)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_treefdel, leaf_only)
	TEST_PRINT(uint,	treefdel, "tree=(%s), del=(counting function)", (leaf_only ? "single leaf" : "fixture"))
}
void	test_treefdel(void)
{
//	| TEST FUNCTION     | TEST NAME        |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treefdel("treefdel        ",	FALSE,	4,          FALSE);
	print_test_treefdel("treefdel (leaf) ",	FALSE,	1,          TRUE);
}
#endif



#ifndef c_treeget
void test_treeget(void)	{}
#warning "treeget() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeget(t_size index, t_bool from_leaf)
{
	s_tree(any)*	tree = (from_leaf ? c_treenew(any)((void*)g_tree_val[0]) : gen_tree_fixture());
	s_tree(any)*	node = c_treeget(any)(tree, index);
	char*	result = gen_tree_tostr(node); // (gen_tree_tostr handles NULL gracefully)
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treeget(char const* test_name, t_testflags flags,
		char const* expecting,
		t_size index,
		t_bool from_leaf)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeget, index, from_leaf)
	TEST_PRINT(str,	treeget, "tree=(%s), index=" SF_SIZE, (from_leaf ? "single leaf" : "fixture"), index)
	TEST_FREE()
}
void	test_treeget(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_treeget("treeget (first)       ",	FALSE,	"( wa )",                0, FALSE);
	print_test_treeget("treeget (second)      ",	FALSE,	"(mou  (shindeiru.))",    1, FALSE);
	print_test_treeget("treeget (out of range)",	FALSE,	"(null)",                2, FALSE);
	print_test_treeget("treeget (from a leaf) ",	FALSE,	"(null)",                0, TRUE);
}
#endif



#ifndef c_treeset
void test_treeset(void)	{}
#warning "treeset() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeset(t_size index)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	node = c_treeset(any)(tree, index, c_treeitem(any)((void*)g_tree_val_extra));
	if (index < 2 && node == NULL)
	{
		c_treefree(any)(tree);
		return (strdup("(set returned NULL)"));
	}
	return (gen_tree_consume(tree));
}
void	print_test_treeset(char const* test_name, t_testflags flags,
		char const* expecting,
		t_size index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeset, index)
	TEST_PRINT(str,	treeset, "tree=(fixture), index=" SF_SIZE ", node=(NANI leaf)", index)
	TEST_FREE()
}
void	test_treeset(void)
{
//	| TEST FUNCTION    | TEST NAME               |TESTFLAG| EXPECTING                        | TEST ARGS
	print_test_treeset("treeset (first)       ",	FALSE,	"(Omae (NANI) (mou  (shindeiru.)))", 0);
	print_test_treeset("treeset (subtree)     ",	FALSE,	"(Omae ( wa ) (NANI))",             1);
	print_test_treeset("treeset (out of range)",	FALSE,	GEN_TREE_FIXTURE_STR,               2);
}
#endif



/*============================================================================*\
||                          Tree: editing operations                          ||
\*============================================================================*/

#ifndef c_treeappend
void test_treeappend(void)	{}
#warning "treeappend() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeappend(t_uint variant)
{
	s_tree(any)*	tree = gen_tree_fixture();
	if (variant == 0) // append a leaf to the root node
		c_treeappend(any)(tree, c_treeitem(any)((void*)g_tree_val_extra));
	else if (variant == 1) // append a leaf to a nested node (the " wa " leaf, making it grow)
		c_treeappend(any)(c_treeget(any)(tree, 0), c_treeitem(any)((void*)g_tree_val_extra));
	else if (variant == 2) // append a whole subtree by value (ownership is transferred)
	{
		s_tree(any)*	subtree = c_treecreate(any)((void*)g_tree_val_extra, 2,
			(void*)g_tree_val[1], (void*)g_tree_val[2]);
		c_treeappend(any)(tree, *subtree);
		free(subtree); // only the temporary top-level "shell" struct needs freeing
	}
	return (gen_tree_consume(tree));
}
void	print_test_treeappend(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeappend, variant)
	TEST_PRINT(str,	treeappend, "tree=(fixture), node=(variant %u)", variant)
	TEST_FREE()
}
void	test_treeappend(void)
{
//	| TEST FUNCTION       | TEST NAME             |TESTFLAG| EXPECTING                                        | TEST ARGS
	print_test_treeappend("treeappend (to root) ",	FALSE,	"(Omae ( wa ) (mou  (shindeiru.)) (NANI))",         0);
	print_test_treeappend("treeappend (nested)  ",	FALSE,	"(Omae ( wa  (NANI)) (mou  (shindeiru.)))",          1);
	print_test_treeappend("treeappend (subtree) ",	FALSE,	"(Omae ( wa ) (mou  (shindeiru.)) (NANI ( wa ) (mou )))", 2);
}
#endif



#ifndef c_treeprepend
void test_treeprepend(void)	{}
#warning "treeprepend() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeprepend(void)
{
	s_tree(any)*	tree = gen_tree_fixture();
	c_treeprepend(any)(tree, c_treeitem(any)((void*)g_tree_val_extra));
	return (gen_tree_consume(tree));
}
void	print_test_treeprepend(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeprepend)
	TEST_PRINT(str,	treeprepend, "tree=(fixture), node=(NANI leaf)")
	TEST_FREE()
}
void	test_treeprepend(void)
{
//	| TEST FUNCTION        | TEST NAME         |TESTFLAG| EXPECTING
	print_test_treeprepend("treeprepend      ",	FALSE,	"(Omae (NANI) ( wa ) (mou  (shindeiru.)))");
}
#endif



#ifndef c_treeinsert
void test_treeinsert(void)	{}
#warning "treeinsert() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeinsert(t_size index)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	node = c_treeinsert(any)(tree, c_treeitem(any)((void*)g_tree_val_extra), index);
	if (index <= 2 && node == NULL)
	{
		c_treefree(any)(tree);
		return (strdup("(insert returned NULL)"));
	}
	return (gen_tree_consume(tree));
}
void	print_test_treeinsert(char const* test_name, t_testflags flags,
		char const* expecting,
		t_size index)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeinsert, index)
	TEST_PRINT(str,	treeinsert, "tree=(fixture), node=(NANI leaf), index=" SF_SIZE, index)
	TEST_FREE()
}
void	test_treeinsert(void)
{
//	| TEST FUNCTION       | TEST NAME                  |TESTFLAG| EXPECTING                                 | TEST ARGS
	print_test_treeinsert("treeinsert (beginning)   ",	FALSE,	"(Omae (NANI) ( wa ) (mou  (shindeiru.)))",  0);
	print_test_treeinsert("treeinsert (middle)      ",	FALSE,	"(Omae ( wa ) (NANI) (mou  (shindeiru.)))",  1);
	print_test_treeinsert("treeinsert (end)         ",	FALSE,	"(Omae ( wa ) (mou  (shindeiru.)) (NANI))",  2);
	print_test_treeinsert("treeinsert (out of range)",	FALSE,	GEN_TREE_FIXTURE_STR,                       3);
}
#endif



#ifndef c_treeremoveat
void test_treeremoveat(void)	{}
#warning "treeremoveat() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeremoveat(t_size index, t_bool nested)
{
	s_tree(any)*	tree = gen_tree_fixture();
	if (nested) // remove the only sub-node of a nested node (the "mou " node's sub-nodes array must be freed)
	{
		s_tree(any)*	mou = c_treeget(any)(tree, 1);
		c_treeremoveat(any)(mou, index);
		if (mou->node_count == 0 && mou->nodes != NULL)
		{
			c_treefree(any)(tree);
			return (strdup("(nodes not freed)"));
		}
	}
	else
		c_treeremoveat(any)(tree, index);
	return (gen_tree_consume(tree));
}
void	print_test_treeremoveat(char const* test_name, t_testflags flags,
		char const* expecting,
		t_size index,
		t_bool nested)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeremoveat, index, nested)
	TEST_PRINT(str,	treeremoveat, "tree=(fixture%s), index=" SF_SIZE, (nested ? ", nested node" : ""), index)
	TEST_FREE()
}
void	test_treeremoveat(void)
{
//	| TEST FUNCTION         | TEST NAME                   |TESTFLAG| EXPECTING                   | TEST ARGS
	print_test_treeremoveat("treeremoveat (first)      ",	FALSE,	"(Omae (mou  (shindeiru.)))",  0, FALSE);
	print_test_treeremoveat("treeremoveat (subtree)    ",	FALSE,	"(Omae ( wa ))",              1, FALSE);
	print_test_treeremoveat("treeremoveat (out of rng) ",	FALSE,	GEN_TREE_FIXTURE_STR,         2, FALSE);
	print_test_treeremoveat("treeremoveat (only node)  ",	FALSE,	"(Omae ( wa ) (mou ))",       0, TRUE);
}
#endif



#ifndef c_treefremoveat
void test_treefremoveat(void)	{}
#warning "treefremoveat() test suite function defined, but the function isn't defined."
#else
static t_uint	g_treefremoveat_count = 0;
static void	gen_treefremoveat_delete(void* value)
{
	(void)value;
	g_treefremoveat_count += 1;
}
static t_uint	c_gen_treefremoveat(t_size index)
{
	s_tree(any)*	tree = gen_tree_fixture();
	g_treefremoveat_count = 0;
	c_treefremoveat(any)(tree, index, gen_treefremoveat_delete);
	c_treefree(any)(tree);
	return (g_treefremoveat_count); // del() must be called for every value of the removed subtree
}
void	print_test_treefremoveat(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_size index)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_treefremoveat, index)
	TEST_PRINT(uint,	treefremoveat, "tree=(fixture), index=" SF_SIZE ", del=(counting function)", index)
}
void	test_treefremoveat(void)
{
//	| TEST FUNCTION          | TEST NAME                 |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treefremoveat("treefremoveat (leaf)    ",	FALSE,	1,          0);
	print_test_treefremoveat("treefremoveat (subtree) ",	FALSE,	2,          1);
}
#endif



#ifndef c_treeremove
void test_treeremove(void)	{}
#warning "treeremove() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeremove(void* value)
{
	s_tree(any)*	tree = gen_tree_fixture();
	c_treeremove(any)(tree, value);
	return (gen_tree_consume(tree));
}
void	print_test_treeremove(char const* test_name, t_testflags flags,
		char const* expecting,
		void* value)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeremove, value)
	TEST_PRINT(str,	treeremove, "tree=(fixture), value=\"%s\"", (value ? (char const*)value : "NULL"))
	TEST_FREE()
}
void	test_treeremove(void)
{
//	| TEST FUNCTION       | TEST NAME                  |TESTFLAG| EXPECTING                   | TEST ARGS
	print_test_treeremove("treeremove (leaf)        ",	FALSE,	"(Omae (mou  (shindeiru.)))",  (void*)g_tree_val[1]);
	print_test_treeremove("treeremove (subtree)     ",	FALSE,	"(Omae ( wa ))",              (void*)g_tree_val[2]);
	print_test_treeremove("treeremove (grandchild)  ",	FALSE,	GEN_TREE_FIXTURE_STR,         (void*)g_tree_val[3]);
	print_test_treeremove("treeremove (twin pointer)",	FALSE,	GEN_TREE_FIXTURE_STR,         (void*)g_tree_val_twin);
}
#endif



#ifndef c_treeremall
void test_treeremall(void)	{}
#warning "treeremall() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treeremall(void* value, t_bool all_same)
{
	s_tree(any)*	tree;
	if (all_same) // every direct sub-node has the same value: the node must become a leaf again
		tree = c_treecreate(any)((void*)g_tree_val[0], 2,
			(void*)g_tree_val[1], (void*)g_tree_val[1]);
	else // two direct sub-nodes (out of three) share the given value
		tree = c_treecreate(any)((void*)g_tree_val[0], 3,
			(void*)g_tree_val[1], (void*)g_tree_val[2], (void*)g_tree_val[1]);
	c_treeremall(any)(tree, value);
	if (all_same && tree->node_count == 0 && tree->nodes != NULL)
	{
		c_treefree(any)(tree);
		return (strdup("(nodes not freed)"));
	}
	return (gen_tree_consume(tree));
}
void	print_test_treeremall(char const* test_name, t_testflags flags,
		char const* expecting,
		void* value,
		t_bool all_same)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeremall, value, all_same)
	TEST_PRINT(str,	treeremall, "tree=(%s), value=\"%s\"", (all_same ? "2 same-value nodes" : "3 nodes, 2 matching"), (value ? (char const*)value : "NULL"))
	TEST_FREE()
}
void	test_treeremall(void)
{
//	| TEST FUNCTION       | TEST NAME                 |TESTFLAG| EXPECTING       | TEST ARGS
	print_test_treeremall("treeremall (two matches)",	FALSE,	"(Omae (mou ))",  (void*)g_tree_val[1], FALSE);
	print_test_treeremall("treeremall (all match)  ",	FALSE,	"(Omae)",         (void*)g_tree_val[1], TRUE);
	print_test_treeremall("treeremall (no match)   ",	FALSE,	"(Omae ( wa ) (mou ) ( wa ))", (void*)g_tree_val_twin, FALSE);
}
#endif



#ifndef c_treefremall
void test_treefremall(void)	{}
#warning "treefremall() test suite function defined, but the function isn't defined."
#else
static t_uint	g_treefremall_count = 0;
static void	gen_treefremall_delete(void* value)
{
	(void)value;
	g_treefremall_count += 1;
}
static t_uint	c_gen_treefremall(void)
{	// two direct sub-nodes match; one of them has a sub-node of its own (3 values deleted in total)
	s_tree(any)*	tree = c_treecreate(any)((void*)g_tree_val[0], 3,
		(void*)g_tree_val[1], (void*)g_tree_val[2], (void*)g_tree_val[1]);
	c_treeappend(any)(c_treeget(any)(tree, 0), c_treeitem(any)((void*)g_tree_val[3]));
	g_treefremall_count = 0;
	c_treefremall(any)(tree, (void*)g_tree_val[1], gen_treefremall_delete);
	c_treefree(any)(tree);
	return (g_treefremall_count);
}
void	print_test_treefremall(char const* test_name, t_testflags flags,
		t_uint expecting)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_treefremall)
	TEST_PRINT(uint,	treefremall, "tree=(4 nodes, 2 matching + 1 sub-node), del=(counting function)")
}
void	test_treefremall(void)
{
//	| TEST FUNCTION        | TEST NAME          |TESTFLAG| EXPECTING
	print_test_treefremall("treefremall       ",	FALSE,	3);
}
#endif



/*============================================================================*\
||                         Tree: checking operations                          ||
\*============================================================================*/

#ifndef c_treesize
void test_treesize(void)	{}
#warning "treesize() test suite function defined, but the function isn't defined."
#else
static t_size	c_gen_treesize(t_bool leaf_only)
{
	s_tree(any)*	tree = (leaf_only ? c_treenew(any)((void*)g_tree_val[0]) : gen_tree_fixture());
	t_size	result = c_treesize(any)(tree);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treesize(char const* test_name, t_testflags flags,
		t_size expecting,
		t_bool leaf_only)
{
	TEST_INIT(size)
	TEST_PERFORM(gen_treesize, leaf_only)
	TEST_PRINT(size,	treesize, "tree=(%s)", (leaf_only ? "single leaf" : "fixture"))
}
void	test_treesize(void)
{
//	| TEST FUNCTION     | TEST NAME        |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treesize("treesize        ",	FALSE,	4,          FALSE);
	print_test_treesize("treesize (leaf)",	FALSE,	1,          TRUE);
}
#endif



#ifndef c_treedepth
void test_treedepth(void)	{}
#warning "treedepth() test suite function defined, but the function isn't defined."
#else
static t_size	c_gen_treedepth(t_uint variant)
{
	s_tree(any)*	tree;
	t_size	result;
	if (variant == 0)
		tree = c_treenew(any)((void*)g_tree_val[0]);
	else if (variant == 1)
		tree = c_treecreate(any)((void*)g_tree_val[0], 2, (void*)g_tree_val[1], (void*)g_tree_val[2]);
	else
		tree = gen_tree_fixture();
	result = c_treedepth(any)(tree);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treedepth(char const* test_name, t_testflags flags,
		t_size expecting,
		t_uint variant)
{
	TEST_INIT(size)
	TEST_PERFORM(gen_treedepth, variant)
	TEST_PRINT(size,	treedepth, "tree=(variant %u)", variant)
}
void	test_treedepth(void)
{
//	| TEST FUNCTION      | TEST NAME            |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treedepth("treedepth (leaf)    ",	FALSE,	1,          0);
	print_test_treedepth("treedepth (2 levels)",	FALSE,	2,          1);
	print_test_treedepth("treedepth (3 levels)",	FALSE,	3,          2);
}
#endif



#ifndef c_treefind
void test_treefind(void)	{}
#warning "treefind() test suite function defined, but the function isn't defined."
#else
static char*	c_gen_treefind(void* value)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	node = c_treefind(any)(tree, value);
	char*	result = gen_tree_tostr(node);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treefind(char const* test_name, t_testflags flags,
		char const* expecting,
		void* value)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treefind, value)
	TEST_PRINT(str,	treefind, "tree=(fixture), value=\"%s\"", (value ? (char const*)value : "NULL"))
	TEST_FREE()
}
void	test_treefind(void)
{
//	| TEST FUNCTION     | TEST NAME                 |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_treefind("treefind (root)         ",	FALSE,	GEN_TREE_FIXTURE_STR,  (void*)g_tree_val[0]);
	print_test_treefind("treefind (subtree)      ",	FALSE,	"(mou  (shindeiru.))",  (void*)g_tree_val[2]);
	print_test_treefind("treefind (deep leaf)    ",	FALSE,	"(shindeiru.)",        (void*)g_tree_val[3]);
	print_test_treefind("treefind (twin pointer) ",	FALSE,	"(null)",              (void*)g_tree_val_twin);
}
#endif



#ifndef c_treeffind
void test_treeffind(void)	{}
#warning "treeffind() test suite function defined, but the function isn't defined."
#else
static t_bool	gen_treeffind_match_one_subnode(s_tree(any) const* node)
{
	return (node->node_count == 1); // matches the "mou " node (the first node with exactly 1 sub-node)
}
static t_bool	gen_treeffind_match_none(s_tree(any) const* node)
{
	(void)node;
	return (FALSE);
}
static char*	c_gen_treeffind(t_bool match_none)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	node = c_treeffind(any)(tree,
		(match_none ? gen_treeffind_match_none : gen_treeffind_match_one_subnode));
	char*	result = gen_tree_tostr(node);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treeffind(char const* test_name, t_testflags flags,
		char const* expecting,
		t_bool match_none)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeffind, match_none)
	TEST_PRINT(str,	treeffind, "tree=(fixture), match=(%s)", (match_none ? "matches nothing" : "node_count == 1"))
	TEST_FREE()
}
void	test_treeffind(void)
{
//	| TEST FUNCTION      | TEST NAME             |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_treeffind("treeffind           ",	FALSE,	"(mou  (shindeiru.))",  FALSE);
	print_test_treeffind("treeffind (no match)",	FALSE,	"(null)",              TRUE);
}
#endif



#ifndef c_treecount
void test_treecount(void)	{}
#warning "treecount() test suite function defined, but the function isn't defined."
#else
static t_size	c_gen_treecount(void* value, t_bool multi_level)
{
	s_tree(any)*	tree;
	t_size	result;
	if (multi_level) // the same value appears at 3 different levels of the tree
	{
		tree = gen_tree_fixture();
		c_treeappend(any)(c_treeget(any)(tree, 1), c_treeitem(any)((void*)g_tree_val[0]));
		c_treeappend(any)(tree, c_treeitem(any)((void*)g_tree_val[0]));
	}
	else
		tree = gen_tree_fixture();
	result = c_treecount(any)(tree, value);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treecount(char const* test_name, t_testflags flags,
		t_size expecting,
		void* value,
		t_bool multi_level)
{
	TEST_INIT(size)
	TEST_PERFORM(gen_treecount, value, multi_level)
	TEST_PRINT(size,	treecount, "tree=(%s), value=\"%s\"", (multi_level ? "fixture + 2 dup values" : "fixture"), (value ? (char const*)value : "NULL"))
}
void	test_treecount(void)
{
//	| TEST FUNCTION      | TEST NAME                 |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treecount("treecount (one)         ",	FALSE,	1,          (void*)g_tree_val[2], FALSE);
	print_test_treecount("treecount (multi-level) ",	FALSE,	3,          (void*)g_tree_val[0], TRUE);
	print_test_treecount("treecount (twin pointer)",	FALSE,	0,          (void*)g_tree_val_twin, FALSE);
}
#endif



#ifndef c_treecontains
void test_treecontains(void)	{}
#warning "treecontains() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_treecontains(void* value)
{
	s_tree(any)*	tree = gen_tree_fixture();
	t_bool	result = c_treecontains(any)(tree, value);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treecontains(char const* test_name, t_testflags flags,
		t_bool expecting,
		void* value)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_treecontains, value)
	TEST_PRINT(bool,	treecontains, "tree=(fixture), value=\"%s\"", (value ? (char const*)value : "NULL"))
}
void	test_treecontains(void)
{
//	| TEST FUNCTION         | TEST NAME                     |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treecontains("treecontains (root)        ",	FALSE,	TRUE,       (void*)g_tree_val[0]);
	print_test_treecontains("treecontains (deep leaf)   ",	FALSE,	TRUE,       (void*)g_tree_val[3]);
	print_test_treecontains("treecontains (twin pointer)",	FALSE,	FALSE,      (void*)g_tree_val_twin);
}
#endif



#ifndef c_treehas
void test_treehas(void)	{}
#warning "treehas() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_treehas(t_uint variant, t_bool has_only)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	target = NULL;
	t_bool	result;
	if (variant == 0) // target holds every value of the fixture (and more)
	{
		target = gen_tree_fixture();
		c_treeappend(any)(target, c_treeitem(any)((void*)g_tree_val_extra));
	}
	else if (variant == 1) // target holds only some values of the fixture
		target = c_treecreate(any)((void*)g_tree_val_extra, 1, (void*)g_tree_val[1]);
	else if (variant == 2) // target holds no value of the fixture
		target = c_treenew(any)((void*)g_tree_val_extra);
	result = (has_only
		? c_treehasonly(any)(tree, target)
		: c_treehas(any)(tree, target));
	c_treefree(any)(target);
	c_treefree(any)(tree);
	return (result);
}
void	print_test_treehas(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_uint variant,
		t_bool has_only)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_treehas, variant, has_only)
	TEST_PRINT(bool,	treehas, "tree=(fixture), target=(variant %u)%s", variant, (has_only ? " [HasOnly]" : ""))
}
void	test_treehas(void)
{
//	| TEST FUNCTION    | TEST NAME                 |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treehas("treehas (all values)    ",	FALSE,	TRUE,       0, FALSE);
	print_test_treehas("treehas (some values)   ",	FALSE,	TRUE,       1, FALSE);
	print_test_treehas("treehas (no values)     ",	FALSE,	FALSE,      2, FALSE);
}
void	test_treehasonly(void)
{
//	| TEST FUNCTION    | TEST NAME                  |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treehas("treehasonly (all values) ",	FALSE,	TRUE,       0, TRUE);
	print_test_treehas("treehasonly (some values)",	FALSE,	FALSE,      1, TRUE);
	print_test_treehas("treehasonly (no values)  ",	FALSE,	FALSE,      2, TRUE);
}
#endif



#ifndef c_treeequ
void test_treeequ(void)	{}
#warning "treeequ() test suite function defined, but the function isn't defined."
#else
static s_tree(any)*	gen_treeequ_build(t_uint variant)
{
	s_tree(any)*	tree = NULL;
	s_tree(any)*	node;
	if (variant == 0) // identical to the fixture
		tree = gen_tree_fixture();
	else if (variant == 1) // one differing value, deep in the tree
	{
		tree = gen_tree_fixture();
		node = c_treeget(any)(c_treeget(any)(tree, 1), 0);
		node->value = (void*)g_tree_val_extra;
	}
	else if (variant == 2) // different structure (missing the deep leaf)
	{
		tree = gen_tree_fixture();
		c_treeremoveat(any)(c_treeget(any)(tree, 1), 0);
	}
	else if (variant == 3) // same values, but the sub-nodes are in a different order
	{
		tree = c_treenew(any)((void*)g_tree_val[0]);
		node = c_treeappend(any)(tree, c_treeitem(any)((void*)g_tree_val[2]));
		c_treeappend(any)(node, c_treeitem(any)((void*)g_tree_val[3]));
		c_treeappend(any)(tree, c_treeitem(any)((void*)g_tree_val[1]));
	}
	return (tree);
}
static t_bool	c_gen_treeequ(t_uint variant)
{
	s_tree(any)*	tree1 = gen_tree_fixture();
	s_tree(any)*	tree2;
	t_bool	result;
	if (variant == 9) // compare with itself (same pointer)
	{
		result = c_treeequ(any)(tree1, tree1);
		c_treefree(any)(tree1);
		return (result);
	}
	tree2 = gen_treeequ_build(variant);
	result = c_treeequ(any)(tree1, tree2);
	c_treefree(any)(tree2);
	c_treefree(any)(tree1);
	return (result);
}
void	print_test_treeequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_uint variant)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_treeequ, variant)
	TEST_PRINT(bool,	treeequ, "tree1=(fixture), tree2=(variant %u)", variant)
}
void	test_treeequ(void)
{
//	| TEST FUNCTION    | TEST NAME                     |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treeequ("treeequ (identical)         ",	FALSE,	TRUE,       0);
	print_test_treeequ("treeequ (differing value)   ",	FALSE,	FALSE,      1);
	print_test_treeequ("treeequ (differing shape)   ",	FALSE,	FALSE,      2);
	print_test_treeequ("treeequ (different order)   ",	FALSE,	FALSE,      3);
	print_test_treeequ("treeequ (same pointer)      ",	FALSE,	TRUE,       9);
}
#endif



#ifndef c_treeequn
void test_treeequn(void)	{}
#warning "treeequn() test suite function defined, but the function isn't defined."
#else
static t_bool	c_gen_treeequn(t_size depth, t_bool differ_at_root)
{
	s_tree(any)*	tree1 = gen_tree_fixture();
	s_tree(any)*	tree2 = gen_tree_fixture();
	t_bool	result;
	if (differ_at_root)
		tree2->value = (void*)g_tree_val_extra;
	else // the two trees differ only at depth 3 (the deep "shindeiru." leaf value)
		c_treeget(any)(c_treeget(any)(tree2, 1), 0)->value = (void*)g_tree_val_extra;
	result = c_treeequn(any)(tree1, tree2, depth);
	c_treefree(any)(tree2);
	c_treefree(any)(tree1);
	return (result);
}
void	print_test_treeequn(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_size depth,
		t_bool differ_at_root)
{
	TEST_INIT(bool)
	TEST_PERFORM(gen_treeequn, depth, differ_at_root)
	TEST_PRINT(bool,	treeequn, "trees=(differ at depth %s), depth=" SF_SIZE, (differ_at_root ? "1" : "3"), depth)
}
void	test_treeequn(void)
{
//	| TEST FUNCTION     | TEST NAME                     |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treeequn("treeequn (depth 0)          ",	FALSE,	TRUE,       0, FALSE);
	print_test_treeequn("treeequn (depth 1)          ",	FALSE,	TRUE,       1, FALSE);
	print_test_treeequn("treeequn (depth 2)          ",	FALSE,	TRUE,       2, FALSE);
	print_test_treeequn("treeequn (depth 3)          ",	FALSE,	FALSE,      3, FALSE);
	print_test_treeequn("treeequn (root, depth 1)    ",	FALSE,	FALSE,      1, TRUE);
	print_test_treeequn("treeequn (root, depth 0)    ",	FALSE,	TRUE,       0, TRUE);
}
#endif



/*============================================================================*\
||                        Tree: functional operations                         ||
\*============================================================================*/

#ifndef c_treeiter
void test_treeiter(void)	{}
#warning "treeiter() test suite function defined, but the function isn't defined."
#else
static char	g_treeiter_accumulator[128];
static void	gen_treeiter_visit(s_tree(any)* node)
{
	size_t	length = strlen(g_treeiter_accumulator);
	snprintf(g_treeiter_accumulator + length, sizeof(g_treeiter_accumulator) - length,
		"[%s]", (char const*)node->value);
}
static char*	c_gen_treeiter(void)
{
	s_tree(any)*	tree = gen_tree_fixture();
	g_treeiter_accumulator[0] = '\0';
	c_treeiter(any)(tree, gen_treeiter_visit);
	c_treefree(any)(tree);
	return (strdup(g_treeiter_accumulator));
}
void	print_test_treeiter(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treeiter)
	TEST_PRINT(str,	treeiter, "tree=(fixture), f=(accumulates values in visit order)")
	TEST_FREE()
}
void	test_treeiter(void)
{
	// the tree must be visited in depth-first pre-order (a node before its sub-nodes)
//	| TEST FUNCTION     | TEST NAME       |TESTFLAG| EXPECTING
	print_test_treeiter("treeiter       ",	FALSE,	"[Omae][ wa ][mou ][shindeiru.]");
}
#endif



#ifndef c_treediter
void test_treediter(void)	{}
#warning "treediter() test suite function defined, but the function isn't defined."
#else
static char	g_treediter_accumulator[128];
static void	gen_treediter_visit(s_tree(any)* node, t_size depth)
{
	size_t	length = strlen(g_treediter_accumulator);
	snprintf(g_treediter_accumulator + length, sizeof(g_treediter_accumulator) - length,
		"[%u:%s]", (unsigned)depth, (char const*)node->value);
}
static char*	c_gen_treediter(void)
{
	s_tree(any)*	tree = gen_tree_fixture();
	g_treediter_accumulator[0] = '\0';
	c_treediter(any)(tree, gen_treediter_visit);
	c_treefree(any)(tree);
	return (strdup(g_treediter_accumulator));
}
void	print_test_treediter(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treediter)
	TEST_PRINT(str,	treediter, "tree=(fixture), f=(accumulates values with depths)")
	TEST_FREE()
}
void	test_treediter(void)
{
	// the given node itself is visited with a depth of 0, its direct sub-nodes with 1, and so on
//	| TEST FUNCTION      | TEST NAME        |TESTFLAG| EXPECTING
	print_test_treediter("treediter       ",	FALSE,	"[0:Omae][1: wa ][1:mou ][2:shindeiru.]");
}
#endif



#ifndef c_treemap
void test_treemap(void)	{}
#warning "treemap() test suite function defined, but the function isn't defined."
#else
static void*	gen_treemap_swap(void* value)
{	// maps values "Omae"<->"shindeiru." and " wa "<->"mou " (reverses the value assignment)
	for (t_uint i = 0; i < 4; ++i)
	{
		if (value == (void*)g_tree_val[i])
			return ((void*)g_tree_val[3 - i]);
	}
	return (value);
}
static char*	c_gen_treemap(void)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	result = c_treemap(any)(tree, gen_treemap_swap);
	c_treefree(any)(tree); // the mapped tree (a deep copy) must survive its source being freed
	return (gen_tree_consume(result));
}
void	print_test_treemap(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treemap)
	TEST_PRINT(str,	treemap, "tree=(fixture), map=(reverses values)")
	TEST_FREE()
}
void	test_treemap(void)
{
//	| TEST FUNCTION    | TEST NAME      |TESTFLAG| EXPECTING
	print_test_treemap("treemap       ",	FALSE,	"(shindeiru. (mou ) ( wa  (Omae)))");
}
#endif



#ifndef c_treefilter
void test_treefilter(void)	{}
#warning "treefilter() test suite function defined, but the function isn't defined."
#else
static t_bool	gen_treefilter_not_mou(void* value)
{
	return (value != (void*)g_tree_val[2]); // filters out the "mou " node (pruning its subtree)
}
static t_bool	gen_treefilter_not_root(void* value)
{
	return (value != (void*)g_tree_val[0]); // filters out the root node itself
}
static t_bool	gen_treefilter_all(void* value)
{
	(void)value;
	return (TRUE);
}
static char*	c_gen_treefilter(t_uint variant)
{
	s_tree(any)*	tree = gen_tree_fixture();
	s_tree(any)*	result = c_treefilter(any)(tree,
		(variant == 0 ? gen_treefilter_all :
		(variant == 1 ? gen_treefilter_not_mou : gen_treefilter_not_root)));
	c_treefree(any)(tree); // the filtered tree (a deep copy) must survive its source being freed
	return (gen_tree_consume(result));
}
void	print_test_treefilter(char const* test_name, t_testflags flags,
		char const* expecting,
		t_uint variant)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_treefilter, variant)
	TEST_PRINT(str,	treefilter, "tree=(fixture), filter=(variant %u)", variant)
	TEST_FREE()
}
void	test_treefilter(void)
{
//	| TEST FUNCTION       | TEST NAME                  |TESTFLAG| EXPECTING            | TEST ARGS
	print_test_treefilter("treefilter (keep all)    ",	FALSE,	GEN_TREE_FIXTURE_STR,  0);
	print_test_treefilter("treefilter (prune branch)",	FALSE,	"(Omae ( wa ))",       1);
	print_test_treefilter("treefilter (prune root)  ",	FALSE,	"(null)",              2);
}
#endif



#ifndef c_treereduce
void test_treereduce(void)	{}
#warning "treereduce() test suite function defined, but the function isn't defined."
#else
static void*	gen_treereduce_sum_value_lengths(s_tree(any) const* node, void* acc)
{	// accumulates the total length of every value string (in a uintptr accumulator)
	return ((void*)((t_uintptr)acc + strlen((char const*)node->value)));
}
static t_uint	c_gen_treereduce(t_bool fold, t_uint initial)
{
	s_tree(any)*	tree = gen_tree_fixture();
	void*	result;
	if (fold)
		result = c_treefold(any)(tree, gen_treereduce_sum_value_lengths, (void*)(t_uintptr)initial);
	else
		result = c_treereduce(any)(tree, gen_treereduce_sum_value_lengths);
	c_treefree(any)(tree);
	return ((t_uint)(t_uintptr)result);
}
void	print_test_treereduce(char const* test_name, t_testflags flags,
		t_uint expecting,
		t_bool fold,
		t_uint initial)
{
	TEST_INIT(uint)
	TEST_PERFORM(gen_treereduce, fold, initial)
	TEST_PRINT(uint,	treereduce, "tree=(fixture), f=(sums value lengths)%s", (fold ? ", with initial value" : ""))
}
void	test_treereduce(void)
{
	// the fixture value lengths are: "Omae"=4, " wa "=4, "mou "=4, "shindeiru."=10 (total: 22)
//	| TEST FUNCTION       | TEST NAME         |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treereduce("treereduce       ",	FALSE,	22,         FALSE, 0);
}
void	test_treefold(void)
{
//	| TEST FUNCTION       | TEST NAME         |TESTFLAG| EXPECTING | TEST ARGS
	print_test_treereduce("treefold         ",	FALSE,	122,        TRUE,  100);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_generic_tree(void)
{
	print_suite_title("libccc/generic/tree");

	test_treeitem();
	test_treenew();
	test_treecreate();
	test_treedup();
	test_treeclear();
	test_treefclear();
	test_treefdel();

	test_treeget();
	test_treeset();

	test_treeappend();
	test_treeprepend();
	test_treeinsert();
	test_treeremoveat();
	test_treefremoveat();
	test_treeremove();
	test_treeremall();
	test_treefremall();

	test_treesize();
	test_treedepth();
	test_treefind();
	test_treeffind();
	test_treecount();
	test_treecontains();
	test_treehas();
	test_treehasonly();
	test_treeequ();
	test_treeequn();

	test_treeiter();
	test_treediter();
	test_treemap();
	test_treefilter();
	test_treereduce();
	test_treefold();

	return (OK);
}
