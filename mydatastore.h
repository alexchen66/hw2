#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore : public DataStore {

    public :
    ~MyDataStore();
    void addProduct(Product *p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addCart(std::string username, Product* p );
    std::deque<Product*> viewCart (std::string username);
    void buyCart(std::string username);

    private :
    std::set<Product*> products_; 
    std::map<std::string, std::deque<Product*>> usernameToCarts_; // note: use deque instead of vector
    std::map<std::string, User*> usernameToUsers_; 
    std::map<std::string,std::set<Product*>> keywordsToProducts_;

};



#endif 