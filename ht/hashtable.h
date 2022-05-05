#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstdint>
#include <string>
#include <iostream>
#include <cassert>
#include <memory>

#define MAX_KEY 100

namespace hsbrdg
{
	struct user
	{
		std::string m_login{};
		std::string m_password{};
		struct user* m_next{};

	public:
		friend std::istream& operator>> (std::istream& in, user& _user);

	public:
		user() = default;

		user(std::string login, std::string password)
			:
			m_login(login),
			m_password(password)
		{
			m_next = nullptr;
		}
	};


	class hashtable 
	{
	private:
		user** ht;

	public:
		friend std::ostream& operator<< (std::ostream& out, hsbrdg::hashtable& _ht);

		//void test_hash_func(void);
		//void test_insert_func(void);
		//void test_print_func(void);

		uint8_t hash_func(std::string key);
		void insert(void);

	public:
		hashtable()
		{
			ht = (new user*[MAX_KEY]);

			for (int i = 1; i != MAX_KEY; ++i)
			{
				ht[i] = nullptr;
			}
		}

		~hashtable()
		{
			delete ht;
		}
	};

	std::istream& operator>> (std::istream& in, hsbrdg::user& _user)
	{
		std::cout << "login: ";
		in >> _user.m_login;

		std::cout << "password: ";
		in >> _user.m_password;

		return in;
	}

	std::ostream& operator<< (std::ostream& out, hsbrdg::hashtable& _ht)
	{
		for (int slot = 0; slot != MAX_KEY; ++slot)
		{
			user* tmp = _ht.ht[slot];

			if (tmp == nullptr)
			{
				continue;
			}

			for (;;)
			{
				out << tmp->m_login << ' ' << tmp->m_password;

				if (tmp->m_next == nullptr)
				{
					break;
				}

				tmp = tmp->m_next;
			}
		}

		return out;
	}
};

#endif