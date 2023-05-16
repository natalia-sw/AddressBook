#include "AddressBook.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "Contact.h"
#include "User.h"
#include "Utils.h"

namespace
{
	void print_contact(const address_book::Contact& contact)
	{
		std::cout << std::endl;
		std::cout << "ID: " << contact.get_id() << std::endl;
		std::cout << "Name: " << contact.get_name() << std::endl;
		std::cout << "Surname: " << contact.get_surname() << std::endl;
		std::cout << "Phone number: " << contact.get_phone_number() << std::endl;
		std::cout << "E-mail: " << contact.get_email() << std::endl;
		std::cout << "Address: " << contact.get_address() << std::endl;
	}
}

namespace address_book
{
	AddressBook::AddressBook(const std::string& user_file_name, const std::string& contact_file_name) :
		_user_manager{user_file_name}, _contact_file_name{contact_file_name}
	{
	}

	void AddressBook::add_contact()
	{
		system("cls");

		Contact contact;
		contact.set_id(_contact_manager->get_new_contact_id());
		contact.set_user_id(_user_manager.get_logged_user()->get_id());

		std::cout << "Name: ";
		contact.set_name(utils::read_line());

		std::cout << "Surname: ";
		contact.set_surname(utils::read_line());

		std::cout << "Phone number: ";
		contact.set_phone_number(utils::read_line());

		std::cout << "E-mail: ";
		contact.set_email(utils::read_line());

		std::cout << "Address: ";
		contact.set_address(utils::read_line());

		_contact_manager->add_contact(contact);
	}

	void AddressBook::change_password()
	{
		system("cls");

		std::cout << "Please refrain from using the symbol '|' in password." << std::endl;
		std::cout << "Enter new password: ";
		std::string new_password{utils::read_line()};

		_user_manager.change_password(new_password);

		std::cout << "\033[32m" << "The password has been successfully updated." << "\033[0m" << std::endl;
		system("pause");
	}

	bool AddressBook::login_user()
	{
		std::cout << "\033[0m";
		system("cls");

		std::cout << "Login: ";
		std::string login{utils::read_line()};

		std::cout << "Password: ";
		std::string password{utils::read_line()};

		if (_user_manager.login_user(login, password))
		{
			_contact_manager.emplace(
				_contact_file_name, _user_manager.get_logged_user()->get_id()
			);

			return true;
		}
		
		std::cout << "\033[31m" << "Wrong credentials." << "\033[0m" << std::endl;		
		system("pause");

		return false;
	}

	void AddressBook::logout_user()
	{
		_user_manager.logout_user();
		_contact_manager.reset();
	}

	void AddressBook::register_user()
	{
		std::cout << "\033[0m";
		system("cls");
		std::cout << "Please refrain from using the symbol '|' in either your login or password." << std::endl;

		std::string login;

		while (true)
		{
			std::cout << "Enter login: ";
			login = utils::read_line();

			if (_user_manager.login_exists(login))
			{
				std::cout << "\033[31m" << "Sorry, the login you have selected is currently in use." << "\033[0m" << std::endl;

				continue;
			}

			break;
		}

		std::cout << "Enter password: ";
		std::string password{utils::read_line()};

		User user;
		user.set_login(login);
		user.set_password(password);
		user.set_id(_user_manager.get_new_user_id());

		_user_manager.register_user(user);
		
		std::cout << std::endl << "Your account has been created." << std::endl;		
		system("pause");
	}

	void AddressBook::search_by_name() const
	{
		std::cout << "\033[0m";
		system("cls");

		std::cout << "Enter the name of the contact you are looking for." << std::endl;
		std::string name{utils::read_line()};

		auto it{_contact_manager->get_contacts().begin()};

		for (; it != _contact_manager->get_contacts().end(); ++it)
		{
			if (it->get_name() == name)
			{
				print_contact(*it);
			}
		}

		system("pause");

		if (it == _contact_manager->get_contacts().end())
		{
			std::cout << "\033[31m" << "There is no contact by that name." << "\033[0m" << std::endl;
			system("pause");
		}
	}

	void AddressBook::search_by_surname() const
	{
		std::cout << "\033[0m";
		system("cls");

		std::cout << "Enter the surname of the contact you are looking for." << std::endl;
		std::string surname{utils::read_line()};

		auto it{_contact_manager->get_contacts().begin()};

		for (; it != _contact_manager->get_contacts().end(); ++it)
		{
			if (it->get_surname() == surname)
			{
				print_contact(*it);
				system("pause");
			}
		}

		if (it == _contact_manager->get_contacts().end())
		{
			std::cout << "\033[31m" << "There is no contact by that surname." << "\033[0m" << std::endl;
			system("pause");
		}
	}

	void AddressBook::delete_contact()
	{
		std::cout << "\033[0m";
		system("cls");

		int id;

		std::cout << "Enter number ID of the contact you want to remove from the address book." << std::endl;
		std::cin >> id;

		auto it{_contact_manager->get_contacts().begin()};

		for (; it != _contact_manager->get_contacts().end(); ++it)
		{
			if (it->get_id() == id)
			{
				break;
			}
		}

		if (it == _contact_manager->get_contacts().end())
		{
			std::cout << "\033[31m" << "The given ID number does not exist." << "\033[0m" << std::endl;
			system("pause");

			return;
		}

		print_contact(*it);

		std::cout << "Are you sure you want to delete this contact? Y/for delete N/for exit >> ";

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		char decision;

		while (true)
		{
			decision = utils::read_sign();

			switch (decision)
			{
			case 'Y':
				_contact_manager->delete_contact_from_file(*it);
				_contact_manager->get_contacts().erase(it);
				std::cout << "\033[32m" << "The contact was deleted successfully." << "\033[0m" << std::endl;
				system("pause");
				break;
			case 'N':
				return;
			}
			break;
		}
	}

	void AddressBook::edit_contact()
	{
		system("cls");

		int id;

		std::cout << "Enter number ID of the contact you want to edit." << std::endl;
		std::cin >> id;

		auto it{_contact_manager->get_contacts().begin()};

		for (; it != _contact_manager->get_contacts().end(); ++it)
		{
			if (it->get_id() == id)
			{
				break;
			}
		}

		if (it == _contact_manager->get_contacts().end())
		{
			std::cout << "\033[31m" << "The given ID number does not exist." << "\033[0m" << std::endl;
			system("pause");

			return;
		}

		if (it->get_id() == id)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			print_contact(*it);

			std::cout << "What do you want to edit?\n"
				"N for name, "
				"S for surname, "
				"P for phone number, "
				"E for e - mail, "
				"A for addres, "
				"X for exit." << std::endl;

			while (true)
			{
				char decision{utils::read_sign()};

				switch (decision)
				{
				case 'N':
					std::cout << "Name: ";
					it->set_name(utils::read_line());
					break;
				case 'S':
					std::cout << "Surname: ";
					it->set_surname(utils::read_line());
					break;
				case 'P':
					std::cout << "Phone number: ";
					it->set_phone_number(utils::read_line());
					break;
				case 'E':
					std::cout << "E-mail: ";
					it->set_email(utils::read_line());
					break;
				case 'A':
					std::cout << "Address: ";
					it->set_address(utils::read_line());
					break;
				case 'X':
					return;
				}

				_contact_manager->update_contact_in_file(*it);

				std::cout << "\033[32m" << "The contact's details have been changed correctly.\n" << "\033[0m"
					<< "Do you want edit something else ? If yes, select option again, if no, enter X for exit." << std::endl;
			}
		}	
	}

	void AddressBook::view_all_contacts() const
	{
		system("cls");
		std::cout << "\033[32;1m" << std::setw(80) << "*** YOUR ADDRESS BOOK ***" << std::endl;
		std::cout << "\033[0m";

		if (_contact_manager->get_contacts().empty())
		{
			std::cout << "\nYour address book is empty." << std::endl;
		}

		for (const auto& contact : _contact_manager->get_contacts())
		{
			print_contact(contact);
		}

		system("pause");
	}
}
