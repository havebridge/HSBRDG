#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#define MAX_KEY 100

namespace hsbrdg
{
	class hashtable 
	{
	private:
		struct user
		{
			std::string m_login{};
			std::string m_password{};
			struct user* m_next{};

			user(std::string login, std::string password)
				: 
				m_login(login),
				m_password(password)
			{}
		};

		user _user;

		uint8_t current_size_ht{ 0 };
		static constexpr uint8_t max_size_ht{ MAX_KEY };

		std::vector<user*> ht;

	public:
		void test_hash_func(void);

	
		user input_user_data(void);

		uint8_t hash_func(std::string key);
		void insert(std::string login, std::string password);

	public:
		hashtable(std::string login, std::string password)
			:
			_user(login, password)
		{
			ht.reserve(MAX_KEY);


		}
			
		~hashtable() = default;
	};
};

#endif