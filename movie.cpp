#include "product.h"
#include "movie.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>
#include "util.h"
#include <iomanip>
#include <math.h>


Movie::Movie(const std::string genre, const std::string name, double price, int qty, std::string rating):
    Product("movie", name,  price,  qty)
{
    genre_ = genre;
    rating_ = rating;
} 

std::set<std::string> Movie::keywords() const{
    std::set<std::string> toWords;
    std::set<std::string> toWordsG;
    toWords = parseStringToWords(Product::getName());
    toWordsG = parseStringToWords(genre_);
    return setUnion(toWords, toWordsG);
    
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
    bool match = false;
    bool genreMatch = false;
    for(unsigned int i = 0; i < searchTerms.size(); i++){
        if(Product::getName() == searchTerms[i]){
            match = true;
        }
        if(genre_ == searchTerms[i]){
            genreMatch = true;
        }
       
    }
    if(genreMatch && match){
        return true;
    }
    else{
        return false;
    }
}

std::string Movie::displayString() const{
    std::string retval;
    // std::cout << "MADE HERE " << std::endl;
    std::string d = std::to_string(Product::getPrice());
    retval = Product::getName() + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + d + " " + std::to_string(Product::getQty()) + " left.";
    return retval;
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << std::endl;
    os << rating_ << std::endl;
    

}
