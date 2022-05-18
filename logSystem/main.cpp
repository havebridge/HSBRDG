#include "..\ht\hashtable.h"

using namespace hsbrdg;

//#define TEST_HASH 1
#define TEST_PUT 1

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	hashtable<std::string, std::string, 1> _hashtable;

#if TEST_PUT
	_hashtable.put("login", "password111");
	_hashtable.put("name", "qwerty");
	_hashtable.put("dayn", "me");
	_hashtable.remove("name", "qwerty"); 
	_hashtable.remove("login", "password111");
	std::cout << _hashtable;
#endif

#if TEST_HASH
	std::vector<std::string> same;

	for (int i = 0; i < 5; ++i)
	{
		same.push_back(std::to_string(_hashtable.test_hash_func()));
	}

	int k = 0;
	for (int i = 1; i < 5; ++i)
	{
		k = 1;
		for (int j = 0; j < i; ++j)
		{
			if (same.at(i) == same.at(j))
			{
				k++;
			}
		}
	}
	std::cout << k << std::endl;
#endif
	
	return 0;
}