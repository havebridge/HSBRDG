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

		void setPassword(U password)
		{
			_password = password;
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
					std::vector<user<T, U>*> sameLogins;

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
						user<T, U>* entity = ht[bucket];
						user<T, U>* prevEntity = NULL;

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

		user<T, U>* get(const T& login, const U& password) const
		{
			bool isFounded = false;

			user<T, U>* tmp = NULL;
			user<T, U>* prev = NULL;

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
					bool isSameLogins = false;
					std::vector<user<T, U>*> sameLogins;

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
			user<T, U> _user;

			std::cin >> _user;

			return static_cast<int>(hash_func(_user.getLogin())); // uint8_t doesn`t work with ASCII
		}
		
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