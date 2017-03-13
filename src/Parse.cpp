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
Parse::Parse(KB* knowledgeBase, RB* ruleBase){//, Query* QQ2){
	RuleBase = ruleBase;
	KnowledgeBase = knowledgeBase;
	//QQ = QQ2;
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
void Parse::ParsePred(string input, bool factMode){
	vector<string> Entries;
	string currEntry;
	int nextLen;
	bool oneArg;
	int delimiter1 = input.find("(");
	string relationship = input.substr(0, delimiter1);
	Entries.push_back(relationship);

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
			//cout << currEntry << "\n";
			Entries.push_back(currEntry);
			break;
		}
		nextLen = searchLength(delimiter1,delimiter2) -1; //determines search length
		currEntry = input.substr(delimiter1+1,nextLen); //parses out component
		//cout << currEntry << "\n";
		Entries.push_back(currEntry); //adds to vector of components
		delimiter1 = delimiter2;
		delimiter2 = input.find(",",delimiter2+1);
	}
	//Testing print statement
	//for(int i=0; i< Entries.size(); i++) cout << Entries.at(i) << " ";
	if(factMode){
		AddFact(Entries);
	}else{
		Preds.push_back(Entries);
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
	bool Logic;

	for (int i = 0; i < numRuns; i++) {

		if( i == 0 ){
			searchStart = 0;
			searchEnd = input.find(")",0);
		}else{
			searchStart = searchEnd + 2;
			searchEnd = input.find(")", searchEnd + 1);
		}
		if (searchEnd == -1) searchEnd = input.size()-1;

		//Gets Logic Operator and updates searchStart past it
		if (i == 1) {
			//Logical Operator
			if (input[searchStart] == '-') {
				if (input[searchStart + 2] == 'A') {
					Logic = 1;
					searchStart += 6;
				}
				else if (input[searchStart + 2] == 'O') {
					Logic = 0;
					searchStart += 5;
				}
			}
		}
		nextLen = searchLength(searchStart, searchEnd);
		ParsePred(input.substr(searchStart, nextLen), false);
	}

	AddRule(Logic);
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
		ParsePred(input.substr(searchStart, nextLen+1), true);
		return;
	}else if(RULE){
		nextLen = searchLength(searchStart, input.size());
		ParseRule(input.substr(searchStart, nextLen));
		return;
	}else if(INFE){
		/*nextLen = searchLength(searchStart, input.size());
		if(RuleBase->rules.count(input.substr(searchStart, nextLen))==0){
			vector<string> input;
			input.push_back(RuleBase->rules[index]->name);
			for(int i=0; i < RuleBase->rules[index]->actors.size(); i++){
				input.push_back("");
			}
			QQ->inference(input);
		}else{
			if(numPreds == 1){
				ParsePred(input.substr(searchStart, nextLen),false);
				QQ->inference(Preds.at(0));
				Preds.clear();
			}
			else cout<<"No results in RuleBase for: '"<< input.substr(searchStart, nextLen) << "'\n";
		}*/
	}else{ //DROP
		string searchingFor = input.substr(searchStart, nextLen);
		bool CheckFactinKB = KnowledgeBase->FactMap.count(searchingFor);// == 0;
		bool CheckRuleinRB = RuleBase->rules.count(searchingFor);

		if(CheckFactinKB){
			KnowledgeBase->Remove(searchingFor);
		}
		if(CheckRuleinRB){
			RuleBase->Remove(searchingFor);
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
	  if(input.size() == 0) break;
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
void Parse::AddFact(vector<string> f){
	KnowledgeBase->Add(f);
}

//Creates rule from FactVector, Logic, and Relationship and puts it into the RB
//Input: int representing number of functions in rule
//Output: void
void Parse::AddRule(bool Logic) {

	string fcnName = Preds.at(0).at(0);
	vector<string> enactVars;
	for(int i=1; i< Preds.at(0).size(); i++){
		string temp = Preds.at(0).at(i);
		enactVars.push_back(temp);
	}
	
	//Delete the input Pred so doesn't go into the components
	Preds.erase(Preds.begin());

	Rule * newRule = new Rule(fcnName, Logic, enactVars, Preds); 
	RuleBase->Add(newRule);
	Preds.clear();
}

int main(){
  KB* knowledge = new KB();
  RB* rules = new RB();
  //Query* query = new Query(knowledge, rules);
  Parse* Parser = new Parse(knowledge,rules);//, query);
  Parser->ParseTerminalInput();
}
