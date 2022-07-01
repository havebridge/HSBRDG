#include "..\ht\hashtable.h"

using namespace Hsbrdg;

#define TEST_PUT 1
#define TEST_REMOVE 1
#define TEST_GET 0
#define TEST_PRINT 1
#define TEST_HASH 0


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Hashtable<std::string, std::string, 100> _hashtable;

#if TEST_PUT
	const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";

	std::vector<User<std::string, std::string>> u;

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	std::string login_put;
	std::string password_put;

	for (std::size_t i = 0; i != 5; ++i)
	{
		User<std::string, std::string> _user;
		for (std::size_t j = 0; j != 4; ++j)
		{
			login_put += CHARACTERS[distribution(generator)];
			password_put += CHARACTERS[distribution(generator)];
		}
		_hashtable.put(login_put, password_put);

		_user.setLogin(login_put);
		_user.setPassword(password_put);

		u.push_back(_user);
	}
#endif

#if TEST_REMOVE
	int i = 1;
	std::cout << "Users to delete: " << '\n';
	for (auto it : u)
	{
		std::cout << i++ << ')' <<it.getLogin() << ' ' << it.getPassword() << '\n';
	}
	std::cout << std::endl;

	std::string login_remove, password_remove;
	std::cin >> login_remove >> password_remove;

	_hashtable.remove(login_remove, password_remove);
#endif

#if TEST_PRINT
	std::cout << _hashtable;
#endif

#if TEST_GET
	user<std::string, std::string>* getTest = _hashtable.get("g", "1007");
	std::cout << getTest->getLogin() << ' ' << getTest->getPassword() << '\n';
#endif

#if TEST_HASH
	std::vector<std::string> same;

	for (int i = 0; i < 5; ++i)
	{
		same.push_back(std::to_string(_hashtable.test_hash_func()));
	}

	int k = 0;
	for (int i = 1; i < 5; ++i)
	{
		k = 1;
		for (int j = 0; j < i; ++j)
		{
			if (same.at(i) == same.at(j))
			{
				k++;
			}
		}
	}
	std::cout << k << std::endl;
#endif

	return 0;
}