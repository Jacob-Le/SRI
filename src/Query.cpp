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

void Query::inference(){
	for()
}

//Prints the results of the query to terminal
//Input: void
//Output: void
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}
	//-------------------------------------------------------PHASE 1-------------------------------------------
void Query::CreatePredNames(Rule* r) {
	for (int i = 0; i < r->components.size(); i++) {
		predNames.push_back(r->components.at(i)->name); //Builds vector of relationship names
		for (int j = 0; j < r->components.at(i)->components.size(); j++) //Iterate through rule actors
			ToBind.push_back(r->components.at(i)->components.at(j)); //pushes actors onto ToBind
	}
}

vector< vector<Fact*>*> Query::PermutateAndBind(KB* kb) {

	vector< vector<Fact*>*> FromKB;
	vector< vector<Fact*>*> permutation;

	for (int j = 0; j<predNames.size(); j++) { //(Father, Parent)
		vector<Fact*>* Temp;
		Temp = kb->Find(predNames.at(j)); //passes in a relationship name
		FromKB.push_back(Temp); //Fact pointer onto FromKB (Actor1, Actor2)
	}
	//I need to build permutation vector here
	//ToBind holds needed actors
	//iterate through toBind and assign an integer to each unique actor and store ints into a vector
	//With permutated vector, we assign each relationship to X,Y
	//Assign other half of permuted to Z,X while checking if they fit the integers assigned.

	return FromKB; //vector of all relationships relevant
}
//-----------------------PHASE 2---------------------------------------------------------
vector<string> Query::Bind(KB* KnowledgeBase) {
	vector<int> ID;
	ID = BuildID(); //builds ID vector
	vector< vector<Fact*>* > toBeBinded = PermutateAndBind(KnowledgeBase);
	vector<string> result;
	map<int,string> varStorage;
	for (int i = 0; i < toBeBinded[0]->size(); i++){
		varStorage[ID[0]] = toBeBinded[0]->at(i)->components[0];
		varStorage.[ID[1]] = toBeBinded[0]->at(i)->components[1];
		for (int j = 0; j < toBeBinded[1]->size(); j++){
			if (varStorage.find(ID[2]) != varStorage.end()) break;
			if (varStorage.find(ID[3]) != varStorage.end()) break;
			result.push_back(toBeBinded[0]->at(i)->components[0]);
			result.push_back(toBeBinded[0]->at(i)->components[1]);
			result.push_back(toBeBinded[1]->at(i)->components[0]);
			result.push_back(toBeBinded[1]->at(i)->components[1]);
			//call phase 3(result); Passes actors in an array. eg [John,Mary,Ahmed,John] of [X, Y, Z, Z]
		}
		varStorage.clear();
	}
	return result; //Change return types depending on how you use this function.
}

vector<int> Query::BuildID() {
	vector<int> id; //holds actor id for building (X,Y,Z,X) or whatever combo it is
	int currnum = 0;
	for (int i = 0; i < ToBind.size(); i++) {//Iterate through needed actors
		if (id.size() != 0) { //If IDs are not empty, do the thing
			for (int j = 0; j < i; j++) { //Iterate through processed indexes
				if (ToBind[i] == ToBind[j]) { //If it's occured already, put it in again
					id.push_back(id[i]);
					break;
				}
				else { //ID is empty, put 0 in index 1
					id.push_back(currnum);
					currnum++;
				}
			}
		}
		else {
			id.push_back(currnum);
			currnum++;
		}
	}
	return id;
}