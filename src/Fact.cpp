//Main building block of the rule system

#include <stdlib.h>

//Constructor
Fact::Fact(std::string a_1, std::string a_2, std::string r){
  std::string Actor1 = a_1;
  std::string Actor2 = a_2;
  std::string Relationship = r;
}

//Returns a tuple pair that contains the names of the actors involved in the fact
std::pair Fact::getActors(){
  std::pair <std::string, std::string> actors (Actor1, Actor2)
  return actors;
}
