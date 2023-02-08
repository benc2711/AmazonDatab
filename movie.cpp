#include "product.h"
#include "movie.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>


Movie::Movie(const std::string genre, const std::string name, double price, int qty, std::string rating):
    Product("movie", name,  price,  qty)
{
    genre_ = genre;
    rating_ = rating;
} 

std::set<std::string> Movie::keywords() const{
    std::set<std::string> retval;
    retval.insert(genre_);
    retval.insert(Product::getName());
    return retval;
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
    std::string d = std::to_string(Product::getPrice());
    retval = "Name: " + Product::getName() + " Price: " + d + " Quantity " + std::to_string(Product::getQty()) + " Catagory: Movie " + "Genre: " + genre_ ;
    return retval;
}

void Movie::dump(std::ostream& os) const{
    std::string retval;
    std::string d = std::to_string(Product::getPrice());
    os << "movie\n"  << Product::getName()  << "\n" << d  << "\n" << std::to_string(Product::getQty()) << "\n" << genre_ << "\n" << rating_ << "\n";
    

}
