#include "hashtable.h"

uint8_t hsbrdg::hashtable::hash_func(std::string key)
{
	uint8_t hash_val = 0;

	for (int i = 0; i != key.size(); ++i)
	{
		hash_val += static_cast<uint8_t>(key[i]);
	}

	return hash_val % MAX_KEY;
}

void hsbrdg::hashtable::insert(void)
{
	hsbrdg::user data;
	
	std::cin >> data;

	uint8_t slot = hsbrdg::hashtable::hash_func(data.m_login);

	if (ht[slot] == nullptr)
	{
		//TODO: smart pointers
	}
}