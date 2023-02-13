#include "product.h"
#include "clothing.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>
#include "util.h"
#include <iomanip>
#include <math.h>


Clothing::Clothing(const std::string brand, const std::string name, double price, int qty, std::string size) : 
    Product("clothing", name,  price,  qty)
{
    brand_ = brand;
    size_ = size;
}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> toWords;
    std::set<std::string> toWordsG;
    toWords = parseStringToWords(Product::getName());
    // std::cout << "BRAND FOR CLOTHING" << brand_ << std::endl;
    toWordsG = parseStringToWords(brand_);

    return setUnion(toWords, toWordsG);
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
    bool match = false;
    bool brandMatch = false;
    for(unsigned int i = 0; i < searchTerms.size(); i++){
        if(Product::getName() == searchTerms[i]){
            match = true;
        }
        if(brand_ == searchTerms[i]){
            brandMatch = true;
        }
    }
    if(brandMatch && match){
        return true;
    }
    else{
        return false;
    }
}

std::string Clothing::displayString() const{
    std::string retval;
    std::string d = std::to_string(Product::getPrice());
    retval = Product::getName() + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + d + " " + std::to_string(Product::getQty()) + " left.";
    return retval;
}

void Clothing::dump(std::ostream& os) const{
    Product::dump(os);
    os << size_ << std::endl;
    os << brand_ << std::endl;
   
    

}
