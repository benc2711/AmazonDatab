#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include <map>
#include "user.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;
    std::map<User*, std::vector<Product*>> cartMap;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if (cmd == "ADD"){
                string term;
                int hitIndex;
                ss >> term;
                ss >> hitIndex;
                //Check for invalid username
                if(ds.userNames_.find(term) == ds.userNames_.end()){
                    cout << "Invalid Username" << endl;
                }
                else if(!hits[hitIndex]){
                    cout << "Invalid Product Index" << endl;
                }
                //Check for invalid hit index
                //Get the user from our user set 
                User* current = ds.searchUser(term);
                cartMap[current].push_back(hits[hitIndex]);


                //Then map that user to the product being added 


            }
            else if (cmd == "VIEWCART"){
                string uName;
                User* current = ds.searchUser(uName);
                ss >> uName;
                for(int i = cartMap[current].size() -1; i >=0; i--){
                    cout << cartMap[current][i] << endl;
                }

            }
            else if(cmd == "BUYCART"){
                string uName;
                User* current = ds.searchUser(uName);
                ss >> uName;
                std::vector<Product*> currentCart = cartMap[current];
                for(int i = currentCart.size() -1; i >=0; i--){
                    if(currentCart[i]->getQty() > 0){
                        if(current->getBalance() > currentCart[i]->getPrice()){
                            currentCart[i]->subtractQty(1);
                            ds.updateProds(currentCart[i], 1);
                            current->deductAmount(currentCart[i]->getPrice());
                            ds.updateUsers(current, currentCart[i]->getPrice());
                            
                        }
                    }
                }
            }
            
	    /* Add support for other commands here */




            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
