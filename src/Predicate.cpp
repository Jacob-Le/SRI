//Predicate.cpp
/*
	Definitions of predicates, rules, and facts are stored here, along with definitions
	of their assosciated functions.
*/
#include <iostream>
#include<math.h>

#include "Predicate.h"

using namespace std;

//--------------------------------------------Predicate--------------------------------------//
//Predicate is the base struct that Fact and Rule inherit from.

//Swaps the member values between two Predicates
//Input: Two target predicate addresses
//Output: Void.
void Predicate::p_swap(Predicate & one, Predicate & two){
  using std::swap;
  swap(one.name, two.name);
  swap(one.components, two.components);
}

//Default Constructor
Predicate::Predicate(){
  name = "";
  components;
}

//Constructor for Predicate, the base class from which both Fact and Rule extend from.
//Takes in a string as a name, and a variable number of string arguments as Actors
Predicate::Predicate(string n, vector<string> actors){
  name = n;
  components = actors;
}

//Copy constructor
Predicate::Predicate(const Predicate & p){
  name = p.name;
  components = p.components;
}

//Move constructor
Predicate::Predicate(Predicate && p) : Predicate(){
  p_swap(*this, p);
}

//Destructor
Predicate::~Predicate(){

}

//Evaluate function.
//Input: String vector of components
//Output: boolean representing Predicate truth value.
bool Predicate::evaluate(vector<string> components){
  return true;
}

//Operator overloads for copy and move assignment
Predicate& Predicate::operator = (Predicate p){
  p_swap(*this, p);
  return *this;
}

Predicate& Predicate::operator = (Predicate && p){
  p_swap(*this, p);
  return *this;
}

//AND operator
//Input: bool a, bool b
//Output: AND value of a and b
bool Predicate::AND(bool a, bool b) {
	return a&&b;
}

//OR operator
//Input: bool a, bool b
//Output: OR value of a and b
bool Predicate::OR(bool a, bool b) {
	return a||b;
}

string Predicate::toString(){
	string output;
    output = output + name +"(";
    for(int i=0; i < components.size(); i++){
        output += components[i];
        if(i+1 != components.size()) output += ", ";
    }
    output += ") ";
    return output;
}




