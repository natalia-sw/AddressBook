#pragma once

#include <string>

#include "User.h"


namespace address_book
{
	class Contact
	{
	public:
		using id_t = int;

		constexpr id_t get_id() const noexcept;
		constexpr User::id_t get_user_id() const noexcept;
		constexpr const std::string& get_name() const noexcept;
		constexpr const std::string& get_surname() const noexcept;
		constexpr const std::string& get_phone_number() const noexcept;
		constexpr const std::string& get_email() const noexcept;
		constexpr const std::string& get_address() const noexcept;
		constexpr void set_id(id_t id) noexcept;
		constexpr void set_user_id(User::id_t user_id) noexcept;
		void set_name(const std::string& name) noexcept;
		void set_surname(const std::string& surname) noexcept;
		void set_phone_number(const std::string& phone_number) noexcept;
		void set_email(const std::string& email) noexcept;
		void set_address(const std::string& address) noexcept;

	private:
		id_t _id{};
		User::id_t _user_id{};
		std::string _name;
		std::string _surname;
		std::string _phone_number;
		std::string _email;
		std::string _address;
	};

	constexpr Contact::id_t Contact::get_id() const noexcept
	{
		return _id;
	}

	constexpr User::id_t Contact::get_user_id() const noexcept
	{
		return _user_id;
	}

	constexpr const std::string& Contact::get_name() const noexcept
	{
		return _name;
	}

	constexpr const std::string& Contact::get_surname() const noexcept
	{
		return _surname;
	}

	constexpr const std::string& Contact::get_phone_number() const noexcept
	{
		return _phone_number;
	}

	constexpr const std::string& Contact::get_email() const noexcept
	{
		return _email;
	}

	constexpr const std::string& Contact::get_address() const noexcept
	{
		return _address;
	}

	constexpr void Contact::set_id(id_t id) noexcept
	{
		_id = id;
	}

	constexpr void Contact::set_user_id(User::id_t user_id) noexcept
	{
		_user_id = user_id;
	}
}
