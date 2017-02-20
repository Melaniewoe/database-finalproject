//
//  record.cpp
//  final proj
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "record.h"

using std::string;
using std::endl;

namespace ContactDatabase
{
    
    unsigned int record::__idGen = 0;
    const string record::FIELD_NAMES[] =
    {
        "First Name", "Middle Name", "Last Name", "Company Name", "Home Phone", "Office Phone", "Email", "Mobile Number", "Street Address", "City", "State", "Zip Code", "Country", "Affiliates"
    };
    
    record::record()
    {
        __id = ++__idGen;
        first_name = "NULL";
        middle_name = "NULL";
        last_name = "NULL";
        company_name = "NULL";
        home_phone = "NULL";
        office_phone = "NULL";
        __email = "NULL";
        mobile_number = "NULL";
        street_address = "NULL";
        __city = "NULL";
        __state = "NULL";
        __zipCode = "NULL";
        __country = "NULL";
    }
    
    record::record(string firstname, string middlename, string lastname, string companyname, string homephone, string email, string mobilenumber, string Address, string City, string State, string ZipCode, string Country) : record()
    {
        first_name = firstname;
        middle_name = middlename;
        last_name= lastname;
        company_name = companyname;
        home_phone = homephone;
        office_phone = office_phone;
        __email = email;
        mobile_number = mobilenumber;
        street_address = street_address;
        __city = city;
        __state = state;
        __zipCode = ZipCode;
        __country = Country;
    }
    
    //  Setters
    void record::setField(unsigned int index, string entry)
    {
        switch (index)
        {
            case 0:
                first_name = entry;
                break;
            case 1:
                middle_name = entry;
                break;
            case 2:
                last_name = entry;
                break;
            case 3:
                company_name= entry;
                break;
            case 4:
                setHomePhone(entry);
                break;
            case 5:
                setOfficePhone(entry);
                break;
            case 6:
                setEmail(entry);
                break;
            case 7:
                setMobilePhone(entry);
                break;
            case 8:
                street_address = entry;
                break;
            case 9:
                __city = entry;
                break;
            case 10:
                __state = entry;
                break;
            case 11:
                __zipCode = entry;
                break;
            case 12:
                __country = entry;
                break;
            default:
                break;
        }
    }
    
    //conver number to string
    void record::setHomePhone(string number)
    {
        home_phone = convertNumber(number);
    }
    
    void record::setOfficePhone(string number)
    {
        office_phone = convertNumber(number);
    }
    
    void record::setMobilePhone(string number)
    {
        mobile_number= convertNumber(number);
    }
    
    void record::setEmail(string email)
    {
        __email = convertEmail(email);
    }
    
    void record::addAffiliate(const record::Affiliates &aff)
    {
        __affiliates.push_back(aff);
    }
    
    //  Getters - Const
    std::ostream &record::printDetailed(std::ostream &os) const
    {
        // Print out contact information
        for (unsigned int i = 0; i < NUM_FIELDS; ++i)
        {
            os << FIELD_NAMES[i] << ": ";
            if (getField(i) == "NULL")
                os << "<Empty>";
            else
                os << getField(i);
            os << "\n";
        }
        
        // Print out affiliate information is exists
        for (auto it = __affiliates.begin(); it != __affiliates.end(); ++it)
        {
            os << *it;
        }
        
        return os;
    }
    
    const record::Affiliates &record::getAffiliate(unsigned int index) const
    {
        
        return __affiliates[index];
    }
    
    void record::removeAffiliate(Affiliates &aff)
    {
        for (auto it = __affiliates.begin(); it != __affiliates.end(); ++it)
        {
            if (*it == aff)
            {
                __affiliates.erase(it);
            }
        }
    }
    
    const string &record::getField(unsigned int index) const
    {
        
        switch (index)
        {
            case 0:
                return first_name;
            case 1:
                return middle_name;
            case 2:
                return last_name;
            case 3:
                return company_name;
            case 4:
                return home_phone;
            case 5:
                return office_phone;
            case 6:
                return __email;
            case 7:
                return mobile_number;
            case 8:
                return street_address;
            case 9:
                return __city;
            case 10:
                return __state;
            case 11:
                return __zipCode;
            case 12:
                return __country;
            default:
            return first_name;        }
    }
    
    const string &record::operator[](unsigned int index) const
    {
        switch (index)
        {
            case 0:
                return first_name;
            case 1:
                return middle_name;
            case 2:
                return last_name;
            case 3:
                return company_name;
            case 4:
                return home_phone;
            case 5:
                return office_phone;
            case 6:
                return __email;
            case 7:
                return mobile_number;
            case 8:
                return street_address;
            case 9:
                return __city;
            case 10:
                return __state;
            case 11:
                return __zipCode;
            case 12:
                return __country;
            default:
                return first_name;
        }
    }
    
    void record::printNames(FieldSearch f1, FieldSearch f2) const
    {
        std::cout << std::setw(14) << getFirstName();
        if (getMiddleName() != "NULL")
            std::cout << std::setw(14) << getMiddleName();
        if (getLastName() != "NULL")
            std::cout << std::setw(14) << getLastName();
        // Print additional fields as neccessary
        if (f1 != FieldSearch::firstname && f1 != FieldSearch::lastname
            && f1 != FieldSearch::middlename)
        {
            if (getField((unsigned) f1) != "NULL")
                std::cout << std::setw(17) << getField((unsigned) f1).substr(0, 15);
        }
        if (f2 != FieldSearch::firstname && f2 != FieldSearch::lastname
            && f2 != FieldSearch::middlename)
        {
            if (getField((unsigned) f2) != "NULL")
                std::cout << std::setw(17) << getField((unsigned) f2).substr(0, 15);
        }
    }
    
    bool record::searchFor(string &item, FieldSearch field, SearchMode mode) const
    {
        // If null then no search is happening, include everything
        if (item == "NULL") return true;
        
        // Searching all fields for exact or contains
        // Includes affiliates
        if ( field == FieldSearch::all )
        {
            // Search all records
            if ( mode == SearchMode::EXACT )
            {
                // Exact searches: every character must match
                // a string == comparison
                bool contains = false;
                for (unsigned int i = 0; i < (unsigned int)FieldSearch::affiliates; ++i)
                {
                    if (getField(i) == item)
                        contains = true;
                }
                
                for (unsigned int i = 0; i < __affiliates.size(); ++i) {
                    if (__affiliates[i].getFirstName() == item)
                        contains = true;
                    if (__affiliates[i].getLastName() == item)
                        contains = true;
                    if (__affiliates[i].getMobilePhone() == item)
                        contains = true;
                    if (__affiliates[i].getEmail() == item)
                        contains = true;
                }
                
                return contains;
            }
            else
            {
                // mode is CONTAINS
                bool contains = false;
                for (unsigned int i = 0; i < (unsigned int)FieldSearch::affiliates; ++i)
                {
                    int p = getField(i).find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                }
                
                for (unsigned int i = 0; i < __affiliates.size(); ++i)
                {
                    int p = __affiliates[i].getFirstName().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                    p = __affiliates[i].getLastName().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                    p = __affiliates[i].getMobilePhone().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                    p = __affiliates[i].getEmail().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                }
                
                return contains;
            }
        }
        
        // Searching individual fields for exact or contains
        if ( field != FieldSearch::affiliates)
        {
            // non-affiliates are more straightforward
            // searching in a specific field
            if ( mode == SearchMode::EXACT )
            {
                // Exact searches: every character must match
                // a string == comparison
                return (getField((unsigned int)field) == item);
            }
            else {
                // mode is CONTAINS
                int p = getField((unsigned int)field).find(item);
                return (p != string::npos);
            }
        }
        else {
            // Searching through affiliates, all fields
            bool contains = false;
            if ( mode == SearchMode::EXACT ) {
                for (unsigned int i = 0; i < __affiliates.size(); ++i) {
                    if (__affiliates[i].getFirstName() == item)
                        contains = true;
                    if (__affiliates[i].getLastName() == item)
                        contains = true;
                    if (__affiliates[i].getMobilePhone() == item)
                        contains = true;
                    if (__affiliates[i].getEmail() == item)
                        contains = true;
                }
            }
            else
            {
                // Contains
                for (unsigned int i = 0; i < __affiliates.size(); ++i)
                {
                    int p = __affiliates[i].getFirstName().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                    p = __affiliates[i].getLastName().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                    p = __affiliates[i].getMobilePhone().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                    p = __affiliates[i].getEmail().find(item);
                    if (p != string::npos)
                    {
                        contains = true;
                    }
                }
            }
            
            return contains;
        }
    }
    
    //  Getters - Non-Const
    record::Affiliates &record::getAffiliate(unsigned int index)
    {
        
        return __affiliates[index];
    }
    
    string &record::getField(unsigned int index)
    {
        
        switch (index)
        {
            case 0: return first_name;
            case 1: return middle_name;
            case 2: return last_name;
            case 3: return company_name;
            case 4: return home_phone;
            case 5: return office_phone;
            case 6: return __email;
            case 7: return mobile_number;
            case 8: return street_address;
            case 9: return __city;
            case 10: return __state;
            case 11: return __zipCode;
            case 12: return __country;
            default: return first_name;
        }
    }
    string &record::operator[](unsigned int index)
    {
        
        switch (index)
        {
            case 0: return first_name;
            case 1: return middle_name;
            case 2: return last_name;
            case 3: return company_name;
            case 4: return home_phone;
            case 5: return office_phone;
            case 6: return __email;
            case 7: return mobile_number;
            case 8: return street_address;
            case 9: return __city;
            case 10: return __state;
            case 11: return __zipCode;
            case 12: return __country;
            default: return first_name;
        }
    }
    
    // Friend functions
    std::ostream& operator<<(std::ostream &os, const record::Affiliates &aff) {
        os << aff.getFirstName() << " " << aff.getLastName();
        
        if (aff.getMobilePhone() != "NULL" || aff.getEmail() != "NULL") {
            os << ", " << aff.getMobilePhone();
            os << ", " << aff.getEmail();
        }
        
        os << ";" << endl;
        
        return os;
    }
    
    std::ostream &operator<<(std::ostream &os, const record &contact)
    {
        for (unsigned int i = 0; i < (9 - std::to_string(contact.getID()).size()); ++i)
            os << "0";
        os << contact.getID() << endl;
        os << contact.getFirstName() << endl;
        os << contact.getMiddleName() << endl;
        os << contact.getLastName() << endl;
        os << contact.getCompanyName() << endl;
        os << contact.getHomePhone() << endl;
        os << contact.getOfficePhone() << endl;
        os << contact.getEmail() << endl;
        os << contact.getMobilePhone() << endl;
        os << contact.getStreetAddress() << endl;
        os << contact.getCity() << endl;
        os << contact.getState() << endl;
        os << contact.getZipCode() << endl;
        os << contact.getCountry() << endl;
        for (auto it = contact.__affiliates.begin(); it != contact.__affiliates.end(); ++it) {
            os << *it;
        }
        return os;
    }
    
    std::istream &operator>>(std::istream &is, record &contact)
    {
        contact.loadFromStream(is);
        
        return is;
    }
    
    //  Private functions
    string &record::convertNumber(string &number) {
        // converts phone number into
        // (123) 123-3210
        // 12345678901234
        // format
        string newNumber = "(";
        for (unsigned int i = 0; i < number.size(); ++i) {
            if (number[i] >= '0' && number[i] <= '9') {
                newNumber += number[i];
            }
            if (newNumber.size() == 4) {
                newNumber += ") ";
            }
            if (newNumber.size() == 9) {
                newNumber += "-";
            }
        }
        
        number = newNumber;
        return number;
    }
    
    string &record::convertEmail(string &email) {
        // Appends @email.com
        // to the end if it's not present already
        string newemail;
        bool contains = false;
        for (int i = 0; i < email.size(); ++i) {
            if (email[i] == '@') contains = true; break;
        }
        if (!contains) {
            newemail = email + "@email.com";
        }
        
        email = newemail;
        return email;
    }
    
    std::istream &record::loadFromStream(std::istream &is)
    {
        string line;
        getline(is, line);
        
        __idGen--;
        //if (is.eof()) std::cout << "Warning... Empty contact file." << std::endl;
        //if (line.size() != 9) std::cout << "Warning... Corrupt contact file." << std::endl;
        //std::cout << line.size();
        //if (line.size() != 9 && line.size() != 0) throw ExCorruptFile("ID of contact incorrect size.");
        while (!is.eof() && line[0] != '|' /*&& line.size() == 9*/ && line[0] != ' ') {
            bool contactfound = false;
            while (!contactfound && !is.eof()) {
                if (is.eof()) return is;
                try {
                    setID((unsigned) std::stoi(line));
                    contactfound = true;
                }
                catch (...)
                {
                    contactfound = false;
                    getline(is, line);
                }
            }
            if (__id > __idGen) __idGen = (__id + 1);
            for (unsigned int i = 0; i < record::NUM_FIELDS; ++i)
            {
                getline(is, line);
                if (line.size() > 0)
                    getField(i) = line;
                else
                    setField(i, "NULL");
            }
            
            //Affiliates
            getline(is, line);
            while (line[0] != '|' && !is.eof())
            {
                if (getNumChars(line, ','))
                {
                    if (getNumChars(line, ';') == 0)
                    {
                        cout << "Contact: " << getID() << " " << getFirstName() << " ";
                        cout << getMiddleName() << " " << getLastName() << std::endl;
                        cout << "Not loaded due to an affiliate error.\n";
                    }
                    // Has email and phone number
                    string  a_fn, a_ln, a_pn, a_em;
                    
                    a_fn = getWordN(line, 0);
                    line = line.substr(a_fn.size() + 1);
                    a_ln = getWordN(line, 0);
                    a_ln = a_ln.substr(0, a_ln.size() - 1);
                    line = line.substr(a_ln.size() + 2);
                    a_pn = getWordN(line, 0, ',');
                    line = line.substr(a_pn.size() + 2);
                    a_em = getWordN(line, 0, ';');
                    
                    record::Affiliates a(this, a_fn, a_ln, a_pn, a_em);
                    addAffiliate(a);
                }
                else
                {
                    if (getNumChars(line, ';') == 0)
                    {
                        cout << "Contact: " << getID() << " " << getFirstName() << " ";
                        cout << getMiddleName() << " " << getLastName() << std::endl;
                        cout << "Not loaded due to an affiliate error.\n";
                    }
                    // Does not have email or phone number
                    string a_fn, a_ln;
                    
                    a_fn = getWordN(line, 0);
                    line = line.substr(a_fn.size() + 1);
                    a_ln = getWordN(line, 0);
                    a_ln = a_ln.substr(0, a_ln.size() - 1);
                    
                    record::Affiliates a(this, a_fn, a_ln);
                    addAffiliate(a);
                }
                
                getline(is, line);
            }
            
            //getline(is, line);
        }
        
        return is;
    }
    
    string record::getWordN(string str, unsigned int n, char c, unsigned int pos)
    {
        unsigned int cn = 0;
        string tempstring;
        
        for (unsigned int i = pos; i < str.size(); ++i) {
            if (str[i] == c) cn++;
            else {
                if (n == cn) {
                    tempstring += str[i];
                }
            }
        }
        
        return tempstring;
    }
    
    int record::getNumChars(string str, char c) {
        int n = 0;
        for (int i = 0 ; i < str.size(); i++) {
            if (str[i] == c) n++;
        }
        
        return n;
    }
}