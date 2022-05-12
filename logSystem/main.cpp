#include "..\ht\hashtable.h"

using namespace hsbrdg;

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	hashtable<std::string, std::string, 5> _hashtable;

	_hashtable.test_hash_func();
	

	return 0;
}