//
//  database.hpp
//  Final project
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#ifndef database_h
#define database_h

#include <iostream>
#include <string>
#include "RecordsExceptions.h"
#include "RecException.h"
#include "record.h"
#include "AVLTree.h"

using namespace std;

namespace ContactDatabase
{
    class database
    {
    private:
        //AVLNodePtr size;
        AVLTree *__tree;
        string __lastFile;
        
        vector<ItemType> &displaySorted(AVLTree &tree, vector<ItemType> &myvector, FieldSearch field = FieldSearch::firstname);
        
        string getLine();
        
        unsigned int getNumbers(int from, int to);
        
        void save(int type = 0);
    
    public:
        database();
        database(string ID);
        ~database();
        
        
        //call menu display
        void menuMain();
        
        //display the record by first name, middle name, last name, etc...
        void menuDisplay(AVLTree &tree);
        
        //search for the record by the category
        void menuSearch();
        
        //create a new record
        void menuAddContact();
        
        //modify the record
        void menuModifyContact(record &rec);
        
        //list the records' affiliates
        void menuListAffiliates(record &rec);
        
        //print report menu
        void menuPrintReport(vector<ItemType> myvector);
        
        //load recors
        void menuLoad();
        
        //save records
        void menuSave();
        
        //load records from file to tree
        void loadContacts(string ID);
        
        //add records to tree
        friend istream &operator>>(std::istream &is, database &cl);
        
        //ouput the records to out file
        friend ostream &operator<<(std::ostream &os, const database &cl);
      
        
    
  
        
    };
}


#endif /* informations_h */
