//Predicate.h
#include<vector>
#include<cstdarg>
#include<string>
using namespace std;

class Predicate{ //AKA FACT OR RULE, DEPENDING ON WHAT RULE IT IS CALLED IN
  public:
  string Relationship;
  std::vector<string> Actors;
 
  Predicate(string relationship, int argCount, ... );
  bool evaluate();
};  