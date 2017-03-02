#include "Query.h"
#include<iostream>
#include<cstdio>
using namespace std;
//I'm making so many assumptions here. Someone is going to have to fill in the blanks
//Constructor. Maybe won't need copy or move constructors?

vector<Fact*> Results;

Query::Query(KB * kb, RB * rb) {
	KB * knowledge = kb;
	RB * rules = rb;
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

//used in concatenate to look for dupes
vector<Fact*> Query::preventDupes(vector<Fact*>* A, vector<Fact*> B){

	vector<bool> diffChecker;
	bool flag = true;
	for(int i=0; i<A->size(); i++){
		if(B.size() != 0){
			//cout<<"Checking for differences"<<endl;
				for(int j=0; j<B.size(); j++){ //Iterating through Vector
					if(B.at(j)->components.size() == A->at(i)->components.size()){ //if they have the same amount of components
						diffChecker.assign(A->at(i)->components.size(),false); //Initialize all to false
						for(int k = 0; k<B.at(j)->components.size();k++){ //Iterate through components
							if(B.at(j)->components.at(k) != A->at(i)->components.at(k)){ //If actor pair is different
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

void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}
