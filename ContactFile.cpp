#include "ContactFile.h"

#include <cstddef>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "Contact.h"
#include "User.h"
#include "UserManager.h"
#include "Utils.h"

namespace
{
    address_book::Contact to_contact(const std::string& pipe_separated_contact_data)
    {
        address_book::Contact contact;
        std::string single_user_data;
        int single_data_number{};

        for (size_t pos{}; pos < pipe_separated_contact_data.length(); ++pos)
        {
            if (pipe_separated_contact_data[pos] != '|')
            {
                single_user_data += pipe_separated_contact_data[pos];
            }
            else
            {
                switch (single_data_number)
                {
                case 0:
                    contact.set_id(std::atoi(single_user_data.c_str()));
                    break;
                case 1:
                    contact.set_user_id(atoi(single_user_data.c_str()));
                    break;
                case 2:
                    contact.set_name(single_user_data);
                    break;
                case 3:
                    contact.set_surname(single_user_data);
                    break;
                case 4:
                    contact.set_phone_number(single_user_data);
                    break;
                case 5:
                    contact.set_email(single_user_data);
                    break;
                case 6:
                    contact.set_address(single_user_data);
                    break;
                default:
                    break;
                }

                single_user_data.clear();
                ++single_data_number;
            }
        }

        return contact;
    }

    std::string to_string(address_book::Contact contact)
    {
        std::string line;
        line += std::to_string(contact.get_id()) + '|';
        line += std::to_string(contact.get_user_id()) + '|';
        line += contact.get_name() + '|';
        line += contact.get_surname() + '|';
        line += contact.get_phone_number() + '|';
        line += contact.get_email() + '|';
        line += contact.get_address() + '|';

        return line;
    }
}

namespace address_book
{
    ContactFile::ContactFile(const std::string& contact_file_name) :
        _contact_file_name{contact_file_name}
    {
    }

    void ContactFile::add_contact_to_file(const Contact& contact) const
    {
        std::ofstream text_file{_contact_file_name, std::ios::app};

        if (text_file.good())
        {
            text_file << to_string(contact) << std::endl;
        }
    }

    std::vector<Contact> ContactFile::read_contacts_from_file(int user_id)
    {
        std::ifstream text_file{_contact_file_name};

        std::vector<Contact> contacts;

        if (text_file.good())
        {
            std::string pipe_separated_contact_data;

            while (std::getline(text_file, pipe_separated_contact_data))
            {
                Contact contact{to_contact(pipe_separated_contact_data)};

                if (contact.get_user_id() == user_id)
                {
                    contacts.push_back(contact);
                }

                _last_contact_id = contact.get_id();
            }
        }

        return contacts;
    }

    void ContactFile::update_contact_in_file(const Contact& contact) const
    {
        static constexpr auto TemporaryFileName{"tmp_file.txt"};

        std::fstream text_file{_contact_file_name, std::fstream::in};
        std::fstream tmp_file{TemporaryFileName, std::fstream::out};

        if (text_file.good() && tmp_file.good())
        {
            std::string pipe_separated_contact_data;

            if (text_file.good())
            {
                while (std::getline(text_file, pipe_separated_contact_data))
                {
                    if (to_contact(pipe_separated_contact_data).get_id() != contact.get_id())
                    { 
                        tmp_file << pipe_separated_contact_data << std::endl;
                    }
                    else
                    {
                        tmp_file << to_string(contact) << std::endl;
                    }
                }
            }
        }

        text_file.close();
        tmp_file.close();

        text_file = std::fstream{_contact_file_name, std::fstream::out};
        tmp_file = std::fstream{TemporaryFileName, std::fstream::in};

        text_file << tmp_file.rdbuf();

        tmp_file.close();

        if (std::filesystem::exists(TemporaryFileName))
        {
            std::filesystem::remove(TemporaryFileName);
        }
    }

    void ContactFile::delete_contact_from_file(const Contact& contact)
    {
        static constexpr auto TemporaryFileName{"tmp_file.txt"};

        std::fstream text_file{_contact_file_name, std::fstream::in};
        std::fstream tmp_file{TemporaryFileName, std::fstream::out};

        if (text_file.good() && tmp_file.good())
        {
            std::string pipe_separated_contact_data;

            Contact last_contact;

            if (text_file.good())
            {
                while (std::getline(text_file, pipe_separated_contact_data))
                {
                    last_contact = to_contact(pipe_separated_contact_data); 

                    if (last_contact.get_id() != contact.get_id())
                    {
                        tmp_file << pipe_separated_contact_data << std::endl;
                    }
                }
            }

            if (last_contact.get_id() == contact.get_id())
            {
                set_last_contact_id(contact.get_id() - 1);
            }
        }

        text_file.close();
        tmp_file.close();

        text_file = std::fstream{_contact_file_name, std::fstream::out};
        tmp_file = std::fstream{TemporaryFileName, std::fstream::in};

        text_file << tmp_file.rdbuf();

        tmp_file.close();

        if (std::filesystem::exists(TemporaryFileName))
        {
            std::filesystem::remove(TemporaryFileName);
        }
    }
}
