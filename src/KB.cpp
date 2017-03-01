//knowledge base//
//#include<map>
#include<algorithm>

#ifndef PREDICATE_H
#define PREDICATE_H
#endif

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
void KB::Add(Fact * fact){
	//checking if relationship exists in the KB
	//cout << fact->Relationship;
	//if(FactMap.find(fact->Relationship) == FactMap.end()){
	if(FactMap.count(fact->Relationship) == 0){ //If it doesn't exist
		vector<Fact*> v;
		v.push_back(fact);
		FactMap[fact->Relationship] = v; //May or may not be null cuz temporary variable
	}else{ //If it does exist
		vector<bool> diffChecker;		
		bool flag = true;
		if(FactMap[fact->Relationship].size()!= 0){
			//cout<<"Checking for differences"<<endl;
				for(int j=0; j<FactMap[fact->Relationship].size(); j++){ //Iterating through Vector
					//cout<< FactMap[fact->Relationship].at(j)->toString()<<endl;
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
				//if(diffChecker.size()==0) FactMap[fact->Relationship].push_back(fact);
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

Fact* KB::Fetch(string r, vector<string> a) {
	for(Fact* f : FactMap[r]){
		if(f->components == a) return f;
	}
	return NULL; //was nullptr (probably should still be)
}

//Pretty sure obsolete now
/*Fact* KB::Remove(Fact * fact){
	vector<Fact*>::iterator pos = Find(FactMap[fact->Relationship].begin(), FactMap[fact->Relationship].end(), fact);
	Fact * temp = fact;
	FactMap[fact->Relationship].erase(pos);
	return temp;
}*/

void KB::Remove(string r){
	FactMap.erase(r);
}

vector<Fact*>* KB::Find(string findKey){
	vector<Fact*>* ptr = &FactMap[findKey];
	return ptr;
}

string KB::toString(){
	string output = "";
	map<string, vector<Fact*> > ::iterator it = FactMap.begin();
	for(; it!= FactMap.end(); it++){
		for(int i=0; i< it->second.size();i++) output += it->second.at(i)->toString();
	}
	return output;
}

