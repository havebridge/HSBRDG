#include "..\ht\hashtable.h"

using namespace hsbrdg;

//#define TEST 1

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	hashtable<std::string, std::string, 2> _hashtable;

#if TEST
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