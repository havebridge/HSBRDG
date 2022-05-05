#include "hashtable.h"

void hsbrdg::hashtable::get_input(hsbrdg::user& _user)
{
	std::cout << "login: ";
	std::cin >> _user.m_login;

	std::cout << "password: ";
	std::cin >> _user.m_password;
}

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
	user data;
	
	get_input(data);

	uint8_t slot = hash_func(data.m_login);

	if (ht[slot] == nullptr)
	{
		ht[slot]->m_login = data.m_login;
		ht[slot]->m_password = data.m_password;
		ht[slot]->m_next = nullptr;

		return;
	}

	user* tmp = ht[slot];
	user* prev = (new user[sizeof(user)]);

	while (tmp->m_next != nullptr)
	{
		prev = tmp;
		tmp = prev->m_next;
	}

	ht[slot] = prev;
	ht[slot]->m_next->m_login = data.m_login;
	ht[slot]->m_next->m_password = data.m_password;
	ht[slot]->m_next->m_next = nullptr;
}

void hsbrdg::hashtable::print_ht(void)
{
	for (int slot = 0; slot != MAX_KEY; ++slot)
	{
		user* tmp = ht[slot];

		if (tmp == nullptr)
		{
			continue;
		}

		for (;;)
		{
			std::cout << tmp->m_login << ' ' << tmp->m_password << '\n';

			if (tmp->m_next == nullptr)
			{
				break;
			}

			tmp = tmp->m_next;
		}
	}
}