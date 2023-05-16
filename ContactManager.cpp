#include "ContactManager.h"

#include <string>
#include <vector>

#include "Contact.h"

namespace address_book
{
    ContactManager::ContactManager(const std::string& contact_file_name, int logged_user_id) :
        _contact_file{contact_file_name}
    {
        _contacts = _contact_file.read_contacts_from_file(logged_user_id);
    }

    void ContactManager::add_contact(const Contact& contact)
    {
        _contacts.push_back(contact);
        _contact_file.add_contact_to_file(contact);
        _contact_file.set_last_contact_id(contact.get_id());
    }

    void ContactManager::update_contact_in_file(const Contact& edited_contact)
    {
        _contact_file.update_contact_in_file(edited_contact);
    }

    void ContactManager::delete_contact_from_file(const Contact& deleted_contact)
    {
        _contact_file.delete_contact_from_file(deleted_contact);
    }
}