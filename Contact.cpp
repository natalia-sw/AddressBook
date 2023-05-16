#include "Contact.h"

#include <string>

namespace address_book
{
	void Contact::set_name(const std::string& name) noexcept
	{
		_name = name;
	}

	void Contact::set_surname(const std::string& surname) noexcept
	{
		_surname = surname;
	}

	void Contact::set_phone_number(const std::string& phone_number) noexcept
	{
		_phone_number = phone_number;
	}

	void Contact::set_email(const std::string& email) noexcept
	{
		_email = email;
	}

	void Contact::set_address(const std::string& address) noexcept
	{
		_address = address;
	}
}
