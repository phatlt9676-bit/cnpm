#ifndef CONTACTGROUPMAPPING_H
#define CONTACTGROUPMAPPING_H

#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

class ContactGroupMapping {
private:
    // Maps contactId to set of groupIds
    map<int, set<int> > contactToGroups;
    // Maps groupId to set of contactIds
    map<int, set<int> > groupToContacts;

public:
    // Add a contact to a group
    void addContactToGroup(int contactId, int groupId);
    
    // Remove a contact from a group
    void removeContactFromGroup(int contactId, int groupId);
    
    // Get all groups for a contact
    vector<int> getGroupsForContact(int contactId) const;
    
    // Get all contacts in a group
    vector<int> getContactsInGroup(int groupId) const;
    
    // Remove all mappings for a contact
    void removeAllMappingsForContact(int contactId);
    
    // Remove all mappings for a group
    void removeAllMappingsForGroup(int groupId);
    
    // Check if contact is in group
    bool isContactInGroup(int contactId, int groupId) const;
    
    // Clear all mappings
    void clear();
    
    // For file operations
    string serialize() const;
    void deserialize(const string& data);
};

#endif