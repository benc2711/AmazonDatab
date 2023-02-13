#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include "product.h"


class MyDataStore: public DataStore{
    public:
      ~MyDataStore();
        void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
        void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        void addtocart(std::string uname, Product* p);
        void viewcart(std::string uname);
        void buycart(std::string uname);

    /**
     * Reproduce the database file from the current Products and User values
     */
        void dump(std::ostream& ofile);
        User* searchUser(std::string uName);
        void updateUsers(std::string uname, double deduction);
        void updateProds(Product* p, int deduction);

        //We need to add product and 
        std::set<User*> users_;
        std::set<Product*> prods_;
        std::set<std::string> prodNames_;
        std::set<std::string> prodKeyWords_;
        std::map<std::string, std::set<Product*>> keywordmap;
        std::set<std::string> userNames_;
        std::map<std::string, std::vector<Product*>> cartMap;

        
};

#endif
