#include "UserManager.h"

#include <string>

#include "User.h"
#include "UserFile.h"

namespace address_book
{
    UserManager::UserManager(const std::string& user_file_name) :
        _user_file{user_file_name}
    {
        _users = _user_file.read_users_from_file();
    }

    void UserManager::change_password(const std::string& password)
    {
        _logged_user->set_password(password);
        _user_file.update_user_in_file(*_logged_user);
    }

    bool UserManager::login_exists(const std::string& login) const
    {
        auto it{_users.begin()};

        while (it != _users.end())
        {
            if (it->get_login() == login)
            {
                return true;
            }

            ++it;
        }

        return false;
    }

    bool UserManager::login_user(const std::string& login, const std::string& password)
    {
        for (auto user{_users.begin()}; user != _users.end(); ++user)
        {
            if (user->get_login() == login && user->get_password() == password)
            {
                _logged_user = &*user;

                return true;
            }
        }

        return false;
    }

    void UserManager::logout_user()
    {
        _logged_user = nullptr;
    }

    void UserManager::register_user(const User& user)
    {
        _users.push_back(user);
        _user_file.add_user_to_file(user);
    }

    int UserManager::get_new_user_id() const noexcept
    {
        if (_users.empty())
        {
            return 1;
        }
        else
        {
            return _users.back().get_id() + 1;
        }
    }
}