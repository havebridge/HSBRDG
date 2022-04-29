#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstdint>
#include <string>
#include <iostream>

#define MAX_KEY 100

namespace hsbrdg
{
	class hashtable 
	{
	private:
		struct user
		{
			std::string login{};
			std::string password{};
			struct user* next{};

			user(std::string s)
				: 
				login(s)
			{
			}
		};

		user _user;

		uint8_t size_ht{ 0 };
		static constexpr uint8_t max_size_ht{ MAX_KEY };

		user* ht[];

	public:
		void test_hash_func();
		uint8_t hash_func(std::string key);

	public:
		hashtable(std::string s)
			:
			_user(s)
		{
		}
			
		~hashtable() = default;
	};
};

#endif