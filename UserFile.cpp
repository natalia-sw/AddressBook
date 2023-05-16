#include "UserFile.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "User.h"
#include "Utils.h"

namespace
{
    address_book::User to_user(const std::string& pipe_separated_user_data)
    {
        address_book::User user;
        std::string user_data_entry;
        int single_data_number{};

        for (size_t pos{}; pos < pipe_separated_user_data.length(); ++pos)
        {
            if (pipe_separated_user_data[pos] != '|')
            {
                user_data_entry += pipe_separated_user_data[pos];
            }
            else
            {
                switch (single_data_number)
                {
                case 0:
                    user.set_id(std::atoi(user_data_entry.c_str()));
                    break;
                case 1:
                    user.set_login(user_data_entry);
                    break;
                case 2:
                    user.set_password(user_data_entry);
                    break;
                default:
                    break;
                }

                user_data_entry.clear();
                ++single_data_number;
            }
        }

        return user;
    }

    std::string to_string(const address_book::User& user)
    {
        std::string line;
        line += std::to_string(user.get_id()) + '|';
        line += user.get_login() + '|';
        line += user.get_password() + '|';

        return line;
    }
}

namespace address_book
{
    UserFile::UserFile(const std::string& user_file_name) :
        _user_file_name{user_file_name}
    {
    }

    void UserFile::add_user_to_file(const User& user) const 
    {
        std::ofstream text_file{_user_file_name, std::ofstream::app};

        if (text_file.good())
        {
            text_file << to_string(user) << std::endl;
        }
    }

    std::vector<User> UserFile::read_users_from_file() const
    {
        std::vector<User> users;

        std::ifstream text_file{_user_file_name};

        if (text_file.good())
        {
            std::string pipe_separated_user_data;

            while (std::getline(text_file, pipe_separated_user_data))
            {
                users.push_back(to_user(pipe_separated_user_data));
            }
        }

        return users;
    }

    void UserFile::update_user_in_file(const User& user) const
    {
        static constexpr auto TemporaryFileName{"tmp_file.txt"};

        std::fstream text_file{_user_file_name, std::fstream::in};
        std::fstream tmp_file{TemporaryFileName, std::fstream::out};

        if (text_file.good() && tmp_file.good())
        {
            std::string pipe_separated_user_data;

            if (text_file.good())
            {
                while (std::getline(text_file, pipe_separated_user_data))
                {
                    if (to_user(pipe_separated_user_data).get_id() != user.get_id())
                    {
                        tmp_file << pipe_separated_user_data << std::endl;
                    }
                    else
                    {
                        tmp_file << to_string(user);
                    }
                }
            }
        }

        text_file.close();
        tmp_file.close();
    
        text_file = std::fstream{_user_file_name, std::fstream::out};
        tmp_file = std::fstream{TemporaryFileName, std::fstream::in};

        text_file << tmp_file.rdbuf();
 
        tmp_file.close();

        if (std::filesystem::exists(TemporaryFileName))
        {
            std::filesystem::remove(TemporaryFileName);
        }
    }
}