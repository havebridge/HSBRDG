#include "hashtable.h"


void hsbrdg::hashtable::test_hash_func() 
{
	std::cout << static_cast<int>(hash_func(hashtable::_user.login)) << '\n';
}