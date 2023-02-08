#include "product.h"
#include "clothing.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>


Clothing::Clothing(const std::string brand, const std::string name, double price, int qty, std::string size) : 
    Product("clothing", name,  price,  qty)
{
    brand_ = brand;
    size_ = size;
}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> retval;
    retval.insert(brand_);
    retval.insert(Product::getName());
    return retval;
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
    retval = "Name: " + Product::getName() + " Price: " + d + " Quantity " + std::to_string(Product::getQty()) + " Catagory: Clothing " + "Brand: " + brand_;
    return retval;
}

void Clothing::dump(std::ostream& os) const{
    std::string retval;
    std::string d = std::to_string(Product::getPrice());
    os << "clothing\n"  << Product::getName()  << "\n" << d  << "\n" << std::to_string(Product::getQty()) << "\n" << size_ << "\n" << brand_ << "\n";
    

}
