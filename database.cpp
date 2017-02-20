//
//  informations.cpp
//  Final project
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//


//implementation of database.h

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "record.h"
#include "database.h"

namespace ContactDatabase
{
    
    database::database()
    {
        __tree = new AVLTree;
        __lastFile = "NULL";
    }
    
    database::database(string ID) : database()
    {
        __lastFile = "NULL";
        loadContacts(ID);
    }
    
    database::~database()
    {
        delete __tree;
    }
    
   
    string database::getLine()
    {
        string line;
        
        getline(cin, line);
        
        return line;
    }
    
    unsigned int database::getNumbers(int from, int to)
    {
        string word;
        int num = 0000;
        while (word.size() < 1 || num < from || num > to)
        {
            getline(cin, word, '\n');
            
        }
        
        return (unsigned ) num;
    }
    
    
   //call out main menu
    void database::menuMain()
    {
        menuDisplay(*__tree);
    }
    
    
     //display the record by first name, middle name, last name, etc...
    void database::menuDisplay(AVLTree &tree)
    {
        int choice;
        vector<ItemType> myvector;
        
        
        while (choice != 4)
        {
            cout << endl << "------ Menu ------" << endl;
            cout << "1. Sort records"  << endl;
            cout << "2. Display records"  << endl;
            cout << "3. Add record" << endl;
            cout << "4. Modify record" << endl;
            cout << "5. Search record " << endl;
            cout << "6. Load record" << endl;
            cout << "7. Save record" << endl;
            cout << "8. Exit" << endl;
            
            cout << "your choice is: ";
            cin >> choice;

            
            switch (choice)
            {
                case 1:
                {
                    // Sort and display
                    FieldSearch field;
                    
                    //ask the user input
                    cout << "Enter the FIRST field to sort by:" << endl;
                    for (int i = 0; i < record::NUM_FIELDS; ++i)
                    {
                        if (i % 3 == 0)
                            cout << std::endl;
                        
                        string o = to_string(i + 1) + ") " + record::FIELD_NAMES[i];
                        
                    }
                    
                    field = (FieldSearch) (getNumbers(1, record::NUM_FIELDS) - 1);
                    
                    
                    // Clear then display with sort fields
                    myvector.clear();
                    displaySorted(tree, myvector, field);
                }
                    break;
                    
                    
                    
                case 2:
                    // Sort and display, loading for next menu iteration
                    
                    displaySorted(tree, myvector);
                    break;
               
                case 3:
                    menuAddContact();
                    
                    break;
                    
                case 4:
                    
                    unsigned int row;
                    cout << "Enter contact row number to modify:\n";
                    cin >> row;
                    //row = getNumbers(1, myvector.size());
                    //row--;
                    if (row < myvector.size())
                    {
                        menuModifyContact(myvector[row]);
                        choice = 0;
                    }
                    else
                        cout << "Error: Row #" << row << " does not exist!" << endl;
             
                    break;
                    
                case 5:
                    menuSearch();
                    break;
                case 6:
                    menuLoad();
                    break;
                case 7:
                    menuSave();
                    break;
                case 8:
                    return; //exit
                    break;
                    
                default:
                    break;
            }
            
        }
        if (tree.size() == 0)
        {
            cout << "Record is empty" << endl;
            return;
        }
        
    }
    
    //search for the record by the category
    void ContactDatabase::database::menuSearch()
    {
        // Make sure list is not empty
        if (__tree->size() == 0)
        {
            cout << "Record is empty" << endl;
            return;
        }
      
        
        // Search arguments
        FieldSearch field = FieldSearch::all;
        SearchMode mode = SearchMode::EXACT;
        
        string item = "NULL";
        
        // Tree with search results
        AVLTree searchtree(*__tree);
        vector<ItemType> myvector;
        
        // Menu choice
        unsigned int choice = 0;
        
        while (choice != 6)
        {
            if (__tree->size() == searchtree.size())
                cout << endl << "------ Menu ------" << endl;
            else
                cout << endl << "------ Sub Menu ------" << endl;
            cout << "1. Search" << endl;
            cout << "2. Enter a search term" << endl;
            cout << "3. Select field to search" << endl;
            cout << "4. Select search mode" << endl;
            cout << "5. Display & Sort Menu" << endl;
            cout << "6. exit" << endl;
            
            cin >> choice;
            
            switch (choice)
            {
                case 1:
                {
                    AVLTree tmp(searchtree);
                    searchtree.clearTree();
                    try
                    {
                        tmp.addTree(searchtree, item, field, mode);
                    }
                    catch (ContactDatabase::ExEmptyTree &ex)
                    {
                        cerr << "Exception thrown: ";
                        ex.print(cerr);
                        cerr << endl;
                    }
                    if (searchtree.size() > 0)
                    {
                        myvector.clear();
                        displaySorted(searchtree, myvector);
                    }
                    else
                    {
                        cout << "\n\nSearch produced no results!\n\n";
                        __tree->addTree(searchtree);
                    }
                }
                    break;
                    
                case 2:
                {
                    cout << "\nEnter a word or phrase to search for:\n";
                    getline(cin, item, '\n');
                }
                    break;
                    
                case 3:
                {
                    cout << endl << "Please enter a field to be searched:" << endl;
                    for (int i = 0; i < record::NUM_FIELDS; ++i)
                    {
                        if (i % 3 == 0) std::cout << std::endl;
                        
                        string o = to_string(i + 1) + ") " + record::FIELD_NAMES[i];
                    }
                    cout << (record::NUM_FIELDS + 1) << ") ALL\n";
                
                    choice = getNumbers(0, record::NUM_FIELDS + 1);
                    if (choice == (record::NUM_FIELDS + 1))
                    {
                        field == FieldSearch::all;
                    }
                    else
                    {
                        choice--;
                        field = (FieldSearch) choice;
                    }
                }
                    break;
                    
                case 4:
                {
                    cout << "Enter a mode to search by:" << endl;
                    cout << "1) Exact" << endl;
                    cout << "2) Contains" << endl;
                    choice = getNumbers(1, 2);
                    choice--;
                    switch (choice)
                    {
                        case 0: mode = SearchMode::EXACT;
                            break;
                        case 1: mode = SearchMode::CONTAINS;
                            break;
                        default: break;
                    }
                }
                    break;
                    
                case 5:
                    menuDisplay(searchtree);
                    break;
                    
               
                case 6:
                    return;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
   //create a new record
    void ContactDatabase::database::menuAddContact()
    {
        ContactDatabase::record rec;
        menuModifyContact(rec);
        
    }
    
    /*
     * Modify Contact Menu
     * Menu to modify contact values
     */
    void ContactDatabase::database::menuModifyContact(record &rec)
    {
        record database = rec;
        unsigned int input = 0;
        while (input != (rec.NUM_FIELDS + 2))
        {
            // Display menu
            cout << "modify contact" << endl;
            
            // Print current state of contact
            rec.printDetailed(cout);
            
            
            
            // If within input range, get entry from user
            if (input < rec.NUM_FIELDS)
            {
                string entry;
                
                // Sub menu for new entry
                cout << "Records available: " << endl;
                cout << rec.FIELD_NAMES[input] << ": ";
                if (rec.getField(input) == "NULL")
                    cout << "-----empty-----";
                else
                    cout << rec.getField(input) << endl;
                    cout << "Please enter a new entry for field: " << rec.FIELD_NAMES[input] << endl;
                
                cin >> entry;
                
                while (entry == "NULL")
                {
                    cout << "Cannot be 'NULL'. Please re-enter:\n";
                    entry = getLine();
                }
                
                if (entry.size() == 0) entry = "NULL";
                
                rec.setField(input, entry);
            }
            else
            {
                if (input == 13)
                {
                    // Affiliates menu
                    menuListAffiliates(rec);
                }
                else if (input == 14)
                {
                    // delete contact, make sure!
                    cout << "Are you sure you want to delete: ";
                    rec.printNames();
                    cout << "Enter yes to delete" << endl;
                    string entry;
                    
                    entry = getLine();
                    if (entry == "yes")
                    {
                        __tree->remove(rec);
                        cout << "Record deleted" << std::endl;
                        return;
                    }
                }
            }
        }
        
        if (rec.getFirstName() != "NULL")
        {
            __tree->remove(database);
            __tree->insert(rec);
        }
        else
        {
            cout << "\n\nFirst name cannot be 'NULL'\nContact not saved!\n\n";
        }
    }
    
    /*
     * List Contact's Affiliates Menu
     * Menu to select an affiliate
     */
    void ContactDatabase::database::menuListAffiliates(record &rec)
    {
        int choice = 0;
        string line;
        
        while (choice != 4)
        {
            cout << "\n------ Affiliates ------\n\n";
            for (int i = 0; i < rec.getNumAffiliates(); ++i)
            {
                cout << "#" << (i + 1) << " ";
                cout << rec.getAffiliate(i) << endl;
            }
            cout << "1. Add Affiliate" << endl;
            cout << "2. Remove Affiliate" << endl;
            cout << "3. Exit "<< endl;
            
            cin >> choice;
            
            switch (choice)
            {
                case 1:
                {
                    record::Affiliates aff(&rec, "NULL", "NULL");
                    if (aff.getFirstName() != "NULL")
                        rec.addAffiliate(aff);
                    else
                        cout << "\n\nAffiliate must have a first name. Not Added.\n\n";
                }
                    break;
                    
                case 2:
                {
                    cout << "\nEnter the row number of the affiliate to modify:\n";
                    int sel = getNumbers(1, rec.getNumAffiliates() + 1);
                    sel--;
                    
                    cout << "Are you sure you want to permenantly delete this affiliate?\n";
                    cout << "This action cannot be done! To continue enter 'YES' exactly as shown:\n";
                    string confirm = getLine();

                    
                    if (confirm == "YES")
                    {
                        rec.removeAffiliate(rec.getAffiliate(sel));
                    }
                }
                    break;
                    
                case 3:
                    return;
                    
                default:
                    break;
            }
        }
    }
    
    
    
 //print out
    void ContactDatabase::database::menuPrintReport(vector<ItemType> myvector)
    {
        enum Flags { FIRST=1, MIDDLE=2, LAST=4, COMPANY=8,
            HOME=16, OFFICE=32, EMAIL=64, MOBILE=128, STREET=256,
            CITY=512, STATE=1024, ZIP=2048, COUNTRY=4096, AFFILLIATES=8192 };
        
        unsigned int flags = Flags::FIRST | Flags::LAST | Flags::MOBILE;
        int input = 0;
        while (input != record::NUM_FIELDS + 1)
        {
            for (unsigned int i = 0; i <= record::NUM_FIELDS; ++i)
            {
                if (i % 3 == 0) std::cout << std::endl;
                string line = to_string(i) + ") " + record::FIELD_NAMES[i];
                if (flags & (1 << i)) line += "X";
                else line += "_";
                
            }
        }
    }
    
    /*
     * Load Contacts Menu
     * Prompt user for a file to load
     */
    void ContactDatabase::database::menuLoad()
    {
        string ID = "NULL";
        cout << "------Load Menu------" << std::endl;
        cout << "Enter the name of file to load:" << std::endl;
        
        cin >> ID;
        
        // file is loaded
        loadContacts(ID);
    }
    
    /*
     * Save Contacts Menu
     * Prompts the user for either the same
     * or a new filename to save contacts to
     */
    void ContactDatabase::database::menuSave()
    {
        int numOptions = 3;
        cout << "Saving Records";
        if (__lastFile != "NULL")
        {
            cout << "1) Save (same name)\n";
            cout << "2) Save as (new name)\n";
            cout << "3) Back\n";
        }
        else
        {
            numOptions = 2;
            cout << "1) Save\n";
            cout << "2) Back\n";
        }
        
        int input = 0;
        //cin >> input;
        input = getNumbers(1, numOptions);
        
        if (__lastFile == "NULL") input++;
        
        switch (input) {
            case 1: save( ); break;
            case 2: save(1); break;
            default: break;
                
        }
    }
    
    void database::loadContacts(string ID)
    {
        ifstream file(ID);
        
        if (file)
        {
            if (__tree->size() > 0)
            {
                __tree->clearTree();
            }
            try
            {
                while (!file.eof())
                {
                    record c;
                    file >> c;
                    __tree->insert(c);
                }
            }
            catch (ExCorruptFile &ex)
            {
                //file cannot be load
                cerr << "Error" << endl;
                ex.print(cerr);
            }
            
            catch (...)
            {
                cerr << "Error" << endl;
            }
            
            
            if (__tree->size() > 0)
            {
                __lastFile = ID;
            }
            
        }
        else
        {
            cout << "Error opening file, records couldn't be loaded";
        }
    }
    
    ostream &operator<<(std::ostream &os, const database &cl)
    {
        vector<ItemType> myvector;
        
        cl.__tree->addVector(myvector);
        
        for (auto &end : myvector)
        {
            os << end << "|" << std::endl;
        }
        
        return os;
    }
    
    istream &operator>>(std::istream &is, database &cl)
    {
        //int i = 0;
        while (!is.eof())
        {
            record rec;
            is >> rec;
            if (rec.getFirstName() != "NULL")
                cl.__tree->insert(rec);
        }
        
        return is;
    }
    
    vector<ItemType> &database::displaySorted(AVLTree &tree, vector<ItemType> &myvector, FieldSearch field)
    {
        
        tree.addVector(myvector);
        
        SortContacts s;
        
        // Sort based on first name then last name by default
        sort(myvector.begin(), myvector.end(), s);
        
        
        
        cout << "------------------ Record List ------------------" << std::endl;
        cout << setw(15) << "First Name";
        cout << setw(15) << "Middle Name";
        cout << setw(15) << "Last Name";
        cout << setw(15) << "Street Address";
       
        return myvector;
    }
    
    void database::save(int type)
    {
        if (type == 1 || __lastFile == "NULL")
        {
            std::string entry;
            std::cout << "Enter a filename to save the contact list as with .txt as the extension" << endl;
            entry = getLine();
            __lastFile = entry;
        }
        
        ofstream file(__lastFile);
        
        if (file)
        {
            file << *this;
            cout << "Records saved";
        }
        else
        {
            cout << "Error. File couldn't be saved";
        }
    }
    
    
}