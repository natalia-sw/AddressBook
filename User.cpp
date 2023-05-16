#include "User.h"

#include <string>

namespace address_book
{
	void User::set_login(const std::string& login) noexcept
	{
		_user_login = login;
	}

	void User::set_password(const std::string& password) noexcept
	{
		_password = password;
	}
}