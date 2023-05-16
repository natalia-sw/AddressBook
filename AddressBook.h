#pragma once

#include <optional>
#include <string>

#include "ContactManager.h"
#include "UserManager.h"

namespace address_book
{
	class AddressBook
	{
	public:
		AddressBook(const std::string& user_file_name, const std::string& contact_file_name);

		void add_contact();
		void change_password();
		bool login_user();
		void logout_user();
		void register_user();
		void search_by_name() const;
		void search_by_surname() const;
		void delete_contact();
		void edit_contact();
		void view_all_contacts() const;

		constexpr const User* get_logged_user() const noexcept;

	private:
		std::string _contact_file_name;
		std::optional<ContactManager> _contact_manager;
		UserManager _user_manager;
	};

	constexpr const User* AddressBook::get_logged_user() const noexcept
	{
		return _user_manager.get_logged_user();
	}
}
