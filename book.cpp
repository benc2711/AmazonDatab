#include "product.h"
#include "book.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>


Book::Book(const std::string author, std::string ISBN,  const std::string name, double price, int qty) : 
    Product("book", name,  price,  qty)
{
    ISBN_ = ISBN;
    author_ = author;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> retval;
    retval.insert(author_);
    retval.insert(Product::getName());
    retval.insert(ISBN_);
    return retval;
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
    retval = "Name: " + Product::getName() + " Price: " + d + " Quantity " + std::to_string(Product::getQty()) + " Catagory: Book " + "Author: " + author_ + "ISBN: " + ISBN_;
    return retval;
}

void Book::dump(std::ostream& os) const{
    std::string retval;
    std::string d = std::to_string(Product::getPrice());
    os << "book\n"  << Product::getName()  << "\n" << d  << "\n" << std::to_string(Product::getQty()) << "\n" << ISBN_ << "\n" << author_ << "\n";
    

}
