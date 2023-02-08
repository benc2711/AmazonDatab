#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>


class Movie: public Product{
    public:
        Movie(const std::string genre, const std::string name, double price, int qty, std::string rating);
        
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
        std::string genre_;
        std::string rating_;
        
};

#endif
