#pragma once

#include <string>
#include <vector>

#include "Contact.h"

namespace address_book
{
	class ContactFile
	{
	public:
		ContactFile(const std::string& contact_file_name);

		void add_contact_to_file(const Contact& contact) const;
		std::vector<Contact> read_contacts_from_file(int user_id);
		void update_contact_in_file(const Contact& contact) const;
		void delete_contact_from_file(const Contact& contact);

		constexpr int get_last_contact_id() const noexcept;
		constexpr void set_last_contact_id(int contact_id) noexcept;

	private:
		std::string _contact_file_name;
		int _last_contact_id{};
	};

    constexpr int ContactFile::get_last_contact_id() const noexcept
    {
        return _last_contact_id;
    }

    constexpr void ContactFile::set_last_contact_id(int contact_id) noexcept
    {
        _last_contact_id = contact_id;
    }
}