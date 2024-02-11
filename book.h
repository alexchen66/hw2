#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include "product.h"
#include <sstream>

class Book : public Product{
public:
  Book(const std::string name, double price, int qty, const std::string isbn, const std::string author);
  ~Book();

  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

protected:
  const std::string isbn_;
  const std::string author_;
};
#endif