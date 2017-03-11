#include "KB.h"
#include<algorithm>
#include<iostream>
using namespace std;

KB::KB(){
	//cout<< "Give int for max depth of KB"<<endl;
	/*const int index = 4;
	//cin >> index;
	FactMap<string, vector<string>, index> facts;*/	
}

/*void KB::Add(FactMap<string, vector<string>, int> facts, vector<string> actors, int depth){
	
	if(facts.count(key) == 1){ //if the Key already exists
		
		if(depth > 1){ //if not at last level
			facts = facts[actors[actors.size()-depth]]; //move down a level
			Add(facts, actors, depth-1); //call it again
		}else{
			facts[actors[actors.size()-depth]].push_back(actors.at(actors.size()-1));
		}
		
	}else if(facts.count(key) == 0){ //if the key doesnt exist yet
		if( depth>2){
			FactMap<string, FactMap, depth-1> facty;
			facts[actors[actors.size()-depth]] = facty;
			Add(facts, actors, depth-1); //stepping into lower
		}else if(depth == 2){
			FactMap<string, vector<string>, depth-1> factie;
			facts[actors[actors.size()-depth]] = factie;
			Add(facts, actors, depth-1);
		}else if(depth ==1){
			facts[actors[actors.size()-depth]].push_back(actors.at(actors.size()-1));
		}
	}
	
}*/

int main(){
	KB* kb = new KB();
	vector<string> cheese;
	cheese.push_back("cheese");
	cheese.push_back("pepperoni");
	cheese.push_back("crust");
	map<string,vector<string> > temp;
	map<string,map<string, vector<string> > > outer_layer;
	temp[cheese.at(1)] = cheese;
	outer_layer[cheese.at(2)] = temp;
	vector<string>* Doritos = outer_layer[temp[cheese.at(1)]];//.at(0);
	cout << Doritos->at(2);
	//kb->facts[cheese.at(0)] = temp;
	//cout << cheese.at(0);
	//kb->facts[cheese.at(0)];
	//cout << cheese.at(1);
	//
	//for(int i=0; i< kb->facts["pepperoni"].size(); i++) cout << kb->facts.at(temp["pepperoni"]).at(i);
	//kb.add(kb.facts,cheese,4);
}