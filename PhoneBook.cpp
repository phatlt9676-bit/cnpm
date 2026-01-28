#include "PhoneBook.h"
#include <fstream>
#include <algorithm>

/* ===== CONTACT ===== */
Contact::Contact() {}

Contact::Contact(string name, string phone, string email)
    : name(name), phone(phone), email(email) {}

string Contact::getName() const { return name; }
string Contact::getPhone() const { return phone; }
string Contact::getEmail() const { return email; }

void Contact::setName(string name) { this->name = name; }
void Contact::setPhone(string phone) { this->phone = phone; }
void Contact::setEmail(string email) { this->email = email; }

void Contact::display() const {
    cout << "Name: " << name
         << " | Phone: " << phone
         << " | Email: " << email << endl;
}

/* ===== CONTACT GROUP ===== */
ContactGroup::ContactGroup() {}

ContactGroup::ContactGroup(string name) : groupName(name) {}

string ContactGroup::getGroupName() const {
    return groupName;
}

vector<int>& ContactGroup::getContacts() {
    return contactIndexes;
}

void ContactGroup::addContact(int index) {
    contactIndexes.push_back(index);
}

void ContactGroup::removeContact(int index) {
    contactIndexes.erase(
        remove(contactIndexes.begin(), contactIndexes.end(), index),
        contactIndexes.end()
    );
}

void ContactGroup::display(const vector<Contact>& contacts) const {
    cout << "Group: " << groupName << endl;
    for (int idx : contactIndexes) {
        if (idx >= 0 && idx < contacts.size()) {
            contacts[idx].display();
        }
    }
}

/* ===== PHONEBOOK ===== */
void PhoneBook::addContact() {
    string name, phone, email;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter phone: ";
    getline(cin, phone);
    cout << "Enter email: ";
    getline(cin, email);

    contacts.push_back(Contact(name, phone, email));
    cout << "Contact added successfully!\n";
}

void PhoneBook::viewContacts() const {
    if (contacts.empty()) {
        cout << "No contacts available!\n";
        return;
    }
    for (int i = 0; i < contacts.size(); i++) {
        cout << "[" << i << "] ";
        contacts[i].display();
    }
}

void PhoneBook::editContact() {
    viewContacts();
    int index;
    cout << "Choose contact index: ";
    cin >> index;

    if (index < 0 || index >= contacts.size()) return;

    cin.ignore();
    string name, phone, email;
    cout << "New name: ";
    getline(cin, name);
    cout << "New phone: ";
    getline(cin, phone);
    cout << "New email: ";
    getline(cin, email);

    contacts[index].setName(name);
    contacts[index].setPhone(phone);
    contacts[index].setEmail(email);
}

void PhoneBook::deleteContact() {
    viewContacts();
    int index;
    cout << "Choose contact index to delete: ";
    cin >> index;

    if (index < 0 || index >= contacts.size()) return;
    contacts.erase(contacts.begin() + index);
    cout << "Contact deleted!\n";
}

void PhoneBook::searchContact() const {
    cin.ignore();
    string key;
    cout << "Enter keyword: ";
    getline(cin, key);

    for (const auto& c : contacts) {
        if (c.getName().find(key) != string::npos ||
            c.getPhone().find(key) != string::npos) {
            c.display();
        }
    }
}

/* ===== GROUP ===== */
void PhoneBook::addGroup() {
    cin.ignore();
    string name;
    cout << "Enter group name: ";
    getline(cin, name);
    groups.push_back(ContactGroup(name));
}

void PhoneBook::viewGroups() const {
    for (int i = 0; i < groups.size(); i++) {
        cout << "[" << i << "] " << groups[i].getGroupName() << endl;
    }
}

void PhoneBook::assignContactToGroup() {
    viewContacts();
    int cIdx;
    cout << "Choose contact index: ";
    cin >> cIdx;

    viewGroups();
    int gIdx;
    cout << "Choose group index: ";
    cin >> gIdx;

    if (cIdx >= 0 && cIdx < contacts.size() &&
        gIdx >= 0 && gIdx < groups.size()) {
        groups[gIdx].addContact(cIdx);
    }
}

void PhoneBook::viewContactsByGroup() const {
    viewGroups();
    int index;
    cout << "Choose group index: ";
    cin >> index;

    if (index >= 0 && index < groups.size()) {
        groups[index].display(contacts);
    }
}

/* ===== FILE ===== */
void PhoneBook::saveToFile(const string& filename) const {
    ofstream file(filename);
    file << contacts.size() << endl;
    for (const auto& c : contacts) {
        file << c.getName() << endl
             << c.getPhone() << endl
             << c.getEmail() << endl;
    }
    file.close();
}

void PhoneBook::loadFromFile(const string& filename) {
    ifstream file(filename);
    int n;
    file >> n;
    file.ignore();

    contacts.clear();
    for (int i = 0; i < n; i++) {
        string name, phone, email;
        getline(file, name);
        getline(file, phone);
        getline(file, email);
        contacts.push_back(Contact(name, phone, email));
    }
    file.close();
}
