#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include "product.h"
#include <sstream>

class Clothing : public Product{
public:
  Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand);
  ~Clothing();

  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

protected:
  const std::string size_;
  const std::string brand_;
};
#endif