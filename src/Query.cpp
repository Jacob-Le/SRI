//Query.cpp
/*
	Query handles interactions between databases. Allow databases to query each other
	for truth values of targetted facts or rules.
*/
#include<iostream>
#include<cstdio>

#include "Query.h"

using namespace std;

Query::Query(KB * knowledge, RB * rules) {
	kb = knowledge;
	rb = rules;
}

//Grandfather->vector
//[0]: [John, John]
//[1] : [Bob, Mary]

map<string, vector<vector<string>> > Query::inference(vector<string> newFact){ //(Father,bob, " ", jerry,etc)
	string relation = newFact[0]; //Stores target name
	map<int,vector<string>> binding;
	vector<string> tracker;
	vector<string> actors; //Actors

	cout << "INFERENCE: Inference begin." << endl;

	for (int i = 1; i < newFact.size(); i++) {
		actors.push_back(newFact[i]);
		cout << "INFERENCE: Actors:" << newFact[i] << endl;
	}

	map<string, vector<vector<string>> > output;

	if (rb->rules.count(relation) == 1) {
		cout << "Found in KB and RB! Evaluating assosciated Rule" << endl;
		Rule * r = rb->rules[relation];
		cout << "INFERENCE: In rulebase=" << ruleEvaluate(r,actors) << endl;
		if (ruleEvaluate(r, actors)) {
			cout << "INFERENCE: Rule Evaluated! Iterating now!" << endl;
			string temp;
			for (int j = 0; j < r->components.size(); j++){
				traverse(actors, &(r->components[j]), j, &binding, &tracker);
			}
			//output[relation].insert(output[relation].end(), path.begin(), path.end());
		}//somehow return an empty output?
	}
	cout << "Iteration Complete! Output:" << endl;
	for (map<int, vector<string>>::iterator it = binding.begin(); it != binding.end(); it++){
		for (int i = 0; i < it->second.size(); i++){
			cout << "INFERENCE: Binding row " << it->first << " column " << i << ": " << it->second.at(i) << endl;
		}
	}

	eraseDuplicates(&binding);
	for (int x = 0; binding.count(x) == 1; x++){
		output[relation].push_back(binding[x]);
	}
	return output;
}

bool Query::ruleEvaluate(Rule * r, vector<string> actors) {
	//cout << "Entered RuleEvaluation!" << endl;
	//bool truthValues = false;
	int ops = r->ops;
	string name = r->name;
	if (factEvaluate(actors, name)) return true;
	else if (ops == 0) return operateOR(name, actors, r);
	else if (ops == 1) return operateAND(name, actors, r);
	else return false;//placeholder
}

bool Query::operateOR(string name, vector<string> actors, Rule * r){
	bool finalValue = false;
	for (int i = 0; i < r->components.size(); i++) {
		vector<string> nextActor;
		for (int n = 1; n < r->components[i].size(); n++) {
			//cout << "operateOR: Actor=" << actors[stoi(r->components[i][n])] << endl;
			nextActor.push_back(actors[stoi(r->components[i][n])]);
		}
		//cout << "Entering EvalHelper with: " << r->components[i][0] << endl;
		bool test = ruleEvalHelper(r->components[i][0], nextActor);
		//cout << "operateOR: Name=" << r->components[i][0] << "| Test=" << test << endl;
		finalValue = finalValue || test;
	}
	//cout << "operateOR: finalValue: " << finalValue << endl;
	return finalValue;
}

bool Query::operateAND(string name, vector<string> actors, Rule * r){
	bool finalValue = true;
	for (int i = 0; i < r->components.size(); i++) {
		vector<string> nextActor;
		for (int n = 1; n < r->components[i].size(); n++) {
			//cout << "operateAND: Actor=" << actors[stoi(r->components[i][n])] << endl;
			nextActor.push_back(actors[stoi(r->components[i][n])]);
		}
		//cout << "Entering EvalHelper with: " << r->components[i][0] << endl;
		bool test = ruleEvalHelper(r->components[i][0], nextActor);
		// cout << "operateAND: Name=" << r->components[i][0] << "| Test=" << test << endl;
		if (test == false) return false;
		else finalValue = finalValue && test;
	}
	//cout << "RULEEVAL: finalValue: " << finalValue << endl;
	return finalValue;
}

bool Query::ruleEvalHelper(string name, vector<string> actors) {
	//cout << "EVALHELPER: " << name << endl;
	if (factEvaluate(actors, name)) {
		//cout << "Found in KB" << endl;
		return true;
	}
	else {
		if (rb->rules.count(name) == 1) return ruleEvaluate(rb->rules[name],actors);
		else return false;
	}
}

void Query::traverse(vector<string> actor, vector<string> * currComponent, int currSet, map<int, vector<string>> * bindings, vector<string> * tracker) {
	vector< vector<string> > result;
	string relation;
	vector<int> currActor;
	int currentSet = currSet;

	for (int i = 1; i < currComponent->size(); i++){
		currActor.push_back(stoi(currComponent->at(i)));
	}
	relation = currComponent->at(0);
	vector< vector<string> > actorList = kb->FactMap[relation];

	for (int actorCounter = 0; actorCounter < currActor.size();){
		cout << "TRAVERSE: Traversing!" << endl;
		cout << "TRAVERSE: actorList.size()" << actorList.size() << endl;
		if (actorList.size() == 0)break;
		for (int j = 0; j < actorList.size(); j++) {
			cout << "currActor=" << actor[currActor[actorCounter]] << "|currActor[actorCounter]=" << currActor[actorCounter] << endl;
			if (actor[currActor[actorCounter]] == "_") {
				if (bindings->count(currActor[actorCounter]) == 0){
					cout << "actorList[j][currentSet]=" << actorList[j][currentSet] << endl;
					cout << "New Binding" << endl;
					(*bindings)[currActor[actorCounter]].push_back(actorList[j][currentSet]);
					tracker->push_back(actorList[j][currentSet]);
					actorCounter++;
				}
				else{
					cout << "Found binding" << endl;
					vector<string> temp;
					temp.push_back(actorList[j][currentSet]);
					if (factEvaluate(temp, relation)){
						if (tracker->at(currActor[actorCounter]) != actor[currActor[actorCounter]]){
							bindings->clear();
							tracker->clear();
							break;
						}
					}
				}
			}
			else if (actor[currActor[actorCounter]] == actorList[j][currentSet]) {
				if (bindings->count(currActor[actorCounter]) == 0){
					cout << "actorList[j][currentSet]=" << actorList[j][currentSet] << endl;
					cout << "New Binding" << endl;
					(*bindings)[currActor[actorCounter]].push_back(actorList[j][currentSet]);
					tracker->push_back(actorList[j][currentSet]);
					actorCounter++;
				}
				else{
					vector<string> temp;
					temp.push_back(actorList[j][currentSet]);
					if (factEvaluate(temp, relation)){
						if (tracker->at(currActor[actorCounter]) != actor[currActor[actorCounter]]){
							bindings->clear();
							tracker->clear();
							break;
						}
					}
				}
			}
			else break;
		}
	}
}

bool Query::factEvaluate(vector<string> actors, string name) {
	vector< vector<string> > result;
	vector< vector<string> > actorList;
	bool isValid = false;
	//cout << "FACTEVAL: " << name << endl;
	if (kb->FactMap.count(name) >= 1) {
		//cout << "FACTEVAL: FOUND IN KB" << endl;
		actorList = kb->FactMap[name];
		int initSize = actorList[0].size();
		//cout << "FACTEVAL: InitSize = " << initSize << endl;
		bool broken = false;
		for (int i = 0; i < initSize; i++) {
			vector<string> path;
			bool matchFound = false;
			for (int j = 0; j < actorList.size(); j++) {
				//cout << "FACTEVAL: ActorList: " << actorList[j][i] << " :: Actors: " << actors[i] << endl;
				if (actorList[j].size() < initSize) {
					broken = true;
					break;
				}
				else if (actorList[j][i] == actors[j]) {
					//cout << "FACTEVAL: ActorList: "<<actorList[j][i]<<" :: Actors: "<< actors[i] << endl;
					matchFound = true;
					break;
				}
				else if(actors[j] == "_"){
					matchFound = true;
					break;
				}
				else {
					matchFound = false;
					break;
				}
				//isValid = matchFound;
			}
			isValid = matchFound;
			if (broken == true)break;
		}
	}
	//cout << "FACTEVAL: isValid " << isValid << endl;
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

void Query::eraseDuplicates(map<int,vector<string>> * binding){
	int initSize = binding->begin()->second.size();
	//cout << "ERASEDUPLICATES: initSize=" << initSize << endl;
	for (int i = 0; i < initSize; i++){
		vector<string> buffer;
		for (map<int, vector<string>>::iterator it = binding->begin(); it != binding->end(); it++){
			/*cout << "ERASEDUPLICATES: in buffer=" << it->second.at(i) << endl;
			cout << "ERASEDUPLICATES: current row=" << it->first << endl;
			cout << "ERASEDUPLICATES: current index=" << i << endl;*/
			buffer.push_back(it->second.at(i));
		}
		//cout << "ERASEDUPLICATES: buffersize=" << buffer.size() << endl;
		
		int tempSize = binding->begin()->second.size();
		for (int j = i+1; j < tempSize; j++){
			//cout << "ERASEDUPLICATES: tempSize=" << tempSize << endl;
			bool match = false;
			int bufferCounter = 0;
			for (map<int, vector<string>>::iterator it2 = binding->begin(); it2 != binding->end(); it2++){
				if (buffer[bufferCounter] == it2->second.at(j)){
					match = true;
				}
				else {
					//cout << "ERASEDUPLICATES: no match." << endl;
					match = false;
					break;
				}
				bufferCounter++;
			}
			//bufferCounter++;
			if (match == true){
				remove(j, binding);
				tempSize = binding->begin()->second.size();
				//cout << "ERASEDUPLICATES: tempSize=" << tempSize <<"|j=" << j << endl;
				j--;
				initSize--;
			}
			else if (match == false)break;
			//cout << "ERASEDUPLICATES: removal complete!" << endl;
		}
		//cout << "ERASEDUPLICATES: WHAT THE FUCK ARE YOU FUCKING KIDDING ME i=" << i << "|initSize=" << initSize << endl;
	}
}

void Query::remove(int index, map<int, vector<string>> * binding){
	//cout << "REMOVE: index=" << index << endl;
	for (map<int, vector<string>>::iterator it = binding->begin(); it != binding->end(); it++){
		//cout << "REMOVE: removing!" << endl;
		it->second.erase(it->second.begin() + index);
	}
}