#pragma once

#include <string>

namespace address_book
{
	class User
	{
	public:
		using id_t = int;

		constexpr id_t get_id() const noexcept;
		constexpr const std::string& get_login() const noexcept;
		constexpr const std::string& get_password() const noexcept;
		constexpr void set_id(id_t id) noexcept;
		void set_login(const std::string& login) noexcept;
		void set_password(const std::string& password) noexcept;

	private:
		id_t _id{};
		std::string _user_login;
		std::string _password;
	};

	constexpr User::id_t User::get_id() const noexcept
	{
		return _id;
	}

	constexpr const std::string& User::get_login() const noexcept
	{
		return _user_login;
	}

	constexpr const std::string& User::get_password() const noexcept
	{
		return _password;
	}

	constexpr void User::set_id(id_t id) noexcept
	{
		_id = id;
	}
}
