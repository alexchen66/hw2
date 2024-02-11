#include "book.h"
#include "util.h"
#include <iomanip>
using namespace std;

Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author)
  : Product("book", name, price, qty), isbn_(isbn), author_(author)
  {
  }
Book::~Book()
{
}

std::set<std::string> Book::keywords() const
{
  string temp = name_;
  string s_temp = author_;
  temp = convToLower(temp);
  s_temp = convToLower(s_temp);
  set<std::string> book_keywords = parseStringToWords(temp);
  set<std::string> temp_keywords = parseStringToWords(s_temp);
  book_keywords.insert(temp_keywords.begin(), temp_keywords.end());
  book_keywords.insert(isbn_);
  return book_keywords;
}
std::string Book::displayString() const
{
  ostringstream os;
  os << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left.";
  return os.str();
}
void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << std::fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}