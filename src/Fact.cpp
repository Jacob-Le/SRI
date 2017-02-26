//Main building block of the rule system
#include <iostream>
#include <stdlib.h>
#include "Fact.h"
using namespace std;

//Constructor
Fact::Fact(vector<string> a, string name){
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

//Converts entire fact into a string
string Fact::toString(){
	string output = "";
	output = output + Relationship +"(";
	for(int i=0; i < actors.size(); i++){
		output += actors[i]; 
		if(i+1 != actors.size()) output += ", ";
	}
	output += ")\n";
	return output;
}