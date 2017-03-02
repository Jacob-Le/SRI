//knowledge base
/*
	This file handles the creation of a database holding all Facts generated
	by the program. It contains functions that allow you to access Facts, removes
	Facts, add Facts.
*/
#include<algorithm>

#include "KB.h"

using namespace std;

//Constructor, initializes as empty
KB::KB(){
	map<string, vector<Fact*> > * FactMap = new map<string, vector<Fact*> >();
}

//Destructor
KB::~KB(){
	FactMap.clear();
}

//Takes in a fact pointer (fact must be created outside of add) and adds it to
//the KB if it doesn't already exist
//Input: Fact pointer
//Output: void
void KB::Add(Fact * fact){
	if(FactMap.count(fact->Relationship) == 0){ //If it doesn't exist
		vector<Fact*> v;
		v.push_back(fact);
		FactMap[fact->Relationship] = v; //May or may not be null cuz temporary variable
	}else{ //If it does exist
		vector<bool> diffChecker;
		bool flag = true;
		if(FactMap[fact->Relationship].size()!= 0){
				for(int j=0; j<FactMap[fact->Relationship].size(); j++){ //Iterating through Vector
					if(FactMap[fact->Relationship].at(j)->components.size() == fact->components.size()){ //if they have the same amount of components
						diffChecker.assign(fact->components.size(),false); //Mark no difference
						for(int k = 0; k<FactMap[fact->Relationship].at(j)->components.size();k++){ //Iterate through components
							if(FactMap[fact->Relationship].at(j)->components.at(k) != fact->components.at(k)){ //If actor pair is different
								diffChecker.at(k) = true; //mark difference
								break;
							}
						}
						bool factMatch = false;
						for(int k =0; k<diffChecker.size(); k++){ //Iterate through diffChecker
							if(diffChecker.at(k)==true){ //If there is a difference
								//FactMap[fact->Relationship].push_back(fact); //Add fact
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
				if(flag == true) FactMap[fact->Relationship].push_back(fact);
				diffChecker.clear();
		}else{
			FactMap[fact->Relationship].push_back(fact);
		}
		if(flag == false){
			cout<<"Fact already exists"<<endl;
		}
	}
}

//Retrieves a specific fact from Knowledge database
//Input: Key r, Vector of components for specific relationship
//Output: Target fact or NULL if not found.
Fact* KB::Fetch(string r, vector<string> a) {
	for(Fact* f : FactMap[r]){
		if(f->components == a) return f;
	}
	return NULL; //was nullptr (probably should still be)
}

//Removes fact from database with key r
//Input: Key r
//Output: void
void KB::Remove(string r){
	FactMap.erase(r);
}

//Finds a fact and returns a pointer to that fact
//Input: key r
//Output: pointer to Fact with all relationships
vector<Fact*>* KB::Find(string findKey){
	vector<Fact*>* ptr = &FactMap[findKey];
	return ptr;
}

//Converts Knowledge database to string
//Input: void
//Output: string representation of knowledge database
string KB::toString(){
	string output = "";
	map<string, vector<Fact*> > ::iterator it = FactMap.begin();
	for(; it!= FactMap.end(); it++){
		for(int i=0; i< it->second.size();i++) output += it->second.at(i)->toString();
	}
	return output;
}
