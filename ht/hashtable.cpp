#include "hashtable.h"

hsbrdg::hashtable::user hsbrdg::hashtable::input_user_data(void)
{
	std::cout << "login: ";
	std::cin >> hsbrdg::hashtable::_user.m_login;

	std::cout << "\npassword: ";
	std::cin >> hsbrdg::hashtable::_user.m_password;

	return user(hsbrdg::hashtable::_user.m_login, hsbrdg::hashtable::_user.m_password);
}


uint8_t hsbrdg::hashtable::hash_func(std::string key)
{
	int hash_val = 0;
	for (int i = 0; i != key.size(); ++i)
	{
		hash_val += static_cast<int>(key[i]);
	}

	return hash_val % MAX_KEY;
}

void hsbrdg::hashtable::insert(std::string login, std::string password)
{
	uint8_t slot = hash_func(login);	
}