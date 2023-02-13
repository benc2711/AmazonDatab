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

MyDataStore::~MyDataStore(){
  std::set<User*>::iterator itr; 
  for(itr = users_.begin();itr != users_.end(); itr++){
    delete *itr;
  }
  std::set<Product*>::iterator it; 
  for(it = prods_.begin();it != prods_.end(); it++){
    delete *it;
  }
  // std::map<std::string, std::set<Product*>>::iterator is; 
  // for(is = keywordmap.begin();is != keywordmap.end(); is++){
  //   std::set<Product*>::iterator iss;
  //   for(iss = is->second.begin(); iss != is->second.end(); iss++){
  //     delete *iss;
  //   }
  // }
  // std::map<std::string, std::vector<Product*>>::iterator its; 
  // for(its = cartMap.begin();its != cartMap.end(); its++){
  //  for(int i =0; i< (*its).second.size(); i++){
  //    delete its->second[i];
  //  }
  // }
}



    void MyDataStore::addProduct(Product* p){
        // std::cout << "SEMI WORK" << std::endl;
        prods_.insert(p);
        prodNames_.insert(p->getName());
        std::set<std::string> keywords = p->keywords();
        std::set<std::string>::iterator it;
        for(it = keywords.begin(); it != keywords.end(); it++){
          keywordmap[convToLower(*it)].insert(p);
        }
      // std::cout << "WHO" << std::endl;
    }

    /**
     * Adds a user to the data store
     */
     void MyDataStore::addtocart(std::string uname, Product* p){

       if(userNames_.find(convToLower(uname)) == userNames_.end()){
          std::cout << "Invalid Username" << std::endl;
          return;
        }
        cartMap[convToLower(uname)].push_back(p);
     }

     void MyDataStore::viewcart(std::string uname){
      // std::cout << cartMap[uname][0]->displayString() << std::endl;
      if(cartMap.find(convToLower(uname)) != cartMap.end()){
        // std::vector<Product*>::iterator him;
        int count = 1;
        // std::cout << "CARTMAP SIZE: " << cartMap[uname].size() << std::endl;
        for(unsigned int i =0; i < cartMap[convToLower(uname)].size(); i++){
        //  std::cout << "RAN" << std::endl;
          std::cout << "Item " << std::to_string(count) << std::endl;
          std::cout << cartMap[convToLower(uname)][i]->displayString() << std::endl;
          count++;
        }
      }
      else{
        std::cout << "INVALID username" << std::endl;
      }
     }

     void MyDataStore::buycart(std::string uname){
      if(cartMap.find(convToLower(uname)) == cartMap.end()){
        std::cout << "Invalid username" <<std::endl;
      }
       for(int i = cartMap[uname].size() -1; i >=0; i--){
         std::vector<Product*> currentCart = cartMap[uname]; 
                    if(currentCart[i]->getQty() > 0){
                      User* current = searchUser(uname);

                        if(current->getBalance() > currentCart[i]->getPrice()){
                            currentCart[i]->subtractQty(1);
                            // updateProds(currentCart[i], 1);
                            
                            current->deductAmount(currentCart[i]->getPrice());
                            // cartMap[uname].erase(currentCart.end() - i - 1);
                            // updateUsers(uname), currentCart[i]->getPrice());
                            
                        }
                    }
                }
     }
     void MyDataStore::addUser(User* u){
        users_.insert(u);
        userNames_.insert(convToLower(u->getName()));
        
     }
    User* MyDataStore::searchUser(std::string uName){
        std::set<User*>::iterator itr; 
            for(itr = users_.begin();itr != users_.end(); itr++){
                if(convToLower((*itr)->getName()) == convToLower(uName)){
                    return *itr;
                }
            }
        return NULL;
    }
    void MyDataStore::updateUsers(std::string uname, double deduction){
        searchUser(convToLower(uname))->deductAmount(deduction); 
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
        // std::set<std::string> termSet;
        std::set<Product*> prodst;
        // std::cout << "TERMS" << std::endl;
        std::map<std::string, std::set<Product*>>::iterator its;

        // std::cout << "Keyword map Size: " << keywordmap.size() << std::endl;
        // for(its = keywordmap.begin(); its!= keywordmap.end(); its++){
        //   std::cout << its->first << std::endl;
        // }
        prodst = keywordmap[terms[0]];
        for(unsigned int i =0; i<terms.size(); i++){
          // std::cout << terms[i] << std::endl;
          std::string currterm = convToLower(terms[i]);
          // std::cout << currterm << std::endl;
          if(keywordmap.find(currterm) != keywordmap.end()){
            // std::cout << "RAND THIS AT ALL " << std::endl;
            if(type == 1){
              // std::cout << "Ran Union" << std::endl;
              prodst = setUnion(prodst, keywordmap[currterm]);
            }
            if(type == 0){
              // std::cout << "Ran Intersection" << std::endl;
              prodst = setIntersection(prodst, keywordmap[currterm]);
            }
          }
            
        }
          // std::cout << "Made past this 1 " << std::endl;


        

        // std::cout << "TERMSET SIZE" << termSet.size() << std::endl;
        std::vector<Product*> prodVec(prodst.size());
        copy(prodst.begin(), prodst.end(), prodVec.begin());



        // std::set<Product*>::iterator itr;
        // for(itr = prodst.begin(); itr != prodst.end(); itr++){
        //   prodVec.push_back(*itr);
        //   // std::cout << (*itr)->displayString() << std::endl;
        // }
        // std::cout << "PRODVEC 0 Index" << prodVec[0]->getName() << std::endl;
        //Or search
        // std::cout << "PROD VEC SIZE: " << prodst.size() << std::endl;
        
        //And search
        
        return prodVec;
        
        
     }

    /**
     * Reproduce the database file from the current Products and User values
     */
     void MyDataStore::dump(std::ostream& ofile){
        ofile << "<products>\n";
        std::set<Product*>::iterator itr; 
        for(itr = prods_.begin();itr != prods_.end(); itr++){
                (*itr)->dump(ofile);
                //ofile << "\n";
            }
        ofile << "</products>\n";
        std::set<User*>::iterator its; 
        ofile << "<users>\n";
        for(its = users_.begin();its != users_.end(); its++){
                (*its)->dump(ofile);
                //ofile << "\n";
            }
         ofile << "</users>\n";
     }
