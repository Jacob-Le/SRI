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
	map<string, vector<Predicate*> > * FactMap = new map<string, vector<Predicate*> >();
}

//Destructor
KB::~KB(){
	FactMap.clear();
}

//Takes in a fact pointer (fact must be created outside of add) and adds it to
//the KB if it doesn't already exist
//Input: Fact pointer
//Output: void
bool KB::Add(Predicate * pred){
	if(FactMap.count(pred->name) == 0){ //If it doesn't exist
		vector<Predicate*> v;
		v.push_back(pred);
		FactMap[pred->name] = v; //May or may not be null cuz temporary variable
	}else{ //If it does exist
		vector<bool> diffChecker;
		bool flag = true;
		if(FactMap[pred->name].size()!= 0){
				for(int j=0; j<FactMap[pred->name].size(); j++){ //Iterating through Vector
					if(FactMap[pred->name].at(j)->components.size() == pred->components.size()){ //if they have the same amount of components
						diffChecker.assign(pred->components.size(),false); //Mark no difference
						for(int k = 0; k<FactMap[pred->name].at(j)->components.size();k++){ //Iterate through components
							if(FactMap[pred->name].at(j)->components.at(k) != pred->components.at(k)){ //If actor pair is different
								diffChecker.at(k) = true; //mark difference
								break;
							}
						}
						bool factMatch = false;
						for(int k =0; k<diffChecker.size(); k++){ //Iterate through diffChecker
							if(diffChecker.at(k)==true){ //If there is a difference
								//FactMap[fact->name].push_back(fact); //Add fact
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
				if(flag == true){
				  cout<<"New Fact added to existing relationship category"<<endl;
				  FactMap[pred->name].push_back(pred);
  				  return true;
				}
				diffChecker.clear();
		}else{
			cout<<"New Fact added to new relationship category"<<endl;
			FactMap[pred->name].push_back(pred);
			return true;
		}
		if(flag == false){
			cout<<"Fact already exists"<<endl;
			return false;
		}
	}
}

void KB::Remove(string r){
	FactMap.erase(r);
}


//Finds a fact and returns a pointer to that fact
//Input: key r
//Output: pointer to Fact with all relationships
vector<Predicate*>* KB::Find(string findKey){
	vector<Predicate*>* ptr = &FactMap[findKey];
	return ptr;
}

//Converts Knowledge database to string
//Input: void
//Output: string representation of knowledge database
string KB::toString(){
	string output = "";
	map<string, vector<Predicate*> > ::iterator it = FactMap.begin();
	for(; it!= FactMap.end(); it++){
		for(int i=0; i< it->second.size();i++) output += it->second.at(i)->InKBtoString();
	}
	return output;
}
