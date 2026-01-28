#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* ===== CLASS CONTACT ===== */
class Contact {
private:
    string name;
    string phone;
    string email;

public:
    Contact();
    Contact(string name, string phone, string email);

    string getName() const;
    string getPhone() const;
    string getEmail() const;

    void setName(string name);
    void setPhone(string phone);
    void setEmail(string email);

    void display() const;
};

/* ===== CLASS CONTACT GROUP ===== */
class ContactGroup {
private:
    string groupName;
    vector<int> contactIndexes;

public:
    ContactGroup();
    ContactGroup(string name);

    string getGroupName() const;
    vector<int>& getContacts();

    void addContact(int index);
    void removeContact(int index);
    void display(const vector<Contact>& contacts) const;
};

/* ===== CLASS PHONEBOOK ===== */
class PhoneBook {
private:
    vector<Contact> contacts;
    vector<ContactGroup> groups;

public:
    // Contact functions
    void addContact();
    void viewContacts() const;
    void editContact();
    void deleteContact();
    void searchContact() const;

    // Group functions
    void addGroup();
    void viewGroups() const;
    void assignContactToGroup();
    void viewContactsByGroup() const;

    // File functions
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif
