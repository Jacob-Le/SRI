//Main building block of rule system
#include "Predicate.cpp"
#include <stdlib.h>
<<<<<<< HEAD
using namespace std;

class Fact : Predicate {
  public:
  string Relationship;
  vector<string> actors;

  Fact(vector<string>, string name);
  bool evaluate(vector<string>);
  string toString();
};

