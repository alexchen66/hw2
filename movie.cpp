#include "movie.h"
#include "util.h"
#include <iomanip>

using namespace std;

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating)
  : Product("movie", name, price, qty), genre_(genre), rating_(rating)
  {
  }
Movie::~Movie()
{
}

std::set<std::string> Movie::keywords() const
{
  string temp = name_;
  string s_temp = genre_;
  temp = convToLower(temp);
  set<std::string> movie_keywords = parseStringToWords(temp);
  set<std::string> temp_keywords = parseStringToWords(s_temp);
  movie_keywords.insert(temp_keywords.begin(), temp_keywords.end());
  return movie_keywords;
}
std::string Movie::displayString() const
{
  ostringstream os;
  os << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
  return os.str();
}
void Movie::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << std::fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}