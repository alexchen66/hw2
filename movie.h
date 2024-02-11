#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include "product.h"
#include <sstream>

class Movie : public Product{
public:
  Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating);
  ~Movie();

  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

protected:
  const std::string genre_;
  const std::string rating_;
};
#endif