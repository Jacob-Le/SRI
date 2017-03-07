//Query.cpp
/*
	Query handles interactions between databases. Allow databases to query each other
	for truth values of targetted facts or rules.
*/
#include<iostream>
#include<cstdio>

#include "Query.h"

using namespace std;

vector<Fact*> Results;

Query::Query(KB * knowledge, RB * rules) {
	kb = knowledge;
	rb = rules;
}

//FACT--------------------------------------------------------------------------
// Returns a pointer to a list (vector) of Fact pointers with a similar relationship
//from the Knowledge Base.
// Input: Takes in a pointer to the Knowledge Base and a string
//Output: A pointer to a list (vector) of Fact pointers
// vector<Fact*>* Query::listFact(KB* Knowledge, string factKey) {
// 	vector<Fact*>* result = Knowledge->Find(factKey);
// 	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
// 	return result;
// }

//helper function to get rid of duplicates
//Input: Vector of facts resultA and resultB
//Output: Vector of combined facts with dupblicates eliminated
// vector<Fact*> Query::concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB) {
// 	vector<Fact*> result;
// 	bool found = false;
// 	result = preventDupes(resultA, result);
// 	result = preventDupes(resultB, result);
// 	return result;
// }

//Helper function to help concatenate. Removes duplicates.
//Input: vector of facts A and B
//Output: vector of facts with duplicates eliminated
// vector<Fact*> Query::preventDupes(vector<Fact*>* A, vector<Fact*> B){
//
// 	vector<bool> diffChecker;
// 	bool flag = true;
// 	for(int i=0; i<A->size(); i++){
// 		if(B.size() != 0){
// 			//cout<<"Checking for differences"<<endl;
// 				for(int j=0; j<B.size(); j++){ //Iterating through Vector
// 					if(B.at(j)->components.size() == A->at(i)->components.size()){ //if they have the same amount of components
// 						diffChecker.assign(A->at(i)->components.size(),false); //Initialize all to false
// 						for(int k = 0; k<B.at(j)->components.size();k++){ //Iterate through components
// 							if(B.at(j)->components.at(k) != A->at(i)->components.at(k)){ //If actor pair is different
// 								diffChecker.at(k) = true; //mark difference
// 								break;
// 							}
// 						}
// 						bool factMatch = false;
// 						for(int k =0; k<diffChecker.size(); k++){ //Iterate through diffChecker
// 							if(diffChecker.at(k)==true){ //If there is a difference
// 								factMatch = false;
// 								break;
// 							}
// 							factMatch=true; //THIS IS FALSE IF THERE IS A DIFFERENCE
// 						}
// 						if(factMatch == true){ //if it matches
// 							flag = false;
// 							break;
// 						}
// 					}
// 				}
// 				if(flag == true) B.push_back(A->at(i));
// 				diffChecker.clear();
// 		}else{
// 			B.push_back(A->at(i));
// 		}
// 	}
// }

//Prints the results of the query to terminal
//Input: void
//Output: void
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}


//----------------------------------Part 3: evaluate--------------------------------------//

//If the Rule is valid, adds a Fact representative of the Rule's validity to the KB
//MAKE SURE THAT ACTORS FOR EACH COMPONENT ARE MUTUALLY EXCLUSIVE
//Input: Component vector from Rules
//Output: Returns truth value of the rule
bool Query::enact(Rule * r, vector<string> components){
  if(r->evaluate(components)){
    if(kb->Add(new Fact(r->name, r->actors))){
      //Run query.inference here
    }
    return true;
  }
  return false;
}
