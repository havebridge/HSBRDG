#include "hashtable.h"


void hsbrdg::hashtable::test_hash_func(void)
{
	std::cout << "\nhash test:" << '\n';
	user _user;

	get_input(_user);

	std::cout << static_cast<int>(hash_func(_user.m_login)) << '\n'; // uint8_t doesn`t work with ASCII
}

void hsbrdg::hashtable::test_insert_func(void)
{
	std::cout << "\ninsert test:" << '\n';
	insert_ht();
}

void hsbrdg::hashtable::test_delete_func(void)
{
	std::cout << "\ndelete test:" << '\n';

	std::string login;
	std::cout << "Enter user to delete: ";
	std::cin >> login;

	delete_ht(login);
}

void hsbrdg::hashtable::test_print_func(void)
{
	std::cout << "\nprint test:" << '\n';
	print_ht();
}