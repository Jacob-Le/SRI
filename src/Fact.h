//Main building block of rule system

#include <stdlib.h>
#include<string>
using namespace std;

class Fact{
private:
  string actor1;
  string actor2;
public:
  Fact(string a_1, string a_2, string r);
  //copy and move constructors

  string Relationship;
  std::pair<string, string> getActors();

  //Operator overloads
};
