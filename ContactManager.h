#pragma once

#include <string>
#include <vector>

#include "Contact.h"
#include "ContactFile.h"

namespace address_book
{
	class ContactManager
	{
	public:
		ContactManager(const std::string& contact_file_name, User::id_t logged_user_id);

		void add_contact(const Contact& contact);
		void delete_contact_from_file(const Contact& contact);
		void update_contact_in_file(const Contact& contact);

		constexpr std::vector<Contact>& get_contacts() noexcept;
		constexpr const std::vector<Contact>& get_contacts() const noexcept;
		constexpr int get_new_contact_id() const noexcept;

	private:
		ContactFile _contact_file;
		std::vector<Contact> _contacts;
	};

    constexpr std::vector<Contact>& ContactManager::get_contacts() noexcept
    {
        return _contacts;
    }

    constexpr const std::vector<Contact>& ContactManager::get_contacts() const noexcept
    {
        return _contacts;
    }

    constexpr int ContactManager::get_new_contact_id() const noexcept
    {
        return _contact_file.get_last_contact_id() + 1;
    }
}
