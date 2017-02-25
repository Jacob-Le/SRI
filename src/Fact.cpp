//Main building block of the rule system
#include <iostream>
#include <stdlib.h>
#include "Fact.h"

//Constructor
Fact::Fact(std::vector<std::string> a, std::string name){
  actors = a;
  Relationship = name;
}

//No reference to KB exists yet. 
/*bool Fact::evaluate(std::vector<std::string> actors){
  try{
    if(this == KB.fetch(Relationship, actors)) return true;
  }
  catch(std::invalid_argument){
    std::cout << "ERROR: Fact does not exist" << "\n" << endl;
    return false;
  }
  return false;
}*/

void Fact::toString(){
	std::cout<< Relationship <<"(";
	for(int i=0; i < actors.size(); i++) std::cout << actors[i] <<", ";
	std::cout<<")\n";
}
