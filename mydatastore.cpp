#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "mydatastore.h"
#include "util.h"
#include "clothing.h"
#include "book.h"
#include "movie.h"

using namespace std; 

MyDataStore::~MyDataStore()
{
    std::set<Product*>::iterator product_it; 
    for(product_it = products_.begin() ; product_it != products_.end() ; ++product_it)
    {
        delete *product_it;
    }
    std::map<std::string, User*>::iterator user_it; 
    for(user_it = usernameToUsers_.begin() ; user_it != usernameToUsers_.end() ; ++user_it)
    {
        delete user_it ->second;
    }
}
void MyDataStore::addProduct(Product *p)
{
    products_.insert(p);
    set<string> keywords = p->keywords();
    set<string>::iterator it;
    for (it = keywords.begin(); it != keywords.end(); ++it)
    {
        keywordsToProducts_[*it].insert(p);
    }
}
void MyDataStore::addUser(User* u)
{
    string username = u->getName();
    usernameToCarts_[username];
    usernameToUsers_[username] = u; // create new username pair with user
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::vector<Product*> searched_products;
  std::set<Product*> searched_product_set ; 
  if (terms.size() == 0)
  {
    return searched_products;
  }
  else if (terms.size() == 1)
  {
    if (keywordsToProducts_.find(terms[0]) != keywordsToProducts_.end())
    {
      set<Product *>::iterator product_it;
      for (product_it = keywordsToProducts_[terms[0]].begin(); product_it != keywordsToProducts_[terms[0]].end(); ++product_it)
      {
        searched_products.push_back(*product_it);
      }
    }
    return searched_products;
  }

  // more terms
  if (type == 0)
  {
    if (keywordsToProducts_.find(terms[0]) != keywordsToProducts_.end())
    {
      searched_product_set = keywordsToProducts_[terms[0]]; // set of products of the first term
      for (size_t i=1; i<terms.size(); i++)
      {
        if (keywordsToProducts_.find(terms[i]) != keywordsToProducts_.end())
        {
          searched_product_set = setIntersection(keywordsToProducts_[terms[i]], searched_product_set);
        }
        else
        {
          return searched_products;
        }
      }
    }
    else
    {
      return searched_products;
    }
    set<Product*>::iterator searched_it;
    for (searched_it = searched_product_set.begin(); searched_it != searched_product_set.end(); ++searched_it)
    {
      searched_products.push_back(*searched_it);
    }
    return searched_products;
  }
  else // or
    {
        for(int i = 0; i < terms.size(); ++i)
        {
          if(keywordsToProducts_.find(terms[i]) != keywordsToProducts_.end())
          {
            searched_product_set = setUnion(keywordsToProducts_[terms[i]], searched_product_set);
          }
        }
        set<Product*>::iterator searched_it;
        for (searched_it = searched_product_set.begin(); searched_it != searched_product_set.end(); ++searched_it)
        {
            searched_products.push_back(*searched_it);
        }
        return searched_products;
    }
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl; 
    std::set<Product*>:: iterator product_it;
    for(product_it = products_.begin() ; product_it != products_.end(); ++product_it)
    {
        (*product_it) -> dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    std::map<std::string, User*>::iterator user_it;
    for(user_it = usernameToUsers_.begin(); user_it != usernameToUsers_.end() ; ++user_it)
    {
        (user_it->second) -> dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addCart(std::string username, Product* p )
{
    std::map<std::string,std::deque<Product*>>::iterator it = usernameToCarts_.find(username);
    if(it != usernameToCarts_.end())
    {
        it->second.push_back(p);
    }
    else
    {
        cout << "Invalid request" << endl;
    }
}
std::deque<Product*> MyDataStore::viewCart (std::string username)
{
    std::map<std::string,std::deque<Product*>>::iterator it = usernameToCarts_.find(username);
    if(it == usernameToCarts_.end())
    {
        cout << "invalid username" << endl;
        throw std::invalid_argument("invalid username");
    }
    else
    {
        return (it->second);
    }
}
void MyDataStore::buyCart(std::string username)
{
    map<string,User*>::iterator user_it = usernameToUsers_.find(username);
    if (user_it == usernameToUsers_.end())
    {
        cout << "Invalid username" << std::endl;
        return;
    }
    map<string,deque<Product*>>::iterator userbuying_it = usernameToCarts_.find(username);
    if(userbuying_it != usernameToCarts_.end())
    {   
        deque<Product*> user_cart_product = userbuying_it -> second;
        deque<Product*>::iterator product_it;
        for(product_it = user_cart_product.begin() ; product_it != user_cart_product.end(); ++product_it)
        {   
            if(user_it->second->getBalance() > (*product_it)->getPrice() && ((*product_it) ->getQty() > 0))
            {
                (*product_it) ->subtractQty(1); 
                user_it -> second -> deductAmount((*product_it)->getPrice());
                
                deque<Product*>::iterator remove_it;
                remove_it = std::remove(userbuying_it->second.begin(),userbuying_it->second.end(),*product_it);
                userbuying_it->second.erase(remove_it); 
            }
        }
    }
    else
    {
        cout << "Invalid username" << endl;
    }
}
