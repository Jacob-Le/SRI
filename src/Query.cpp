//Query.cpp
/*
	Query handles interactions between databases. Allow databases to query each other
	for truth values of targetted facts or rules.
*/
#include<iostream>
#include<cstdio>

#include "Query.h"

using namespace std;

vector<Predicate*> Results;

Query::Query(KB * knowledge, RB * rules) {
	kb = knowledge;
	rb = rules;
}

//FACT--------------------------------------------------------------------------
// Returns a pointer to a list (vector) of Fact pointers with a similar relationship
//from the Knowledge Base.
// Takes in a pointer to the Knowledge Base and a string representative of the similar
// relationship.
vector<Predicate*>* Query::listFact(KB* Knowledge, string factKey) {
	vector<Predicate*>* result = Knowledge->Find(factKey);
	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
	return result;
}

//SIMPLE RULE-------------------------------------------------------------------
/*
//helper function to get rid of duplicates
vector<Predicate*> Query::concatenate(vector<Predicate*>* resultA, vector<Predicate*>* resultB) {
	vector<Predicate*> result;
	bool found = false;
	result = preventDupes(resultA, result);
	result = preventDupes(resultB, result);

	return result;
}
*/
//----------------------------------Part 3: evaluate--------------------------------------//

//If the Rule is valid, adds a Fact representative of the Rule's validity to the KB
//MAKE SURE THAT ACTORS FOR EACH COMPONENT ARE MUTUALLY EXCLUSIVE
//Input: Component vector from Rules
//Output: Returns truth value of the rule
bool Query::enact(Rule * r, vector<string> components, KB * kb){
  if(r->evaluate(components)){
    if(kb->Add(new Predicate(r->name, r->actors))){
      //Run query.inference here
    }
    return true;
  }
  return false;
}

//------------------------------Inferencing-----------------------------------------------//

 //Will handle the calling of inference functions
 void Query::inference(Rule* rule){
   CreateVarMapping(rule); 
   CreatePredNames(rule);
   CreateVarBoundsMaster(rule);
   cout << "VarBounds: " << VarBoundstoString() << endl;
   Bind(kb);
 }

 //creates a list of the unique vars
 void Query::CreateVarMapping(Rule* R){
	bool notUnique = false;
	for(int i=0; i< R->actors.size(); i++){
		for(int j=0; j<varMapping.size(); j++){
			if(R->actors.at(i) == varMapping.at(j)) notUnique = true;
		}
		if(varMapping.size() == 0 || notUnique == false){
			varMapping.push_back(R->actors.at(i));
			cout << R->actors.at(i) << " ";
		}
		notUnique = false;
	}
	
	vector<string> temp;
	for(int i=0; i< R->components.size(); i++){
		if(R->RuleTempVars.count(i)==1){ //if rule get its mapped temp vars
			for(int j=0; j = R->RuleTempVars.at(i).size(); j++){
				temp.push_back(R->RuleTempVars.at(i).at(j));
			}
		}else{ //if fact get its components
		    cout << R->components.at(i)->toString();
		    cout << R->components.at(i)->components.size();
			for(int j=0; j < R->components.at(i)->components.size(); j++){
				cout << R->components.at(i)->components.at(j) << " ";
				temp.push_back(R->components.at(i)->components.at(j));
			}
		}
		//cout << temp.size();
		for(int j=0; j< temp.size(); j++){
			cout << "Comparing " << temp.at(j) << ":\n";
			for(int k=0; k < varMapping.size(); k++){
				cout << varMapping.at(k) << " ";
				if(temp.at(j) == varMapping.at(k)) notUnique = true;
			}
			if(notUnique == false){
				varMapping.push_back(temp.at(j));
				cout << temp.at(j) << " ";
			}
			notUnique = false;
		}
	}
}
 
//Should gather all possibilities for vars to be
 void Query::CreateVarBoundsMaster(Rule* R){
 	for(int i=0; i<varMapping.size(); i++){
 		vector<string> temp;
 		VarBounds[varMapping.at(i)] = temp;
 	}
 	for(int i=0; i<R->components.size(); i++){
 		string Relationship = R->components.at(i)->name;
 		vector<Predicate*>* listOfFacts = kb->Find(Relationship);
 		CreateVarBounds(listOfFacts);
 	}	
 }
 
 //create bounds for vars (Called in VarBoundsMaster() )
 void Query::CreateVarBounds(vector<Predicate*>* Facts){
 	
 	int sizeOf = Facts->at(0)->components.size();
 	
 	//iterate through list of facts
 	for(int i=0; i<sizeOf; i++){
 		//iterate through list of actors in facts
 		for(int j=0; j<sizeOf; j++){
 			//Create pointer to vector pertaining to proper var
 			vector<string> temp;
 			temp = VarBounds[varMapping.at(j)];
 			temp.push_back(Facts->at(i)->components.at(j));
 		}
 	}
 }
 
 //prints out varBounds
 string Query::VarBoundstoString(){
 	string output = "";
 	map<string, vector<string> > ::iterator it = VarBounds.begin();
 	for(; it!= VarBounds.end(); it++){
 		output += it->first;
 		output += ": ";
 		for(int i=0; i< it->second.size();i++){
 			output += it->second.at(i);
 			output += ", ";
 		}
 		output += "\n";
 	}
 	return output;
 }
 
//Prints the results of the query to terminal
//Input: void
//Output: void
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}
	//-------------------------------------------------------PHASE 1-------------------------------------------
void Query::CreatePredNames(Rule* r) {
	vector<string> temp;
	cout << "PredNames: ";
	for (int i = 0; i < r->components.size(); i++) {
		cout << r->components.at(i)->name << " ";
		predNames.push_back(r->components.at(i)->name); //Builds vector of relationship names
		if(r->RuleTempVars.count(i)==1){ //if rule get its mapped temp vars
			temp = r->RuleTempVars.at(i);
		}else{ //if rule get its components
			temp = r->components.at(i)->components;
		}
		for (int j = 0; j < temp.size(); j++){ //Iterate through rule actors
		    cout << "Into ToBind: " << temp.at(j) << " ";
			ToBind.push_back(temp.at(j)); //pushes actors onto ToBind
		}
	}
    for(int i = 0; i < ToBind.size(); i++){
  	  cout<<"ToBind: "<<ToBind[i]<<", ";
    }
    cout<<endl;
}

vector< vector<Predicate*>*> Query::KBSlice(KB* kb) {

	vector< vector<Predicate*>*> FromKB;
	vector< vector<Predicate*>*> permutation;
  cout<<"FromKB: ";

	for (int j = 0; j<predNames.size(); j++) { //(Father, Parent)
		vector<Predicate*>* Temp;
		Temp = kb->Find(predNames.at(j)); //passes in a relationship name
    cout<<Temp<< ", ";
		FromKB.push_back(Temp); //Fact pointer onto FromKB (Actor1, Actor2)
	}
  cout<<endl;
return FromKB;
}

//-----------------------PHASE 2---------------------------------------------------------
vector<string> Query::Bind(KB* KnowledgeBase) {
	vector<int> ID;
	ID = BuildID(); //builds ID vector
	vector< vector<Predicate*>* > toBeBinded = KBSlice(KnowledgeBase);
	vector<string> result;
	map<int, string> varStorage;
	for (int i = 0; i < toBeBinded[0]->size(); i++) {
		varStorage[ID[0]] = toBeBinded[0]->at(i)->components[0];
		varStorage[ID[1]] = toBeBinded[0]->at(i)->components[1];
		result.push_back(toBeBinded[0]->at(i)->components[0]);
		result.push_back(toBeBinded[0]->at(i)->components[1]);
    cout<<"Result[0] = "<<toBeBinded[0]->at(i)->components[0]<<endl;
    cout<<"Result[1] = "<<toBeBinded[0]->at(i)->components[1]<<endl;
		for (int j = 0; j < toBeBinded[1]->size(); j++) {
			if (varStorage.count(ID[2]) == 1) break;
			if (varStorage.count(ID[3]) == 1) break;
			result.push_back(toBeBinded[1]->at(i)->components[0]);
			result.push_back(toBeBinded[1]->at(i)->components[1]);
      cout<<"Result[2] = "<<toBeBinded[1]->at(i)->components[0]<<endl;
    	cout<<"Result[3] = "<<toBeBinded[1]->at(i)->components[1]<<endl;
			//call phase 3(result); Passes actors in an array. eg [John,Mary,Ahmed,John] of [X, Y, Z, X]
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
  for(int i = 0; i < id.size(); i++){
  	cout<<id[i]<<", ";
  }
  cout<<endl;
	return id;
}

