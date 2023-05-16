#pragma once

#include <string>
#include <vector>

#include "User.h"
#include "UserFile.h"

namespace address_book
{
	class UserManager
	{
	public:
		UserManager(const std::string& user_file_name);

		void change_password(const std::string& password);
		bool login_exists(const std::string& login) const;
		bool login_user(const std::string& login, const std::string& password);
		void logout_user();
		void register_user(const User& user);

		constexpr const User* get_logged_user() const noexcept;
		int get_new_user_id() const noexcept;

	private:
		User* _logged_user{nullptr};
		UserFile _user_file;
		std::vector<User> _users;
	};

	constexpr const User* UserManager::get_logged_user() const noexcept
    {
        return _logged_user;
    }
}
