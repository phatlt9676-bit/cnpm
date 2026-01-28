#include "ContactGroupMapping.h"
#include <sstream>
using namespace std;

void ContactGroupMapping::addContactToGroup(int contactId, int groupId) {
    contactToGroups[contactId].insert(groupId);
    groupToContacts[groupId].insert(contactId);
}

void ContactGroupMapping::removeContactFromGroup(int contactId, int groupId) {
    map<int, set<int> >::iterator it = contactToGroups.find(contactId);
    if (it != contactToGroups.end()) {
        it->second.erase(groupId);
        if (it->second.empty()) {
            contactToGroups.erase(it);
        }
    }
    
    it = groupToContacts.find(groupId);
    if (it != groupToContacts.end()) {
        it->second.erase(contactId);
        if (it->second.empty()) {
            groupToContacts.erase(it);
        }
    }
}

vector<int> ContactGroupMapping::getGroupsForContact(int contactId) const {
    vector<int> groups;
    map<int, set<int> >::const_iterator it = contactToGroups.find(contactId);
    if (it != contactToGroups.end()) {
        set<int>::const_iterator setIt;
        for (setIt = it->second.begin(); setIt != it->second.end(); ++setIt) {
            groups.push_back(*setIt);
        }
    }
    return groups;
}

vector<int> ContactGroupMapping::getContactsInGroup(int groupId) const {
    vector<int> contacts;
    map<int, set<int> >::const_iterator it = groupToContacts.find(groupId);
    if (it != groupToContacts.end()) {
        set<int>::const_iterator setIt;
        for (setIt = it->second.begin(); setIt != it->second.end(); ++setIt) {
            contacts.push_back(*setIt);
        }
    }
    return contacts;
}

void ContactGroupMapping::removeAllMappingsForContact(int contactId) {
    map<int, set<int> >::iterator it = contactToGroups.find(contactId);
    if (it != contactToGroups.end()) {
        set<int>::iterator setIt;
        for (setIt = it->second.begin(); setIt != it->second.end(); ++setIt) {
            int groupId = *setIt;
            groupToContacts[groupId].erase(contactId);
            if (groupToContacts[groupId].empty()) {
                groupToContacts.erase(groupId);
            }
        }
        contactToGroups.erase(it);
    }
}

void ContactGroupMapping::removeAllMappingsForGroup(int groupId) {
    map<int, set<int> >::iterator it = groupToContacts.find(groupId);
    if (it != groupToContacts.end()) {
        set<int>::iterator setIt;
        for (setIt = it->second.begin(); setIt != it->second.end(); ++setIt) {
            int contactId = *setIt;
            contactToGroups[contactId].erase(groupId);
            if (contactToGroups[contactId].empty()) {
                contactToGroups.erase(contactId);
            }
        }
        groupToContacts.erase(it);
    }
}

bool ContactGroupMapping::isContactInGroup(int contactId, int groupId) const {
    map<int, set<int> >::const_iterator it = contactToGroups.find(contactId);
    if (it != contactToGroups.end()) {
        return it->second.find(groupId) != it->second.end();
    }
    return false;
}

void ContactGroupMapping::clear() {
    contactToGroups.clear();
    groupToContacts.clear();
}

string ContactGroupMapping::serialize() const {
    stringstream ss;
    map<int, set<int> >::const_iterator mapIt;
    for (mapIt = contactToGroups.begin(); mapIt != contactToGroups.end(); ++mapIt) {
        int contactId = mapIt->first;
        set<int>::const_iterator setIt;
        for (setIt = mapIt->second.begin(); setIt != mapIt->second.end(); ++setIt) {
            ss << contactId << "," << *setIt << "\n";
        }
    }
    return ss.str();
}

void ContactGroupMapping::deserialize(const string& data) {
    clear();
    stringstream ss(data);
    string line;
    
    while (getline(ss, line)) {
        if (line.empty()) continue;
        
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            int contactId, groupId;
            stringstream(line.substr(0, commaPos)) >> contactId;
            stringstream(line.substr(commaPos + 1)) >> groupId;
            addContactToGroup(contactId, groupId);
        }
    }
}