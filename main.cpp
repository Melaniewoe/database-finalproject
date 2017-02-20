//
//  main.cpp
//  Final project
//
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#include <iostream>
#include <fstream> //for the stream
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include "database.h"
#include "record.h"
#include "avltree.h"

using namespace std;


int main()
{
    ContactDatabase::database file("database.txt");
    file.menuMain();
    
    return 0;

}