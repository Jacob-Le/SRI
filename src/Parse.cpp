//Parse.cpp
/*
	This file controls the input/output and processes inputs to split them between rules
	facts, and other types. It can also be considered the moderator class that handles
	the actions of the program. There is a test main function at the bottom.
*/
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#include<fstream>

#include "Parse.h"

using namespace std;

//Constructor
//Input: Knowledge database and Rules database
//Output: void, but creates a Parse object
Parse::Parse(KB* knowledgeBase, RB* ruleBase, Query* QQ2){
	RuleBase = ruleBase;
	KnowledgeBase = knowledgeBase;
	QQ = QQ2;
}

//Function to calculate length of string
//Input: ints representing start and end
//Output: int representation between end and start
int Parse::searchLength(int start, int end){
	return end - start;
}

//Parses a predicate, used by both ParseRules and ParseFact, pushes onto Pred vector
//Input: Inputted string, boolean representing if string is Fact
//Output: void
void Parse::ParsePred(string input,bool factMode){
	vector<string> Entries;
	string currEntry;
	int nextLen;
	bool oneArg;
	int delimiter1 = input.find("(");
	string relationship = input.substr(0, delimiter1);


	int delimiter2 = input.find(",",delimiter1); //.find() sets to -1 if not found
	if(delimiter2 == -1) oneArg = true;
	int delimiter3 = input.find(")",delimiter2);
	if(delimiter3 == -1) delimiter3 = input.size();
	while(delimiter2 < delimiter3){
		if(delimiter2 == -1){
			if(oneArg){
				delimiter2 = delimiter1;
			}
			delimiter1+=1;
			delimiter3;
			nextLen = searchLength(delimiter1,delimiter3);
			currEntry = input.substr(delimiter1,nextLen);
			Entries.push_back(currEntry);
			break;
		}
		nextLen = searchLength(delimiter1,delimiter2) -1; //determines search length
		currEntry = input.substr(delimiter1+1,nextLen); //parses out component
		Entries.push_back(currEntry); //adds to vector of components
		delimiter1 = delimiter2;
		delimiter2 = input.find(",",delimiter2+1);
	}
	if(factMode){
		//for(int i=0; i< Entries.size(); i++) cout << Entries.at(i) << " ";
		Predicate* newFact = new Predicate(relationship, Entries);
		AddFact(newFact);
	}else{
		Predicate* newPred = new Predicate(relationship,Entries);
		Preds.push_back(newPred);
	}
}

//Parses an input and calls AddRule to create a rule.
//Input: Inputted string
//Output: void
void Parse::ParseRule(string input){
	int numRuns = numPreds(input);
	int searchStart;
	int searchEnd;
	int nextLen;

	for (int i = 0; i < numRuns; i++) {

		if( i ==0 ){
			searchStart = 0;
			searchEnd = input.find(")",0);
		}else{
			searchStart = searchEnd + 2;
			searchEnd = input.find(")", searchEnd + 1);
		}
		if (searchEnd == -1) searchEnd = input.size()-1;

		//Gets Logic Operator and updates searchStart past it
		if ((i+1)% 2 == 0) {
			//First Logical Operator
			if (input[searchStart] == '-') {
				if (input[searchStart + 2] == 'A') {
					Logic.push_back(1);
					searchStart += 6;
				}
				else if (input[searchStart + 2] == 'O') {
					Logic.push_back(0);
					searchStart += 5;
				}
				//If additional Logical Operator
			}
			else if (input[searchStart + 0] == 'A' || input[searchStart + 0] == 'O') {
				if (input[searchStart + 0] == 'A') {
					Logic.push_back(1);
					searchStart += 4;
				}
				else if (input[searchStart + 0] == 'O') {
					Logic.push_back(0);
					searchStart += 3;
				}
			}
		}
		nextLen = searchLength(searchStart, searchEnd);
		ParsePred(input.substr(searchStart, nextLen), false);
	}

	AddRule(numRuns);
	Preds.clear();
	Logic.clear();
}


//Parses a line of input. Counts the number of '(' there is to count components in the string.
//Input: Input string
//Output: int representation of component number
int Parse::numPreds(string input){
	int numOpenParens = count(input.begin(),input.end(), '(');
	return numOpenParens;
}


//Oversees all parsing on a single line of input. Determines what type of input it is.
//Input: input string
//Output: void
void Parse::ParseLine(string input){

	bool LOAD = false;
	bool DUMP = false;
	bool FACT = false;
	bool RULE = false;
	bool INFE = false; //short for INFERENCE
	bool DROP = false;

	numRuns = numPreds(input);
	int searchStart = 0;
	int searchEnd = input.find(")");
	int nextLen = searchLength(searchStart, searchEnd);

	//Determine Command
	string command = input.substr(searchStart, 4);
	if(command == "LOAD"){
		LOAD = true;
		searchEnd = input.size()-1;
	}else if(command == "DUMP"){
		DUMP = true;
		searchEnd = input.size()-1;
	}else if(command == "FACT") FACT = true;
	else if(command == "RULE") RULE = true;
	else if(command == "INFE"){
		INFE = true;
		searchStart+=5;
	}else if(command == "DROP") DROP = true;
	searchStart += 5;
	nextLen = searchLength(searchStart, searchEnd);

	//Enact Command
	if(LOAD){
		ParseFile(input.substr(searchStart, nextLen+1));
		return;
	}else if(DUMP){
		string fileDump = KnowledgeBase->toString();
		fileDump += RuleBase->toString();
		DumpToFile(input.substr(searchStart, nextLen+1),fileDump);
		return;
	}else if(FACT){
		ParsePred(input.substr(searchStart, nextLen), true);
		return;
	}else if(RULE){
		nextLen = searchLength(searchStart, input.size());
		//cout <<input.substr(searchStart, nextLen) << endl;
		ParseRule(input.substr(searchStart, nextLen));
		return;
	}else if(INFE){
		nextLen = searchLength(searchStart, input.size());
		int index = RuleBase->CheckIfRuleExists(input.substr(searchStart, nextLen));
		if( index != -1){
			QQ->inference(RuleBase->rules[index]);
		}else{
			cout<<"No results in RuleBase for: "<< input.substr(searchStart, nextLen) << endl;
		}
	}else{ //DROP
		string searchingFor = input.substr(searchStart, nextLen);
		bool CheckFactinKB = KnowledgeBase->FactMap.count(searchingFor);// == 0;
		Rule* temp;
		bool CheckRuleinRB = false;
		for(int i=0; i< RuleBase->rules.size(); i++){
			if(searchingFor == RuleBase->rules.at(i)->name){
				temp = RuleBase->rules.at(i);
				CheckRuleinRB = true;
				break;
			}
		}

		if(CheckFactinKB){
			KnowledgeBase->Remove(searchingFor);
		}
		if(CheckRuleinRB){

			RuleBase->Remove(temp);
		}
		if(!CheckFactinKB && !CheckRuleinRB){
			cout << searchingFor << " not in KB or RB to delete\n";
		}
		//Run query.inference here
	}

}

//Parses a file
//Input: file name
//Output: void
void Parse::ParseFile(string fileName){
	string input;
	fstream file;
	file.open(fileName.c_str(),std::fstream::in);
	cout<<"Inputting From File: "<< fileName << endl;
	while(!file.eof()){
	  getline(file,input);
	  ParseLine(input);
	}
	file.close();
}

//Called by DUMP command. Saves to file.
//Input: Filename and string input
//Output: void
void Parse::DumpToFile(string fileName,string input){
	fstream file;
	file.open(fileName.c_str(),std::fstream::out);
	file.write(input.c_str(),input.size());
	file.close();
}

//Parses single line of input from terminal
//Input: void
//Output: void
void Parse::ParseTerminalInput(){
	cout << "Enter 'q' to quit\n";
	string quit = "q";
	while(true){
		string input;
		getline(cin, input);
		if(input.compare(quit) == 0) break;
		ParseLine(input);
	}
}

//Add Fact to KB once function is built
//Input: Fact pointer f to be added
//Output: void
void Parse::AddFact(Predicate* f){
	KnowledgeBase->Add(f);
}

//Creates rule from FactVector, Logic, and Relationship and puts it into the RB
//Input: int representing number of functions in rule
//Output: void
void Parse::AddRule(int numFcns) {

	vector<Predicate*> tempPreds;
	vector<bool> tempLogic;
	string fcnName = Preds.at(0)->name;
	vector<string> enactVars;
	map<int,vector<string>> temp; //stores the rules' temp vars because rule needs to point to itself in the RB
	enactVars = Preds.at(0)->components;


	for (int i = 1; i < Preds.size(); i++){ 
		int index = RuleBase->CheckIfRuleExists(Preds[i]->name);
		if(index != -1){ //Rule
			vector<string> bluh;
			for(int j = 0; j < Preds[i]->components.size(); j++){
				bluh.push_back(Preds[i]->components.at(j));
			}
			temp[i] = bluh;
			tempPreds.push_back(RuleBase->rules.at(index));
		}else{ //Fact
			Fact* newFact = new Fact(Preds[i]->name, Preds[i]->components, KnowledgeBase);
			tempPreds.push_back(newFact);
		}
    }

	for (int i = 0; i < Logic.size(); i++) {
		tempLogic.push_back(Logic[i]);
	}

	Rule * newRule = new Rule(fcnName, enactVars, tempLogic, tempPreds, temp); 
	RuleBase->Add(newRule);

}
