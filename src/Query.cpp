//Query.cpp
/*
	Query handles interactions between databases. Allow databases to query each other
	for truth values of targetted facts or rules.
*/
#include "Query.h"
#include<iostream>
#include<cstdio>
using namespace std;
//Constructor.

vector<Fact*> Results;

Query::Query() {

}

//FACT--------------------------------------------------------------------------
// Returns a pointer to a list (vector) of Fact pointers with a similar relationship
//from the Knowledge Base.
// Input: Takes in a pointer to the Knowledge Base and a string
//Output: A pointer to a list (vector) of Fact pointers
vector<Fact*>* Query::listFact(KB* Knowledge, string factKey) {
	vector<Fact*>* result = Knowledge->Find(factKey);
	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
	return result;
}

//helper function to get rid of duplicates
//Input: Vector of facts resultA and resultB
//Output: Vector of combined facts with dupblicates eliminated
vector<Fact*> Query::concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB) {
	vector<Fact*> result;
	bool found = false;
	result = preventDupes(resultA, result);
	result = preventDupes(resultB, result);
	return result;
}

//Helper function to help concatenate. Removes duplicates.
//Input: vector of facts A and B
//Output: vector of facts with duplicates eliminated
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
//Prints the results of the query to terminal
//Input: void
//Output: void
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}
	//-------------------------------------------------------PHASE 2-------------------------------------------
void Query::CreatePredNames(Rule* r) {
	vector<string> predNames; //Relevant relationship names
	vector<string> ToBind; //Variables that need actors
	for (int i = 0; i < r->components.size(); i++) {
		predNames.push_back(r->components.at(i)->name); //Builds vector of relationship names
		for (int j = 0; j < r->components.components.size(); j++) //Iterate through rule actors
			ToBind.push_back(r->components.components.at(j)); //pushes actors onto ToBind
	}
}

vector< vector<string>*> Query::PermutateAndBind(KB* kb) {

	vector< vector<string>*> FromKB;
	vector< vector<string>*> permutation;

	for (int j = 0; j<predNames.size(); j++) { //(Father, Parent)
		vector<string>* Temp;
		Temp = kb->Find(predNames.at(i));
		FromKB.push_back(Temp); //Fact pointer onto FromKB (Actor1, Actor2)
	}
	//I need to build permutation vector here
	//ToBind holds needed actors
	//iterate through toBind and assign an integer to each unique actor and store ints into a vector
	//With permutated vector, we assign each relationship to X,Y
	//Assign other half of permuted to Z,X while checking if they fit the integers assigned.

	return FromKB; //vector of all relationships relevant
}

vector<string> Query::Bind() {
	vector<int> ID = BuildID(); //builds ID vector
	vector<string> result;
	//match = false;
	//foreach(relation1)
	//vector<string> buff
	//buff0 = relation1(source)
	//buff1 = relation1(target)
	// X: relation1(source) (0)
	// Y: relation1(target) (1)
	//foreach(relation2)
	// foreach(buff)
	//  if relation2(index) == buff: match = true;

	//return result;
}

vector<int> Query::BuildID() {
	vector<int> id; //holds actor id for building (X,Y,Z,X) or whatever combo it is
	int currnum = 0;
	for (int i = 0; i < ToBind.size(); i++) {//Iterate through needed actors
		if (id.size() != 0) { //If IDs are not empty, do the thing
			for (int j = 0; j < i; j++) { //Iterate through processed indexes
				if (ToBind[i] == ToBind[j]) { //If it's occured already, put it in again
					id.push_back(id[j]);
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