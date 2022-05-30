#include "..\ht\hashtable.h"

using namespace hsbrdg;

#define TEST_PUT 1
#define TEST_REMOVE 0
#define TEST_GET 1
#define TEST_PRINT 0
#define TEST_HASH 0


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	hashtable<std::string, std::string, 100> _hashtable;

#if TEST_PUT
	_hashtable.put("daaaaaaaaaaaaaaaaaaa", "af");
	_hashtable.put("o", "meow");
	_hashtable.put("cat", "meow");
	_hashtable.put("g", "1007");
	_hashtable.put("1", "inside");
#endif

#if TEST_REMOVE
	_hashtable.remove("g", "1007");
#endif

#if TEST_PRINT
	std::cout << _hashtable;
#endif

#if TEST_GET
	user<std::string, std::string>* getTest = _hashtable.get("g", "1007");
	std::cout <<  getTest->getLogin() << ' ' << getTest->getPassword() << '\n';
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