#include "hashtable.h"


uint8_t hsbrdg::hashtable::hash_func(std::string key)
{
	int hash_val = 0;
	for (int i = 0; i != key.size(); ++i)
	{
		hash_val += static_cast<int>(key[i]);
	}

	return hash_val % MAX_KEY;
}