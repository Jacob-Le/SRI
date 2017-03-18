//Query.cpp
/*
	Query handles interactions between databases. Allow databases to query each other
	for truth values of targetted facts or rules.
*/
#include<iostream>
#include<cstdio>
#include<future>
#include<thread>
#include<mutex>
//#include<async>

#include "Query.h"

using namespace std;

Query::Query(KB * knowledge, RB * rules) {
	kb = knowledge;
	rb = rules;
  threadID = 0;
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
		//cout << "INFERENCE: In rulebase=" << ruleEvaluate(r,actors) << endl;
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

	//eraseDuplicates(&binding);
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
	//else if (ops == 1) return operateAND(name, actors, r);
	else return false;//placeholder
}

bool Query::operateOR(string name, vector<string> actors, Rule * r){
	std::future<bool> finalValue;
<<<<<<< HEAD
  bool truthValue = false;
  int thisID = threadID++;
=======
  bool finalTruth;
  int thisID = ++threadID;
>>>>>>> origin/master
	for (int i = 0; i < r->components.size(); i++) {
		vector<string> nextActor;
		for (int n = 1; n < r->components[i].size(); n++) {
			nextActor.push_back(actors[stoi(r->components[i][n])]);
		}
<<<<<<< HEAD
    bool test = false;
    string cmpname = r->components[i][0];
		cout << "Component name: " << cmpname << endl;
    if (rb->rules.count(cmpname) == 1){
      cout << "Rule: " << cmpname << " | Thread #" << thisID << " start" << endl;
      finalValue = std::async(std::launch::async, &Query::ruleEvaluate, this, rb->rules[cmpname], actors);
    }
		else{
    	cout << cmpname << " | Thread #" << thisID << " start" << endl;
			finalValue = async(std::launch::async, &Query::factEvaluate, this, actors, cmpname);
		}
    test = finalValue.get();
    cout << "Thread #" << thisID << " end | result: " << test << endl;
    if(test) return true;
=======
    bool truthValue = false;
		cout << "Entering EvalHelper with: " << r->components[i][0] << endl;
			cout << "EVALHELPER: " << r->components[i][0] << endl;
    if (rb->rules.count(r->components[i][0]) == 1){
      cout << "Thread #" << thisID << " start" << endl;
      finalValue = std::async(std::launch::async, &Query::ruleEvaluate, this, rb->rules[r->components[i][0]], actors);
    } 
		else{
			cout << "Found in KB" << endl;
    	cout << "Thread #" << thisID << " start" << endl;
			finalValue = async(std::launch::async, &Query::factEvaluate, this, actors, r->components[i][0]);
		}
    truthValue = finalValue.get();
    cout << "Thread #" << thisID << " end" << endl;
    if(truthValue) return true;
		cout << "RULEEVAL: finalValue: " << truthValue << endl;
>>>>>>> origin/master

		cout << "operateOR: Name=" << cmpname << "| Test=" << test << endl;
		truthValue = truthValue || test;
	}
	cout << "operateOR: finalValue: " << truthValue << endl;
	return truthValue;

}

bool Query::operateAND(string name, vector<string> actors, Rule * r){
	bool finalValue = true;
	for (int i = 0; i < r->components.size(); i++) {
		vector<string> nextActor;
		bool test = false;
		for (int n = 1; n < r->components[i].size(); n++) {
			//cout << "operateAND: Actor=" << actors[stoi(r->components[i][n])] << endl;
			nextActor.push_back(actors[stoi(r->components[i][n])]);
		}
		string cmpname = r->components[i][0];
		cout << "Component name: " << cmpname << endl;
		if (factEvaluate(nextActor, cmpname)) {
			cout << "Found in KB" << endl;
			return true;
		}else {
			if (rb->rules.count(cmpname) == 1) return ruleEvaluate(rb->rules[cmpname],nextActor);
			else return false;
		}
		cout << "RULEEVAL: finalValue: " << test << endl;
		cout << "operateAND: Name=" << r->components[i][0] << "| Test=" << test << endl;
		if (test == false) return false;
		else finalValue = finalValue && test;
	}
	//cout << "RULEEVAL: finalValue: " << finalValue << endl;
	return finalValue;
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
				actorCounter++;
			}
			else if (actor[currActor[actorCounter]] == actorList[j][i]) {
				//if (checkBindings(bindings, actorList[j][i], i, currActor[actorCounter])) {
				//	(*bindings)[currActor[actorCounter]].push_back(actorList[j][i]);
				//	actorCounter++;
				//	cout << "TRAVERSE: pushback " << actorList[j][i] << "  on col " << i << "  row  " << j << endl;
				//}
				//else counter--;
				(*bindings)[currActor[actorCounter]].push_back(actorList[j][i]);
				actorCounter++;
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


// map<string, vector<string>> Query::removeDoubles(map<string, vector<string>>  target) {
// 	map<string, vector<string>> output;
// 	//placeholder method
// 	output = target;
// 	return output;
// }
