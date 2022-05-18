#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <memory>
#include <random>


namespace hsbrdg
{
	template <typename T, typename U> class user;
	template <typename T, typename U, uint8_t tableSize> class hashtable;

	template <typename T, typename U> std::istream& operator>>(std::istream& in, user<T, U>& _user);
	template <typename T, typename U, uint8_t tableSize> std::ostream& operator<<(std::ostream& out, const hashtable<T, U, tableSize>& _hashtable);


	template<typename T, typename U>
	class user
	{
	private:
		T _login{};
		U _password{};
		user* _next{};

	public:
		template<typename T, typename U>
		friend std::istream& operator>>(std::istream& in, user<T, U>& _user);

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
		template<typename T, typename U, uint8_t tableSize>
		friend std::ostream& operator<<(std::ostream& in, const hashtable<T, U, tableSize>& _hashtable);

		uint8_t hash_func(const T& login) const 
		{
			uint8_t hashValue{ 0 };
			
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);

			for (auto it = login.begin(); it != login.end(); ++it)
			{
				hashValue += sizeof(login) + dist(rng);
			}


			return hashValue % tableSize;
		}

		void put(const T& login, const U& password)
		{
			uint8_t hashVal = hash_func(login);
			user<T, U>* entry = ht[hashVal];
			user<T, U>* prev = NULL;

			while (entry != NULL)
			{
				prev = entry;
				entry = entry->getNext();
			}

			if (prev == NULL)
			{
				entry = new user<T, U>(login, password);
				ht[hashVal] = entry;
			}
			else
			{
				entry = new user<T, U>(login, password);
				prev->setNext(entry);
			}
		}

		void remove(const T& login, const U& password)
		{
			bool isRemoved = false;
			user<T, U>* tmp = NULL;
			user<T, U>* prev = NULL;

			user<T, U>* log = NULL;
			std::vector<user<T, U>*> sameLogins;
			std::vector<user<T, U>*> passwords;

			for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
			{
				isRemoved = false;

				tmp = ht[bucket];

				if (tmp == NULL)
				{
					continue;
				}
				else
				{
					while (tmp->getLogin() != login)
					{
						if (tmp->getPassword() == password)
						{
							break;
						}

						prev = tmp;
						tmp = tmp->getNext();
					}

					if (prev == NULL)
					{
						if (tmp->getLogin() == login && tmp->getPassword() == password)
						{
							ht[bucket] = tmp->getNext();
							delete tmp;
							isRemoved = true;
						}
					}
					else
					{
						prev->setNext(tmp->getNext());
						delete tmp;
						isRemoved = true;
					}
				}

				if (isRemoved == false)
				{
					log = ht[bucket];
					int count = 0;

					while (log != NULL && log->getLogin() == login)
					{
						sameLogins.push_back(log);
						log = log->getNext();
						count++;
					}

					int count1 = 0;

					for (int i = 1; i < count; ++i)
					{
						for (int j = 0; j < i; ++j)
						{
							if (sameLogins[i]->getLogin() == sameLogins[j]->getLogin())
							{
								passwords.push_back(sameLogins[i]);
								count1++;
							}
						}
					}

					user<T, U>* log1 = ht[bucket];
					user<T, U>* prevlog1 = NULL;
					while (passwords[count1]->getPassword() != password)
					{
						prevlog1 = log1;
						log1 = log1->getNext();
					}

					if (prevlog1 == NULL)
					{
						ht[bucket] = log1->getNext();
						delete log1;
					}
					else
					{
						prevlog1->setNext(log1->getNext());
						delete log1;
					}
				}
			}
		}

		user<T, U>* get(const T& login) const
		{
		}

	
		int test_hash_func(void)
		{
			user<T, U> _user;

			std::cin >> _user;

			return static_cast<int>(hash_func(_user.getLogin())); // uint8_t doesn`t work with ASCII
		}

		

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

	template<typename T, typename U>
	std::istream& operator>>(std::istream& in, user<T, U>& _user)
	{
		std::cout << "login: ";
		in >> _user._login;

		std::cout << "password: ";
		in >> _user._password;

		return in;
	}

	template<typename T, typename U, uint8_t tableSize>
	std::ostream& operator<<(std::ostream& out, const hashtable<T, U, tableSize>& _hashtable)
	{
		for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
		{
			user<T, U>* _user = _hashtable.ht[bucket];

			if (_user == NULL)
			{
				continue;
			}

			std::cout << "slot[ " << static_cast<int>(bucket) << " ] = ";

			for (;;)
			{
				out << "login: " << _user->getLogin() << ' '<< "password: " << _user->getPassword() << ' ';

				if (_user->getNext() == NULL)
				{
					break;
				}

				_user = _user->getNext();
			}
			std::cout << '\n';
		}

		return out;
	}
};