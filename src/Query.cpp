//Query.cpp
/*
	Query handles interactions between databases. Allow databases to query each other
	for truth values of targetted facts or rules.
*/
#include<iostream>
#include<cstdio>

#include "Query.h"

using namespace std;

//vector<Fact*> Results; REPLACE?

Query::Query(KB * knowledge, RB * rules) {
	kb = knowledge;
	rb = rules;
}
//FACT--------------------------------------------------------------------------
// Returns a pointer to a list (vector) of Fact pointers with a similar relationship
//from the Knowledge Base.
// Takes in a pointer to the Knowledge Base and a string representative of the similar
// relationship.
/*
vector<Fact*>* Query::listFact(KB* Knowledge, string factKey) {
	vector<Fact*>* result = Knowledge->Find(factKey);
	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
	return result;
}*/

//SIMPLE RULE-------------------------------------------------------------------

//helper function to get rid of duplicates
/*vector<Fact*> Query::concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB) {
	vector<Fact*> result;
	bool found = false;
	result = preventDupes(resultA, result);
	result = preventDupes(resultB, result);

	return result;
}*/

//----------------------------------Part 3: evaluate--------------------------------------//

//If the Rule is valid, adds a Fact representative of the Rule's validity to the KB
//MAKE SURE THAT ACTORS FOR EACH COMPONENT ARE MUTUALLY EXCLUSIVE
//Input: Component vector from Rules
//Output: Returns truth value of the rule
/*bool Query::enact(Rule * r, vector<string> components, KB * kb){
  if(r->evaluate(components)){
    if(kb->Add(new Fact(r->name, r->actors))){
      //Run query.inference here
    }
    return true;
  }
  return false;
}*/

//------------------------------Inferencing-----------------------------------------------//

//Check if AND or OR
//if OR, only check the ones with the right number of actors.

/*
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
}*/

//Grandfather->vector
//[0]: [John, John]
//[1] : [Bob, Mary]

map<string, vector<string> > Query::inference(vector<string> newFact){ //(Father,bob, " ", jerry,etc)
	string relation = newFact[0];
	//int reqSize = newFact.size() - 1;
	vector<string> actors;
	cout << "Entered Inference" << endl;
	for (int i = 1; i < newFact.size(); i++) {
		actors.push_back(newFact[i]);
	}

	map<string, vector<string>> output;
	//SORT OUT LOGIC OPS HERE
	vector<string> path;

	if (rb->rules.count(relation) == 1) {
		cout << "Found in KB and RB! Evaluating assosciated Rule" << endl;
		Rule * r = rb->rules[relation];
		if (ruleEvaluate(r, actors)) {
			cout << "Rule Evaluated! Iterating now!" << endl;
			//split components of r
			string temp;
			for (int j = 0; j < r->components.size(); j++) {
				temp = r->components[j][0];
				vector< vector<string> >path = traverse(actors, kb->FactMap[temp]);
			}
			for (int i = 0; i < path.size(); i++) {
				output[relation].push_back(path[i]);//get rid of copies here
			}
		}//somehow return an empty output?
	}
	cout << "Iteration Complete! Output:" << endl;
	for (int i = 0; i < output.size(); i++) {
		cout << output[relation][i] << endl;
	}
	output = removeDoubles(output);
	return output;
}
//["Father", "$X", "$Y", 0, "Mother", "$X", "$Y"]
bool Query::ruleEvaluate(Rule * r, vector<string> actors) {
	cout << "Entered RuleEvaluation!" << endl;
	bool truthValues = false;
	int ops = r->ops;
	string name = r->name;
	if (factEvaluate(actors, name)) return true;
	else if(ops == 0){
		cout << "Calling evalHelper!" << endl;
		//call helper function
		bool finalValue;
		for(int i = 0; i < r->components.size(); i++) {
			vector<string> nextActor;
			for (int n = 1; n < r->components.size(); n++) {
				nextActor.push_back(actors[stoi(r->components[i][n])]);
			}
			cout << "Entering EvalHelper with: " << r->components[i][0] << endl;
			truthValues = truthValues || ruleEvalHelper(r->components[i][0], nextActor);
		}
		return finalValue;
	}
	else if (ops == 1) {
		//AND
		return true;//placeholder
	}
	else return false;//placeholder
}

bool Query::ruleEvalHelper(string name, vector<string> actors) {
	if (factEvaluate(actors, name)) return true;
	else {
		if (rb->rules.count(name) == 1) return ruleEvaluate(rb->rules[name],actors);
		else return false;
	}
}

vector< vector<string>> Query::traverse(vector<string> actors, vector< vector<string> > actorList) {
	vector< vector<string> > result;
	int initSize = actorList[0].size();
	bool invalid = false;
	for (int i = 0; i < initSize; i++) {
		vector<string> path;
		for (int j = 0; j < actorList.size(); j++) {
			if (actorList[j].size() < initSize) {
				invalid = true;
				break;
			}else if(actorList[j][i] == actors[j]) {
				path.push_back(actorList[j][i]);
				break;
			}
			else if (actors[j] == "_") {
				path.push_back(actorList[j][i]);
			}
			else {
				invalid = true;
				break;
			}
		}
		if (invalid == true)break;
		result.push_back(path);
	}
	return result;
}

bool Query::factEvaluate(vector<string> actors, string name) {
	vector< vector<string> > result;
	vector< vector<string> > actorList;
	bool isValid = false;

	if (kb->FactMap.count(name) >= 1) {
		actorList = kb->FactMap[name];
		int initSize = actorList[0].size();
		bool broken = false;
		for (int i = 0; i < initSize; i++) {
			vector<string> path;
			bool matchFound = false;
			for (int j = 0; j < actorList.size(); j++) {
				if (actorList[j].size() < initSize) {
					broken = true;
					break;
				}
				else if (actorList[j][i] == actors[j]) {
					matchFound = true;
					break;
				}
				else if(actors[j] == "_"){
					matchFound = true;
				}
				else {
					matchFound = false;
					break;
				}
			}
			isValid = matchFound;
			if (broken == true)break;
		}
	}
	return isValid;
}

//Prints the results of the query to terminal
//Input: void
//Output: void
//void Query::printResults() {
//	for (int i = 0; i < Results.size(); i++) {
//		cout << Results.at(i)->toString();
//	}
//}

map<string, vector<string>> Query::removeDoubles(map<string, vector<string>>  target) {
	map<string, vector<string>> output;
	//placeholder method
	output = target;
	return output;
}