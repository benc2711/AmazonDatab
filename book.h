#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>


class Book: public Product{
    public:
        Book(const std::string author, std::string ISBN,  const std::string name, double price, int qty);
        
        std::set<std::string> keywords() const;

        /**
         * Allows for a more detailed search beyond simple keywords
         */
        bool isMatch(std::vector<std::string>& searchTerms) const;

        /**
         * Returns a string to display the product info for hits of the search
         */
        std::string displayString() const;

        /**
         * Outputs the product info in the database format
         */
        void dump(std::ostream& os) const;
    private:
        std::string author_;
        std::string ISBN_;
};

#endif
