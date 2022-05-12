#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <memory>

#if 1
#define SIZE 5
#endif // For Overloading operator<<



namespace hsbrdg
{
	template <typename T, typename U> struct user;

	template <typename T, typename U> std::istream& operator>>(std::istream& in, user<T, U>& lhs);
	template <typename T, typename U> std::ostream& operator<<(std::ostream& out, const user<T, U>& lhs);


	template<typename T, typename U>
	class user
	{
	private:
		T _login{};
		U _password{};
		user* _next{};

	public:
		template<typename U, typename T>
		friend std::istream& operator>>(std::istream& in, user<U, T>& _user);
		template<typename U, typename T>
		friend std::ostream& operator<<(std::ostream& in, const user<U, T>& _user);

		user(const T& login, const U& password)
			:
			_login(login), _password(password), _next(NULL)
		{}


		user() = default;
		~user() = default;

	public:
		T getLogin() const
		{
			return _login;
		}

		U getPassword() const
		{
			return _password;
		}

		void setLogin(T login)
		{
			_login = login;
		}

		user* getNext() const 
		{
			return _next;
		}

		void setNext(user* next)
		{
			_next = next;
		}
	};

	template<typename T, typename U, uint8_t tableSize>
	class hashtable 
	{
	private:
		user<T, U>* ht[tableSize];

	public:
		friend user;

		uint8_t hash_func(const U& login) const 
		{
			return 5;
			//return reinterpret_cast<uint8_t>(login) % tableSize;
		}

		void put(void)
		{
			
		}

		void remove(U login)
		{

		}

		user<U, T>* get(U login)
		{

		}

	
		void test_hash_func(void)
		{
			user<T, U> _user;

			std::cin >> _user;

			std::cout << static_cast<int>(hash_func(_user.getLogin())) << '\n'; // uint8_t doesn`t work with ASCII
		}

		//void test_hash_func(void);
		void test_put_func(void);
		void test_remove_func(void);

	public:
		hashtable()
			:
			ht()
		{}

		~hashtable()
		{
			for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
			{
				user<T, U>* entry = ht[bucket];

				while (entry != NULL)
				{
					user<T, U>* prev = entry;
					entry = entry->getNext();

					delete prev;
				}

				ht[bucket] = NULL;
			}
		}
	};

	template<typename T, typename U >
	std::istream& operator>>(std::istream& in, user<T, U>& _user)
	{
		std::cout << "login: ";
		in >> _user._login;

		std::cout << "password: ";
		in >> _user._password;

		return in;
	}

	template<typename T, typename U>
	std::ostream& operator<<(std::ostream& out, const user<T, U>& _user)
	{
		for (uint8_t bucket = 0; bucket != SIZE; ++bucket)
		{
			if (_user == NULL)
			{
				continue;
			}

			std::cout << "slot[ " << bucket << " ] = ";

			for (;;)
			{
				out << _user._login << ' ' << _user._password;

				if (_user._next == NULL)
				{
					break;
				}

				_user = _user.getNext();
			}
			std::cout << '\n';
		}
	}
};