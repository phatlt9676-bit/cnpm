#include "ContactGroup.h"
#include <sstream>
using namespace std;

ContactGroup::ContactGroup() : groupId(0), groupName("") {}

ContactGroup::ContactGroup(int id, const string& name)
    : groupId(id), groupName(name) {}

// Get
int ContactGroup::getGroupId() const { return groupId; }
string ContactGroup::getGroupName() const { return groupName; }

// Set
void ContactGroup::setGroupId(int id) { groupId = id; }
void ContactGroup::setGroupName(const string& name) { groupName = name; }

void ContactGroup::displayGroup() const {
    cout << "Group ID: " << groupId << " | Name: " << groupName << "\n";
}

string ContactGroup::toString() const {
    stringstream ss;
    ss << "ID: " << groupId << " | " << groupName;
    return ss.str();
}

string ContactGroup::toFileString() const {
    stringstream ss;
    ss << groupId << "|" << groupName;
    return ss.str();
}

ContactGroup ContactGroup::fromFileString(const string& data) {
    stringstream ss(data);
    string token;
    ContactGroup group;
    
    getline(ss, token, '|');
    stringstream(token) >> group.groupId;
    
    getline(ss, group.groupName, '|');
    
    return group;
}