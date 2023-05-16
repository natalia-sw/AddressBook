#pragma once

#include <string>
#include <vector>

#include "User.h"

namespace address_book
{
	class UserFile
	{
	public:
		UserFile(const std::string& user_file_name);

		void add_user_to_file(const User& user) const;
		std::vector<User> read_users_from_file() const;
		void update_user_in_file(const User& user) const;

	private:
		std::string _user_file_name;
	};
}
