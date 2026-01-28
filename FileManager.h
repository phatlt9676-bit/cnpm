#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "PhoneBook.h"
#include <string>
using namespace std;

class FileManager {
private:
    string filename;

public:
    FileManager(const string& filename = "phonebook.dat");
    
    // FR-14: Save phone book to file
    bool savePhoneBook(const PhoneBook& phoneBook);
    
    // FR-15: Load phone book from file
    bool loadPhoneBook(PhoneBook& phoneBook);
    
    // Utility
    void setFilename(const string& filename);
    string getFilename() const;
};

#endif