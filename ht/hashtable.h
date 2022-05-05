#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstdint>
#include <string>
#include <iostream>
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
		void test_hash_func(void);
		void test_insert_func(void);
		void test_print_func(void);

		void get_input(user&);
		uint8_t hash_func(std::string key);
		void insert(void);
		void print_ht(void);

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
};

#endif