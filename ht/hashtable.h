#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstdint>
#include <string>
#include <iostream>
#include <cassert>

#define MAX_KEY 100

namespace hsbrdg
{
	struct user
	{
		std::string m_login{};
		std::string m_password{};
		struct user* m_next{};

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
		uint8_t current_size_ht{ 0 };
		static constexpr uint8_t max_size_ht{ MAX_KEY };

		user* ht[];

	public:
		friend std::istream& operator>> (std::istream& in, struct user& _user);

		//void test_hash_func(void);
		//void test_insert_func(void);

		uint8_t hash_func(std::string key);
		void insert(void);

	public:
		hashtable() = default;

		hashtable()
		{
			//hash table initialized to zero
		}

		~hashtable() = default;
	};

	std::istream& operator>> (std::istream& in, struct user& _user)
	{
		std::cout << "login: ";
		in >> _user.m_login;

		std::cout << "password: ";
		in >> _user.m_password;

		return in;
	}
};

#endif