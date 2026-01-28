#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

FileManager::FileManager(const string& fname) : filename(fname) {}

bool FileManager::savePhoneBook(const PhoneBook& phoneBook) {
    ofstream file(filename.c_str());
    
    if (!file.is_open()) {
        cout << "Error: Unable to open file for saving.\n";
        return false;
    }
    
    try {
        // Save metadata
        file << "[METADATA]\n";
        file << phoneBook.getNextContactId() << "\n";
        file << phoneBook.getNextGroupId() << "\n";
        
        // Save contacts
        file << "[CONTACTS]\n";
        const map<int, Contact>& contacts = phoneBook.getAllContacts();
        map<int, Contact>::const_iterator cit;
        for (cit = contacts.begin(); cit != contacts.end(); ++cit) {
            file << cit->second.toFileString() << "\n";
        }
        
        // Save groups
        file << "[GROUPS]\n";
        const map<int, ContactGroup>& groups = phoneBook.getAllGroups();
        map<int, ContactGroup>::const_iterator git;
        for (git = groups.begin(); git != groups.end(); ++git) {
            file << git->second.toFileString() << "\n";
        }
        
        // Save mappings
        file << "[MAPPINGS]\n";
        file << phoneBook.getMapping().serialize();
        
        file.close();
        cout << "Phone book saved successfully to " << filename << "\n";
        return true;
    }
    catch (...) {
        cout << "Error saving phone book.\n";
        file.close();
        return false;
    }
}

bool FileManager::loadPhoneBook(PhoneBook& phoneBook) {
    ifstream file(filename.c_str());
    
    if (!file.is_open()) {
        cout << "Error: Unable to open file for loading.\n";
        return false;
    }
    
    try {
        phoneBook.clearAll();
        
        string line;
        string section = "";
        map<int, Contact> contacts;
        map<int, ContactGroup> groups;
        string mappingData = "";
        int metaCount = 0;
        
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            if (line == "[METADATA]") {
                section = "METADATA";
                continue;
            } else if (line == "[CONTACTS]") {
                section = "CONTACTS";
                continue;
            } else if (line == "[GROUPS]") {
                section = "GROUPS";
                continue;
            } else if (line == "[MAPPINGS]") {
                section = "MAPPINGS";
                continue;
            }
            
            if (section == "METADATA") {
                if (metaCount == 0) {
                    int id;
                    stringstream(line) >> id;
                    phoneBook.setNextContactId(id);
                    metaCount++;
                } else if (metaCount == 1) {
                    int id;
                    stringstream(line) >> id;
                    phoneBook.setNextGroupId(id);
                    metaCount = 0;
                }
            } else if (section == "CONTACTS") {
                Contact contact = Contact::fromFileString(line);
                contacts[contact.getContactId()] = contact;
            } else if (section == "GROUPS") {
                ContactGroup group = ContactGroup::fromFileString(line);
                groups[group.getGroupId()] = group;
            } else if (section == "MAPPINGS") {
                mappingData += line + "\n";
            }
        }
        
        phoneBook.setContacts(contacts);
        phoneBook.setGroups(groups);
        
        ContactGroupMapping mapping;
        mapping.deserialize(mappingData);
        phoneBook.setMapping(mapping);
        
        file.close();
        cout << "Phone book loaded successfully from " << filename << "\n";
        return true;
    }
    catch (...) {
        cout << "Error loading phone book.\n";
        file.close();
        return false;
    }
}

void FileManager::setFilename(const string& fname) {
    filename = fname;
}

string FileManager::getFilename() const {
    return filename;
}