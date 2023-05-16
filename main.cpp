#include <conio.h>
#include <iomanip>
#include <iostream>
#include <string>

#include "AddressBook.h"
#include "Utils.h"

void user_menu(address_book::AddressBook& address_book)
{
	int line_number{1};

	while (true)
	{
		system("cls");
		std::cout << "Logged user: " << "\033[93m" << address_book.get_logged_user()->get_login() << "\033[31m" << std::endl;
		std::cout << std::setw(80) << "Use the up and down arrows to navigate. Enter - select an option." << std::endl;
		std::cout << std::endl;

		address_book::utils::set_color(line_number == 1); std::cout << "1. Add contact." << std::endl;
		address_book::utils::set_color(line_number == 2); std::cout << "2. Search by name." << std::endl;
		address_book::utils::set_color(line_number == 3); std::cout << "3. Search by surname." << std::endl;
		address_book::utils::set_color(line_number == 4); std::cout << "4. View all." << std::endl;
		address_book::utils::set_color(line_number == 5); std::cout << "5. Delete contact." << std::endl;
		address_book::utils::set_color(line_number == 6); std::cout << "6. Edit contact." << std::endl;
		address_book::utils::set_color(line_number == 7); std::cout << "7. Change password" << std::endl;
		address_book::utils::set_color(line_number == 8); std::cout << "8. Log out" << std::endl;
		// TODO: set_color(line_number == 9); std::cout << "9. Delete your account" << std::endl;

		std::cout << "\033[0m";

		bool selected{false};

		while (true)
		{
			int keyboard_code{_getch()};

			switch (keyboard_code)
			{
			case 72:
				line_number = std::max<int>(--line_number, 1);
				break;
			case 80:
				line_number = std::min<int>(9, ++line_number);
				break;
			case 13:
				selected = true;
				break;
			default:
				continue;
			}

			break;
		}

		if (!selected)
		{
			continue;
		}

		switch (line_number)
		{
		case 1:
			address_book.add_contact();
			break;
		case 2:
			address_book.search_by_name();
			break;
		case 3:
			address_book.search_by_surname();
			break;
		case 4:
			address_book.view_all_contacts();
			break;
		case 5:
			address_book.delete_contact();
			break;
		case 6:
			address_book.edit_contact();
			break;
		case 7:
			address_book.change_password(); 
			break;
		case 8:
			address_book.logout_user();
			return;
		}
	}
}

void login_menu(address_book::AddressBook& address_book)
{
	std::cout << "\033[0m";

	int line_number{1};

	while (true)
	{
		system("cls");

		std::cout << std::setw(80) << "Use the up and down arrows to navigate. Enter - select an option." << std::endl;
		std::cout << std::endl;
		address_book::utils::set_color(line_number == 1); std::cout << "1. Log in." << std::endl;
		address_book::utils::set_color(line_number == 2); std::cout << "2. Create an account." << std::endl;
		address_book::utils::set_color(line_number == 3); std::cout << "3. Close program." << std::endl;
		std::cout << "\033[0m";

		bool selected{false};

		while (true)
		{
			int keyboard_code{_getch()};

			switch (keyboard_code)
			{
			case 72:
				line_number = std::max<int>(--line_number, 1);
				break;
			case 80:
				line_number = std::min<int>(3, ++line_number);
				break;
			case 13:
				selected = true;
				break;
			default:
				continue;
			}

			break;
		}

		if (!selected)
		{
			continue;
		}

		switch (line_number)
		{
		case 1:
			if (address_book.login_user())
			{
				user_menu(address_book);
			}
			break;
		case 2:
			address_book.register_user();
			break;
		case 3:
			return;
		}
	}
}

int main()
{
	address_book::AddressBook address_book{"users.txt", "contacts.txt"};

	login_menu(address_book);

	return 0;
}
