#include "..\ht\hashtable.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	hsbrdg::hashtable user1("login");

	user1.test_hash_func();

	return 0;
}