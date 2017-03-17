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
	string relation = newFact[0];
	map<int,vector<string>> binding;
	vector<string> actors;

	for (int i = 1; i < newFact.size(); i++) {
		actors.push_back(newFact[i]);
		//cout << "INFERENCE: Actors:" << newFact[i] << endl;
	}

	map<string, vector<vector<string>> > output;

	if (rb->rules.count(relation) == 1) {
		//cout << "Found in KB and RB! Evaluating assosciated Rule" << endl;
		Rule * r = rb->rules[relation];
		cout << "INFERENCE: In rulebase=" << ruleEvaluate(r,actors) << endl;
		if (ruleEvaluate(r, actors)) {
			//cout << "INFERENCE: Rule Evaluated! Iterating now!" << endl;
			string temp;
			vector<string> buffer;
			vector< vector<string> >path;
			for (int j = 0; j < r->components.size(); j++) {
				vector<int> currActor;
				for (int i = 1; i < r->components[j].size(); i++){
					temp = r->components[j][0];
					//cout << "INFERENCE" << r->components[j][i] << endl;
					currActor.push_back(stoi(r->components[j][i]));
				}
				traverse(actors, currActor, kb->FactMap[temp], &binding);
			}
			//output[relation].insert(output[relation].end(), path.begin(), path.end());
		}//somehow return an empty output?
	}
	//cout << "Iteration Complete! Output:" << endl;
	for (map<int, vector<string>>::iterator it = binding.begin(); it != binding.end(); it++){
		for (int i = 0; i < it->second.size(); i++){
			//cout << "INFERENCE: Binding row " << it->first << " column " << i << ": " << it->second.at(i) << endl;
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
			cout << "operateOR: Actor=" << actors[stoi(r->components[i][n])] << endl;
			nextActor.push_back(actors[stoi(r->components[i][n])]);
		}
		cout << "Entering EvalHelper with: " << r->components[i][0] << endl;
		bool test = ruleEvalHelper(r->components[i][0], nextActor);
		cout << "operateOR: Name=" << r->components[i][0] << "| Test=" << test << endl;
		finalValue = finalValue || test;
	}
	cout << "operateOR: finalValue: " << finalValue << endl;
	return finalValue;
}

bool Query::operateAND(string name, vector<string> actors, Rule * r){
	bool finalValue = true;
	for (int i = 0; i < r->components.size(); i++) {
		vector<string> nextActor;
		for (int n = 1; n < r->components[i].size(); n++) {
			cout << "operateAND: Actor=" << actors[stoi(r->components[i][n])] << endl;
			nextActor.push_back(actors[stoi(r->components[i][n])]);
		}
		cout << "Entering EvalHelper with: " << r->components[i][0] << endl;
		bool test = ruleEvalHelper(r->components[i][0], nextActor);
		cout << "operateAND: Name=" << r->components[i][0] << "| Test=" << test << endl;
		if (test == false) return false;
		else finalValue = finalValue && test;
	}
	cout << "RULEEVAL: finalValue: " << finalValue << endl;
	return finalValue;
}

bool Query::ruleEvalHelper(string name, vector<string> actors) {
	cout << "EVALHELPER: " << name << endl;
	if (factEvaluate(actors, name)) {
		cout << "Found in KB" << endl;
		return true;
	}
	else {
		if (rb->rules.count(name) == 1) return ruleEvaluate(rb->rules[name],actors);
		else return false;
	}
}

void Query::traverse(vector<string> actor, vector<int> currActor, vector< vector<string> > actorList, map<int,vector<string>> * bindings) {
	vector< vector<string> > result;
	int counter = 0;

	//cout << "TRAVERSE: Actorlist.size=" << actorList.size() << endl;
	//cout << "TRAVERSE: Actorlist[0].size=" << actorList[0].size() << endl;
	//cout << "TRAVERSE: actor.size=" << actor.size() << endl;
	//cout << "TRAVERSE: currActor=" << currActor.size() << endl;

	int initSize = actorList[0].size();
	bool invalid = false;
	for (int i = 0; i < initSize; i++) {
		//cout << "TRAVERSE: initSize=" << initSize << endl;
		int actorCounter = 0;
		//cout << "WHY WON'T COUNTER FUCKING DO SOMETHING counter="<< counter << endl;
		for (int j = 0; j < actorList.size(); j++) {
			//cout << "TRAVERSE: actorList[j][i]=" << actorList[j][i] << endl;
			//cout << "TRAVERSE: actorCounter=" << actorCounter << endl;
			//cout << "TRAVERSE: currActor[actorCounter]=" << currActor[actorCounter] << endl;
			if (actorList[j].size() < initSize) {
				invalid = true;
				break;
			}
			else if (actor[currActor[actorCounter]] == "_") {
				//cout << "TRAVERSE: currActor[actorCounter]=" << currActor[actorCounter] << endl;
				//if (checkBindings(bindings, actorList[j][i], i, currActor[actorCounter])){ 
				//	(*bindings)[currActor[actorCounter]].push_back(actorList[j][i]); 
				//	actorCounter++;
				//	cout << "TRAVERSE: pushback " << actorList[j][i] << "  on col " << i << "  row  " << j <<  endl;
				//}
				//else {
				//	counter--;
				//	break;
				//}
				(*bindings)[currActor[actorCounter]].push_back(actorList[j][i]);
			}
			else if (actor[currActor[actorCounter]] == actorList[j][i]) {
				//if (checkBindings(bindings, actorList[j][i], i, currActor[actorCounter])) {
				//	(*bindings)[currActor[actorCounter]].push_back(actorList[j][i]);
				//	actorCounter++;
				//	cout << "TRAVERSE: pushback " << actorList[j][i] << "  on col " << i << "  row  " << j << endl;
				//}
				//else counter--;
				(*bindings)[currActor[actorCounter]].push_back(actorList[j][i]);
				break;
			}
			else {
				invalid = true;
				break;
			}
		}
		if (invalid == true)break;
		counter++;
		//cout << "WTF WHYYYYYYYY" << endl;
	}
}

bool Query::checkBindings(map<int, vector<string>> * binding, string name, int expectedColumn, int expectedRow){
	//cout << "CHECKBINDINGS: Counter:"<< expectedColumn << endl;
	if (binding->size() == 0) return true;
	else if (binding->count(expectedRow) == 0){
		for (map<int, vector<string>>::iterator it = binding->begin(); it != binding->end(); it++){
			//cout << "CHECK: it->first=" << it->first << "|expectedRow=" << expectedRow << "|expectedColumn" << expectedColumn << "|it->second[*expectedColumn]=" << it->second[expectedColumn] << "|name=" << name << endl;
			if (it->second[expectedColumn] == name){
				releaseBindings(binding, expectedColumn);
				return false;
			}
		}return true;
	}
	else {
		for (map<int, vector<string>>::iterator it = binding->begin(); it != binding->end();  it++){
			//cout << "CHECK: it->first=" << it->first << "|expectedRow=" << expectedRow << "|expectedColumn" << expectedColumn << "|it->second[*expectedColumn]=" << it->second[expectedColumn] << "|name=" << name << endl;
			if (it->first != expectedRow && it->second[expectedColumn] == name){
				releaseBindings(binding, expectedColumn);
				return false;
			}
		}return true;
	}
}

void Query::releaseBindings(map<int, vector<string>> *binding, int target){
	//cout << "RELEASE: GAAAAAH target=" << target << endl;
	for (map<int, vector<string>>::iterator it = binding->begin(); it != binding->end(); it++){
		if(it->second.size() >= target) it->second.erase(it->second.begin()+target);
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
		cout << "ERASEDUPLICATES: buffersize=" << buffer.size() << endl;
		
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