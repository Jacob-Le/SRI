//Main building block of the rule system

#include <stdlib.h>
#include "Fact.h"

//Constructor
Fact::Fact(std::string a_1, std::string a_2, std::string r){
  actor1 = a_1;
  actor2 = a_2;
  Relationship = r;
}

//Returns a tuple pair that contains the names of the actors involved in the fact
std::pair<std::string, std::string> Fact::getActors(){
  std::pair <std::string, std::string> actors (actor1, actor2);
  return actors;
}
