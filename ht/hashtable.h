#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <memory>
#include <random>
#include <ctime>


namespace hsbrdg
{
	template<typename T, typename U>
	class User
	{
	private:
		T _login{};
		U _password{};
		User* _next{};

	public:
		template<typename T, typename U>
		friend std::istream& operator>>(std::istream& in, User<T, U>& _user);

		User(const T& login, const U& password)
			:
			_login(login), _password(password), _next(NULL)
		{}


		User() = default;
		~User() = default;

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

		void setPassword(U password)
		{
			_password = password;
		}

		User* getNext() const
		{
			return _next;
		}

		void setNext(User* next)
		{
			_next = next;
		}
	};

	template<typename T, typename U, uint8_t tableSize>
	class Hashtable 
	{
	private:
		User<T, U>* ht[tableSize];

	public:
		template<typename T, typename U, uint8_t tableSize>
		friend std::ostream& operator<<(std::ostream& in, const Hashtable<T, U, tableSize>& _hashtable);

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
			User<T, U>* entry = ht[hashVal];
			User<T, U>* prev = NULL;

			while (entry != NULL)
			{
				prev = entry;
				entry = entry->getNext();
			}

			if (prev == NULL)
			{
				entry = new User<T, U>(login, password);
				ht[hashVal] = entry;
			}
			else
			{
				entry = new User<T, U>(login, password);
				prev->setNext(entry);
			}
		}

		void remove(const T& login, const U& password)
		{
			bool isRemoved = false;

			User<T, U>* tmp = NULL;
			User<T, U>* prev = NULL;

			for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
			{
				if (isRemoved == true)
				{
					break;
				}

				if (ht[bucket] == NULL)
				{
					continue;
				}
				else
				{
					isRemoved = false;

					tmp = ht[bucket];

					while (tmp->getLogin() != login && tmp->getNext() != NULL)
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
						if (tmp->getLogin() == login && tmp->getPassword() == password)
						{
							prev->setNext(tmp->getNext());
							delete tmp;
							isRemoved = true;
						}
					}
				}

				if (isRemoved == false)
				{
					bool isSameLogins = false;
					std::vector<User<T, U>*> sameLogins;

					for (auto i = ht[bucket]; i != NULL; i = i->getNext())
					{
						if (i->getLogin() == login && i->getPassword() == password)
						{
							sameLogins.push_back(i);
							isSameLogins = true;
						}
					}

					if (isSameLogins == true)
					{
						User<T, U>* entity = ht[bucket];
						User<T, U>* prevEntity = NULL;

						while (entity->getPassword() != sameLogins[0]->getPassword())
						{
							prevEntity = entity;
							entity = entity->getNext();
						}
						if (prevEntity == NULL)
						{
							ht[bucket] = entity->getNext();
							delete entity;
						}
						else
						{
							prevEntity->setNext(entity->getNext());
							delete entity;
						}
					}
				}
			}
		}

		User<T, U>* get(const T& login, const U& password) const
		{
			bool isFounded = false;

			User<T, U>* tmp = NULL;
			User<T, U>* prev = NULL;

			for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
			{
				if (ht[bucket] == NULL)
				{
					continue;
				}
				else
				{
					if (isFounded == true)
					{
						break;
					}

					isFounded = false;

					tmp = ht[bucket];

					while (tmp->getLogin() != login && tmp->getNext() != NULL)
					{
						if (tmp->getPassword() == password)
						{
							break;
						}

						prev = tmp;
						tmp = tmp->getNext();
					}

					if (tmp->getLogin() == login && tmp->getPassword() == password)
					{
						isFounded = true;
						return tmp;
					}

				}

				if (isFounded == false)
				{
					for (auto i = ht[bucket]; i != NULL; i = i->getNext())
					{
						if (i->getLogin() == login && i->getPassword() == password)
						{
							return i;
						}
					}
				}
			}
		}

	
		int test_hash_func(void)
		{
			User<T, U> _user;

			std::cin >> _user;

			return static_cast<int>(hash_func(_user.getLogin())); // uint8_t doesn`t work with ASCII
		}
		
	public:
		Hashtable()
			:
			ht()
		{}

		~Hashtable()
		{
			for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
			{
				User<T, U>* entry = ht[bucket];

				while (entry != NULL)
				{
					User<T, U>* prev = entry;
					entry = entry->getNext();

					delete prev;
				}

				ht[bucket] = NULL;
			}
		}
	};

	template<typename T, typename U>
	std::istream& operator>>(std::istream& in, User<T, U>& _user)
	{
		std::cout << "login: ";
		in >> _user._login;

		std::cout << "password: ";
		in >> _user._password;

		return in;
	}

	template<typename T, typename U, uint8_t tableSize>
	std::ostream& operator<<(std::ostream& out, const Hashtable<T, U, tableSize>& _hashtable)
	{
		for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
		{
			User<T, U>* _user = _hashtable.ht[bucket];

			if (_user == NULL)
			{
				continue;
			}

			std::cout << "slot[ " << static_cast<int>(bucket) << " ] = ";

			for (;;)
			{
				out << _user->getLogin() << ' ' << _user->getPassword() << ' ';

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