#ifndef CONTACTGROUP_H
#define CONTACTGROUP_H

#include <string>
#include <iostream>
using namespace std;

class ContactGroup {
private:
    int groupId;
    string groupName;

public:
    // Constructors
    ContactGroup();
    ContactGroup(int id, const string& name);

    // Get
    int getGroupId() const;
    string getGroupName() const;

    // Set
    void setGroupId(int id);
    void setGroupName(const string& name);

    // method
    void displayGroup() const;
    // hiện thị danh sách group
    string toString() const;
    
    string toFileString() const;
    static ContactGroup fromFileString(const string& data);
};

#endif