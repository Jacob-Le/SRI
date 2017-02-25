//Main building block of the rule system

#include <stdlib.h>
#include "Fact.h"

//Constructor
Fact::Fact(std::vector<std::string> a, std::string name){
  std::vector<std::string> actors = a;
  std::string Relationship = name;
}

bool Fact::evaluate(std::vector<std::string> actors){
  //if(this == KB.fetch(actors))
  return true;
}
