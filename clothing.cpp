#include "clothing.h"
#include "util.h"
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand)
  : Product("clothing", name, price, qty), size_(size), brand_(brand)
  {
  }
Clothing::~Clothing()
{
}

std::set<std::string> Clothing::keywords() const
{
  string temp = name_;
  string s_temp = brand_;
  temp = convToLower(temp);
  s_temp = convToLower(s_temp);
  set<std::string> clothing_keywords = parseStringToWords(temp);
  set<std::string> temp_keywords = parseStringToWords(s_temp);
  clothing_keywords.insert(temp_keywords.begin(), temp_keywords.end());
  return clothing_keywords;
}
std::string Clothing::displayString() const
{
  ostringstream os;
  os << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
  return os.str();
}
void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << std::fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
