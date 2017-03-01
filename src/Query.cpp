#include "Query.h"
#include<iostream>
#include<cstdio>
using namespace std;
//I'm making so many assumptions here. Someone is going to have to fill in the blanks
//Constructor. Maybe won't need copy or move constructors?

vector<Fact*> Results;

Query::Query(KB* Knowledge2, RB* ruleBase2) {
	Knowledge = Knowledge2;
	ruleBase = ruleBase2;
}

//FACT--------------------------------------------------------------------------
vector<Fact*>* Query::listFact(string factKey) {
	vector<Fact*>* result = Knowledge->Find(factKey); 
	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
	return result;
}

//SIMPLE RULE-------------------------------------------------------------------
//this method will print both unconcatenated results. Maybe we'll fix it but for now it'll be a debug feature. and maybe stay that way lol
//void Query::listSimpleRule(/*something*/) {
//	printf("Output 1:\n");
	//vector<string> resultA = listFact(/*some kind of key from that something*/);
//	printf("Output 2:\n");
	//vector<string> resultB = listFact(/*some kind of key from that something*/);/

//	printf("Concatenated result:\n");
//	vector<string> resultConcat = concatenate(resultA, resultB);
//	for (int i = 0; i < resultConcat.size(); i++) {
//		printf(resultConcat[i]);
//		printf("\n");
//	}
//}

void Query::CreateVarMapping(Rule* R){
	bool notUnique = false;
	for(int i=0; i< R->enactVars.size(); i++){
		for(int j=0; j<varMapping.size(); j++){
			if(R->enactVars.at(i) == varMapping.at(j)) notUnique = true;
		}
		if(varMapping.size() == 0 || notUnique == false) varMapping.push_back(R->enactVars.at(i));
		notUnique = false;
	}
	for(int i=0; i< R->components.size(); i++){
		for(int j=0; j< R->components.at(i).components.size(); j++){
			for(int k=0; k < varMapping.size(); k++){
				if(R->components.at(i).components.at(j) == varMapping.at(k)) notUnique = true;
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
		string Relationship = R->components.at(i).name;
		vector<Fact*>* listOfFacts = Knowledge->Find(Relationship);
		CreateVarBounds(listOfFacts);
	}	
}

//create bounds for vars
void Query::CreateVarBounds(vector<Fact*>* Facts){
	
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
/*
vector<strings> params;
vector< vector<strings> > perms;

//recursive permutator
/*g(int varOn, int numUniqueVars){
	if(varOn > numUniqueVars){
		return
	}
	//choose string from available list
	//eliminate from other lists for proceeding vars
}

//helper function to get rid of duplicates
vector<Fact*> Query::concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB) {
	vector<Fact*> result;
	bool found = false;
	result = preventDupes(resultA, result);
	result = preventDupes(resultB, result);
	//prepare yourself for a brute force search algorithm wooooooo
	//checks if A in B. If not, pushback onto result vector.
	/*for (int i = 0; i < resultA.size(); i++) {
		found = false;
		for (int j = 0; j < resultB.size(); j++) {
			if (resultA.at(i) == resultB.at(j)) {
				found = true;
				break;
			}
		}

		if (!found) {
			result.push_back(resultA[i]);
		}
	}
	//checks if B in A. If not, pushback onto result vector.
	for (int i = 0; i < resultB.size(); i++) {
		found = false;
		for (int j = 0; j < resultA.size(); j++) {
			if (resultB[i] == resultA[j]) {
				found = true;
				break;
			}
		}

		if (!found) {
			result.push_back(resultB[i]);
		}
	}
	return result;
}

//used in concatenate to look for dupes
vector<Fact*> Query::preventDupes(vector<Fact*>* A, vector<Fact*> B){

	vector<bool> diffChecker;		
	bool flag = true;
	for(int i=0; i<A->size(); i++){
		if(B.size() != 0){
			//cout<<"Checking for differences"<<endl;
				for(int j=0; j<B.size(); j++){ //Iterating through Vector
					if(B.at(j)->actors.size() == A->at(i)->actors.size()){ //if they have the same amount of actors
						diffChecker.assign(A->at(i)->actors.size(),false); //Initialize all to false
						for(int k = 0; k<B.at(j)->actors.size();k++){ //Iterate through actors
							if(B.at(j)->actors.at(k) != A->at(i)->actors.at(k)){ //If actor pair is different
								diffChecker.at(k) = true; //mark difference
								break;
							}
						}
						bool factMatch = false;
						for(int k =0; k<diffChecker.size(); k++){ //Iterate through diffChecker
							if(diffChecker.at(k)==true){ //If there is a difference
								factMatch = false;
								break;
							}
							factMatch=true; //THIS IS FALSE IF THERE IS A DIFFERENCE
						}
						if(factMatch == true){ //if it matches
							flag = false;
							break;
						}
					}
				}
				if(flag == true) B.push_back(A->at(i));
				diffChecker.clear();
		}else{
			B.push_back(A->at(i));
		}
	}
	
	
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}

}
*/