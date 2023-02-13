#include "product.h"
#include "book.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>
#include "util.h"
#include <iomanip>
#include <math.h>




Book::Book(const std::string author, std::string ISBN,  const std::string name, double price, int qty) : 
    Product("book", name,  price,  qty)
{
    ISBN_ = ISBN;
    author_ = author;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> toWords;
    std::set<std::string> toWordsG;
    toWords = parseStringToWords(Product::getName());
    toWordsG = parseStringToWords(author_);
    toWords.insert(ISBN_);

    return setUnion(toWordsG, toWords);
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
    bool match = false;
    bool ISBNMatch = false;
    bool authormatch = false;
    for(unsigned int i = 0; i < searchTerms.size(); i++){
        if(Product::getName() == searchTerms[i]){
            match = true;
        }
        if(author_ == searchTerms[i]){
            authormatch = true;
        }
        if(ISBN_ == searchTerms[i]){
            ISBNMatch = true;
        }
    }
    if(authormatch && match && ISBNMatch){
        return true;
    }
    else{
        return false;
    }
}

std::string Book::displayString() const{
    std::string retval;
    std::string d = std::to_string(Product::getPrice());
    retval = Product::getName() + "\nAuthor: " + author_ + " ISBN: " + ISBN_ + "\n" + d + " " + std::to_string(Product::getQty()) + " left.";
    return retval;
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << ISBN_ << std::endl;
    os << author_ << std::endl;
    

}
