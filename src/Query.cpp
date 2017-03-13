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
// Takes in a pointer to the Knowledge Base and a string representative of the similar
// relationship.
vector<Fact*>* Query::listFact(KB* Knowledge, string factKey) {
	vector<Fact*>* result = Knowledge->Find(factKey);
	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
	return result;
}

//SIMPLE RULE-------------------------------------------------------------------

//helper function to get rid of duplicates
vector<Fact*> Query::concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB) {
	vector<Fact*> result;
	bool found = false;
	result = preventDupes(resultA, result);
	result = preventDupes(resultB, result);

	return result;
}

//----------------------------------Part 3: evaluate--------------------------------------//

//If the Rule is valid, adds a Fact representative of the Rule's validity to the KB
//MAKE SURE THAT ACTORS FOR EACH COMPONENT ARE MUTUALLY EXCLUSIVE
//Input: Component vector from Rules
//Output: Returns truth value of the rule
bool Query::enact(Rule * r, vector<string> components, KB * kb){
  if(r->evaluate(components)){
    if(kb->Add(new Fact(r->name, r->actors))){
      //Run query.inference here
    }
    return true;
  }
  return false;
}

//------------------------------Inferencing-----------------------------------------------//

//Check if AND or OR
//if OR, only check the ones with the right number of actors.

void CreateVarBoundsMaster(int iterate, vector<string> varMapping){
	//Create map fcn will populate
	for(int i=0; i<varMapping.size(); i++){
		vector<string> temp;
		map[varMapping.at(i)] = temp;
	}
	for(int i=0; i<iterate<i++){

	}
}

//create bounds for vars
map<string, vector<string> > CreateVarBounds(vector<Fact*>* Facts, vector<string> varMapping){
	map<string, vector<string> > VarBounds;

	//iterate through list of facts
	for(int i=0; i<Facts[0]->components.size(); i++){
		//iterate through list of actors in facts
		for(int j=0; j<sizeOf; j++){
			//Create pointer to vector pertaining to proper var
			vector<string>* temp = VarBounds[varMapping.at(j)];
			temp.push_back(Facts->at(i)->components.at(j));
		}
	}
return VarBounds;
}

//Grandfather->vector
//[0]: [John, John]
//[1] : [Bob, Mary]

map<string, vector<string>> * Query::inference(vector<string> newFact){ //(Father,bob, " ", jerry,etc)
	string relation = newFact[0];
	//int reqSize = newFact.size() - 1;
	vector<string> actors = newFact.erase(1, newFact.end());
	map<string, vector<string>>* output;
	//SORT OUT LOGIC OPS HERE
	vector<string> path;

	if (kb->FactMap.count(relation) >= 1 || rb.rules.count(relation) >= 1) {
		Rules * r = rb->rules[relation];
		if (ruleEvaluate(r)) {
			//split components of r
			for (int j = 0; j < r->components.size(); j++) {
				vector< vector<string> >path = traverse(actors, *kb.FactMaps[r->components[j][0]]);
				for (int i = 0; i < path.size(); i++) {
					output[relation][i].push_back(&path[i]);
				}//get rid of copies here
			}
		}
	}
	return output;
}
//["Father", "$X", "$Y", 0, "Mother", "$X", "$Y"]
bool Query::ruleEvaluate(Rules * r, vector<string> actors) {
	if (kb->evaluate(r->name, actors)) return true;
	vector<bool> truthValues;
	int ops;
	else {
		//call helper function
		bool finalValue;
		for(int i = 0; i < r->components.size(); i++) {
			ops = r->ops;
			truthValues.push_back(ruleEvalHelper(r->components[i][0], actors));
			else continue;
		}
		finalValue = truthValues[0];
		for (int i = 1; i < r->truthValues.size(); i++) {
			if (ops == 0) finalValue = finalValue || truthValues[i];
			else finalValue = finalValue && truthValues[i];
		}
		return finalValue;
	}
}

bool Query::ruleEvalHelper(string name, vector<string> actors) {
	if (kb->evaluate(name, actors)) return true;
	else {
		if (rb->rules.count(name) == 1)return true; //Assume RB contains only uniquely named rules
		else return false;
	}
}

vector< vector<string> > Query::traverse(vector<string> actors, vector<string> actorList) {
	vector< vector<string> > result;
	int initSize = actorList[0].size();
	for (int i = 0; i < initSize; i++) {
		vector<string> path;
		for (int j = 0; j < actorList.size(); j++) {
			if (actorList[j].size() < initSize) break;
			else path.push_back(actorList[j][i]);
			result.push_back(path);
			}
		}
		return result;
	}

//Prints the results of the query to terminal
//Input: void
//Output: void
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}
