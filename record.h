//
//  record.h
//  final proj
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#ifndef record_hpp
#define record_hpp

#include <string>
#include <vector>
#include <iostream>

using namespace std;


// Search field options
enum FieldSearch
{
    id = 0, firstname, middlename, lastname, companyname, homephone, officephone, email, mobilenumber, streetaddress, city, state, zipcode, country, affiliates, all
};

enum SearchMode
{
    EXACT=0, CONTAINS
};

namespace ContactDatabase
{
    class record
    {
    public:
        // Constants
        static const int NUM_FIELDS = 13;
        
        static const string FIELD_NAMES[];
        
        //Affiliates
        class Affiliates
        {
        public:
            //  Constructors
            Affiliates(record *owner, string firstname, string lastname,
                       string number = "NULL", string email = "NULL")
            {
                first_name = firstname;
                last_name = lastname;
                mobile_number = number;
                __email = email;
                __owner = owner;
            }
            
            //  Setters
            void setFirstName(string firstname)
            {
                first_name = firstname;
            }
            void setMiddleName(string middlename)
            {
                middle_name = middlename;
            }
            void setLastName(string lastname)
            {
                last_name = lastname;
            }
            void setNumber(string number)
            {
                mobile_number = __owner->convertNumber(number);
            }
            void setEmail(string email)
            {
                __email = email;
            }
            
            //  Accessors
            const string &getFirstName() const
            {
                return first_name;
            }
            const string &getMiddleName() const
            {
                return middle_name;
            }
            const string &getLastName() const
            {
                return last_name;
            }
            const string &getMobilePhone() const
            {
                return mobile_number;
            }
            const string &getEmail() const
            {
                return __email;
            }
            const string &getCompanyName() const
            {
                return __owner->getCompanyName();
            }
            const string &getHomePhone() const
            {
                return __owner->getHomePhone();
            }
            const string &getOfficePhone() const
            {
                return __owner->getOfficePhone();
            }
            const string &getStreetAddress() const
            {
                return __owner->getStreetAddress();
            }
            const string &getState() const
            {
                return __owner->getState();
            }
            const string &getZipCode() const
            {
                return __owner->getZipCode();
            }
            const string &getCountry() const
            {
                return __owner->getCountry();
            }
            const record *getOwner() const
            {
                return __owner;
            }
            
            //  Friend functions
            friend ostream &operator<<(std::ostream &os, const Affiliates &aff);
            friend bool operator==(const Affiliates &lhs, const Affiliates &rhs)
            {
                return (lhs.first_name == rhs.first_name && lhs.last_name == rhs.last_name &&
                        lhs.__email == rhs.__email && lhs.mobile_number == rhs.mobile_number);
            }
            friend bool operator!=(const Affiliates &lhs, const Affiliates &rhs)
            {
                return !(lhs == rhs);
            }
            
        private:
            string first_name;
            string last_name;
            string middle_name;
            string mobile_number;
            string __email;
            record *__owner;
        };
       
        record();
        record(string firstname, string middlename, string lastname, string companyname, string homephone, string email, string mobilenumber, string Address, string City, string State, string ZipCode, string Country);
        
        // Helpers
        string &convertNumber(string &number);
        string &convertEmail(string &email);
        
        //  Setters
        istream &loadFromStream(istream &is);
        void setField(unsigned int index, string entry);
        void setID(unsigned int id)
        {
            __id = id;
        }
        void setFirstName(string name)
        {
            first_name = name;
        }
        void setLastName(string name)
        {
            last_name = name;
        }
        void setMiddleName(string name)
        {
            middle_name = name;
        }
        void setCompanyName(string name)
        {
            company_name = name;
        }
        void setHomePhone(string number);
        void setOfficePhone(string number);
        void setMobilePhone(string number);
        void setEmail(string email);
        void setStreetAddress(string address)
        {
            street_address = address;
        }
        void setCity(string city)
        {
            __city = city;
        }
        void setState(string state)
        {
            __state = state;
        }
        void setZipCode(string zipcode)
        {
            __zipCode = zipcode;
        }
        void setCountry(string country)
        {
            __country = country;
        }
        void addAffiliate(const Affiliates &aff);
        void removeAffiliate(Affiliates &aff);
        
        //  Accessors - Constant
        ostream &printDetailed(ostream &os) const;
        const string &getField(unsigned int index) const;
        const unsigned int getID() const
        {
            return __id;
        }
        const string &getFirstName() const
        {
            return first_name;
        }
        const string &getMiddleName() const
        {
            return middle_name;
        }
        const string &getLastName() const
        {
            return last_name;
        }
        const string &getCompanyName() const
        {
            return company_name;
        }
        const string &getHomePhone() const
        {
            return home_phone;
        }
        const string &getOfficePhone() const
        {
            return office_phone;
        }
        const string &getMobilePhone() const
        {
            return mobile_number;
        }
        const string &getEmail() const
        {
            return __email;
        }
        const string &getStreetAddress() const
        {
            return street_address;
        }
        const string &getCity() const
        {
            return __city;
        }
        const string &getState() const
        {
            return __state;
        }
        const string &getZipCode() const
        {
            return __zipCode;
        }
        const string &getCountry() const
        {
            return __country;
        }
        unsigned int getNumAffiliates() const
        {
            return __affiliates.size();
        }
        const Affiliates &getAffiliate(unsigned int index) const;
        const string &operator[](unsigned int index) const;
        void printNames(FieldSearch f1 = FieldSearch::firstname, FieldSearch f2 = FieldSearch::lastname) const;
        bool searchFor(string &item, FieldSearch field = FieldSearch::all, SearchMode mode = SearchMode::EXACT) const;
        
        //  Accessors - Non-Constant
        string &getField(unsigned int index);
        string &getFirstName()
        {
            return first_name;
        }
        string &getMiddleName()
        {
            return middle_name;
        }
        string &getLastName()
        {
            return last_name;
        }
        string &getCompanyName()
        {
            return company_name;
        }
        string &getHomePhone()
        {
            return home_phone;
        }
        string &getOfficePhone()
        {
            return office_phone;
        }
        string &getMobilePhone()
        {
            return mobile_number;
        }
        string &getEmail()
        {
            return __email;
        }
        string &getStreetAddress()
        {
            return street_address;
        }
        string &getCity()
        {
            return __city;
        }
        string &getState()
        {
            return __state;
        }
        
        string &getZipCode()
        {
            return __zipCode;
        }
        string &getCountry()
        {
            return __country;
        }
        Affiliates &getAffiliate(unsigned int index);
        string &operator[](unsigned int index);
        
        // Friend functions
        friend std::ostream &operator<<(std::ostream &os, const record &contact);
        friend std::istream &operator>>(std::istream &is, record &contact);
        friend bool operator<(const record& lhs, const record& rhs)
        {
            return (lhs.getID() < rhs.getID());
        }
        friend bool operator>=(const record& lhs, const record& rhs)
        {
            return (lhs.getID() >= rhs.getID());
        }
        friend bool operator>(const record& lhs, const record& rhs)
        {
            return (lhs.getID() > rhs.getID());
        }
        friend bool operator<=(const record& lhs, const record& rhs)
        {
            return (lhs.getID() <= rhs.getID());
        }
        friend bool operator==(const record& lhs, const record& rhs)
        {
            return (lhs.getID() == rhs.getID());
        }
        friend bool operator!=(const record& lhs, const record& rhs)
        {
            return !(lhs == rhs);
        }
        
        
    private:
        // Variables
        unsigned int __id;
        static unsigned int __idGen;
        string first_name;
        string middle_name;
        string last_name;
        string company_name;
        string home_phone;
        string office_phone;
        string __email;
        string mobile_number;
        string street_address;
        string __city;
        string __state;
        string __zipCode;
        string __country;
        
        // Vector list of affiliates
        vector<Affiliates> __affiliates;
        
        // Private functions
        string getWordN(string str, unsigned int n, char c = ' ', unsigned int pos = 0);
        int getNumChars(string str, char c);
    };
    
    class SortContacts
    {
    public:
        SortContacts() : __index(0) { }
        SortContacts(FieldSearch index)
        : __index((unsigned) index) { }
        
        bool operator()(record &a, record &b)
        {
            return (a.getField(__index) < b.getField(__index));
        }
        
    private:
        unsigned int __index;
    };
}


#endif /* record_hpp */
