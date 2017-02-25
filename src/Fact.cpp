//Main building block of the rule system

#include <stdlib.h>
#include <vector>
#include "Fact.h"
using namespace std;

//Constructor
Fact::Fact(std::vector<std::string> a, std::string name){
  std::vector<std::string> actors = a;
  std::string Relationship = name;
}

bool Fact::evaluate(std::vector<std::string> actors){
  try{
    if(this == KB.fetch(Relationship, actors)) return true;
  }
  catch(std::invalid_argument){
    std::cout << "ERROR: Fact does not exist" + "\n" << endl;
    return false;
  }
  return false;
}
