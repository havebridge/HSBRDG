#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstdint>
#include <string>
#include <iostream>
#include <memory>

#if 0
#define MAX_KEY 5
#endif // DEBUG

#if 1
#define MAX_KEY 100
#endif

namespace hsbrdg
{
	struct user
	{
		std::string m_login{};
		std::string m_password{};
		struct user* m_next{};

	public:
		user() = default;
		~user() = default;
	};


	class hashtable 
	{
	private:
		user* ht[MAX_KEY];

	public:
		void test_hash_func(void);
		void test_insert_func(void);
		void test_delete_func(void);
		void test_print_func(void);

		void get_input(user&);
		uint8_t hash_func(std::string login);
		void insert_ht(void);
		void delete_ht(std::string login);
		void print_ht(void);

	public:
		hashtable()
		{
			for (int slot = 0; slot != MAX_KEY; ++slot)
			{
				ht[slot] = new user;
				ht[slot]->m_login = "";
				ht[slot]->m_password = "";
				ht[slot]->m_next = nullptr;
			}
		}

		~hashtable()
		{
			for (int slot = 0; slot != MAX_KEY; ++slot)
			{
				delete ht[slot];
			}
		}
	};
};

#endif