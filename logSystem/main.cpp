#include "..\ht\hashtable.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	hsbrdg::hashtable _hashtable;

	_hashtable.test_insert_func();
	_hashtable.test_insert_func();

	_hashtable.test_print_func();

	_hashtable.test_delete_func();

	_hashtable.test_print_func();

	return 0;
}