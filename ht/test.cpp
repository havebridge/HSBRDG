#include "hashtable.h"


void hsbrdg::hashtable::test_hash_func(void)
{
	user _user;

	hsbrdg::hashtable::get_input(_user);

	std::cout << static_cast<int>(hash_func(_user.m_login)) << '\n'; // uint8_t doesn`t work with ASCII
}

void hsbrdg::hashtable::test_insert_func(void)
{
	insert();
}

void hsbrdg::hashtable::test_print_func(void)
{
	print_ht();
}