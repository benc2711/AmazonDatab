#include "datastore.h"
#include "mydatastore.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <string.h>
#include "util.h"
#include "product.h"
#include <map>


    void MyDataStore::addProduct(Product* p){
        prods_.insert(p);
        prodNames_.insert(p->getName());
    }

    /**
     * Adds a user to the data store
     */
     void MyDataStore::addUser(User* u){
        users_.insert(u);
        userNames_.insert(u->getName());
     }
    User* MyDataStore::searchUser(std::string uName){
        std::set<User*>::iterator itr; 
            for(itr = users_.begin();itr != users_.end(); itr++){
                if((*itr)->getName() == uName){
                    return *itr;
                }
            }
        return NULL;
    }
    void MyDataStore::updateUsers(User* u, int deduction){
        std::set<User*>::iterator itr = users_.find(u);
        (*itr)->deductAmount(deduction); 
    }
    void MyDataStore::updateProds(Product* p, int deduction){
        std::set<Product*>::iterator itr = prods_.find(p);
        (*itr)->subtractQty(deduction);
    }


    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
     std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
        std::set<std::string> termSet;
        for(unsigned int i =0; i<terms.size(); i++){
            termSet.insert(terms[i]);
        }
        std::vector<Product*> prodVec;
        if(type == 1){
            std::set<std::string> productSet = setUnion(prodNames_, termSet);
            //Itterate over product set match names with product id and then push that to vector
            std::set<Product*>::iterator itr; 
            for(itr = prods_.begin();itr != prods_.end(); itr++){
                if(productSet.find((*itr)->getName()) != productSet.end()){
                    prodVec.push_back(*itr);

                }
            }
            return prodVec;
        }
        else if(type == 0){
            std::set<std::string> productSet = setIntersection(prodNames_, termSet);
            //Itterate over product set match names with product id and then push that to vector
            std::set<Product*>::iterator itr; 
            for(itr = prods_.begin();itr != prods_.end(); itr++){
                if(productSet.find((*itr)->getName()) != productSet.end()){
                    prodVec.push_back(*itr);

                }
            }
            return prodVec;
        }
        
     }

    /**
     * Reproduce the database file from the current Products and User values
     */
     void MyDataStore::dump(std::ostream& ofile){
        ofile << "<Products>\n";
        std::set<Product*>::iterator itr; 
        for(itr = prods_.begin();itr != prods_.end(); itr++){
                (*itr)->dump(ofile);
                ofile << "\n";
            }
        ofile << "</products>\n";
        std::set<User*>::iterator its; 
        ofile << "<users>\n";
        for(its = users_.begin();its != users_.end(); its++){
                (*its)->dump(ofile);
                ofile << "\n";
            }
         ofile << "</users>\n";
     }
