//Main building block of rule system

#include <stdlib.h>
#include <vector>
#include "Predicate.h"
using namespace std;

typedef struct Fact : Predicate {

  std::string Relationship;
  std::vector<std::string> actors;

  Fact(std::vector<std::string> r, std::vector<std::string> name);
  bool evaluate(std::vector<std::string> actors);

};
