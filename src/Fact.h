//Main building block of rule system
#include "Predicate.cpp"
#include <stdlib.h>

class Fact : Predicate {
  public:
  std::string Relationship;
  std::vector<std::string> actors;

  Fact(std::vector<std::string>, std::string name);
  bool evaluate(std::vector<std::string>);
  void toString();
};
