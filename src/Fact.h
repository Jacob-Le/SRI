//Main building block of rule system

#include <stdlib.h>

class Fact{
private:
  std::string actor1;
  std::string actor2;
public:
  Fact(std::string a_1, std::string a_2, std::string r);
  //copy and move constructors

  std::string Relationship;
  std::pair getActors();

  //Operator overloads
}
