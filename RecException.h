//
//  Header.h
//  final proj
//
//  Created by ☁︎ ⓜⓔⓛⓘⓝⓓⓐ.ⓦ ☁︎ on 5/9/16.
//  Copyright © 2016 Melanie Woe. All rights reserved.
//

#ifndef RecException_H
#define RecException_H

#include <string>
#include <iostream>

#include "itemtype.h"

namespace ContactDatabase {
    
    class ExEmptyTree {
    public:
        ExEmptyTree() { __name = "ExEmptyTree"; }
        
        std::ostream &print(std::ostream &os) {
            os << __name << std::endl;
            return os;
        }
        
        friend std::ostream &operator<<(ExEmptyTree &ex, std::ostream &os) {
            ex.print(os);
            return os;
        }
        
    private:
        std::string __name;
    };
    
    class ExItemNotFound {
    public:
        ExItemNotFound(const ItemType &item) {
            __name = "ExItemNotFound";
            __item = item;
        }
        
        std::ostream &print(std::ostream &os) {
            os << __name << ": " << __item << std::endl;
            return os;
        }
        
        std::ostream &operator<<(std::ostream &os) {
            print(os);
            return os;
        }
        
    private:
        std::string __name;
        ItemType __item;
    };
}

#endif //RecException_H