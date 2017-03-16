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
#include<string>

#include "Parse.h"

using namespace std;

//Constructor
//Input: Knowledge database and Rules database
//Output: void, but creates a Parse object
Parse::Parse(KB* knowledgeBase, RB* ruleBase, Query* QQ2){
	RuleBase = ruleBase;
	KnowledgeBase = knowledgeBase;
	QQ = QQ2;
	Server = false;
}

void Parse::ServerModeON(){
	Server = true;
}

void Parse::ServerModeOFF(){
	Server = false;
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
void Parse::ParsePred(string input, int Mode){
	vector<string> Entries;
	string currEntry;
	int nextLen;
	bool oneArg;
	int newName;
	int delimiter1 = input.find("(");
	string relationship = input.substr(0, delimiter1);
	//cout << relationship << endl;
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
			if(Mode == 1 || Mode == 3) Entries.push_back(currEntry); //adds to vector of components
			else{
				if(convert.count(currEntry) == 0){
					newName = convert.size();
					convert[currEntry] = newName;
				}
				Entries.push_back(to_string(convert[currEntry]));				
			}
			break;
		}
		nextLen = searchLength(delimiter1,delimiter2) -1; //determines search length
		currEntry = input.substr(delimiter1+1,nextLen); //parses out component
		//cout << currEntry << "\n";
		
		if(Mode == 1 || Mode == 3) Entries.push_back(currEntry); //adds to vector of components
		else{
			if(convert.count(currEntry) == 0){
				newName = convert.size();
				convert[currEntry] = newName;
			}
			Entries.push_back(std::to_string(convert[currEntry]));				
		}
		delimiter1 = delimiter2;
		delimiter2 = input.find(",",delimiter2+1);
	}
	//Testing print statement
	//for(int i=0; i< Entries.size(); i++) cout << Entries.at(i) << " ";
	if(Mode == 1){
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
		ParsePred(input.substr(searchStart, nextLen), 2);
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
		if(!Server){
			string fileDump = KnowledgeBase->toString();
			fileDump += RuleBase->toString();
			DumpToFile(input.substr(searchStart, nextLen+1),fileDump);
			return;
		}else{
			vector<string> TheKB = KnowledgeBase->serverToString();
			vector<string> TheRB = RuleBase->serverToString();
			//Have to do send these
			//for(int i=0; i<TheKB.size(); i++) cout << TheKB.at(i);
			//for(int i=0; i<TheRB.size(); i++) cout << TheRB.at(i);
		}
	}else if(FACT){
		ParsePred(input.substr(searchStart, nextLen+1), 1);
		return;
	}else if(RULE){
		nextLen = searchLength(searchStart, input.size());
		ParseRule(input.substr(searchStart, nextLen));
		return;
	}else if(INFE){
		//Interpretting Input
		nextLen = searchLength(searchStart, input.size());
		string ruleName = input.substr(searchStart, nextLen);
		if(RuleBase->rules.count(ruleName)==1){
			vector<string> Qinput;
			Qinput.push_back(ruleName);
			for(int i=0; i < RuleBase->rules[ruleName]->actors.size(); i++){
				Qinput.push_back("_");
			}
			for(int i=0; i< Qinput.size(); i++) cout << Qinput.at(i) << endl;
			QueryOutput = QQ->inference(Qinput);			
		}else{
			if(numPreds(ruleName) == 1){
				ParsePred(ruleName,3);
				//cout << Preds.size();
				for(int i=0; i < Preds.at(0).size(); i++) cout << Preds.at(0).at(i) << endl;
				QueryOutput = QQ->inference(Preds.at(0));
				Preds.clear();
			}
			else cout<<"No results in RuleBase for: '"<< ruleName << "'\n";
		}
		
		//Recieving Output
		if(QueryOutput.size() == 0) cout << "No results returned for " << ruleName << endl;
		else if(QueryOutput.size() == 1){
			string output = "";
			map<string, vector<string> > ::iterator it = QueryOutput.begin();
			for(int i=0; i < it->second.size(); i++){
				for(int j=0; j< it->second.at(i).size(); j++){
					output = output + it->second.at(i).at(j) + "\n";
				}
			}
		}else{
			string output = "";
			map<string, vector<string> > ::iterator it = QueryOutput.begin();
			for(; it!= QueryOutput.end(); it++){
				output = output + it->first + ":\n";
				for(int i=0; i < it->second.size(); i++){
					for(int j=0; j< it->second.at(i).size(); j++){
						output = output + it->second.at(i).at(j) + "\n";
					}
				}
			}
		cout << "From Inference: \n" << output;
		//Need to clear() QueryOutput after storing it in the KB
		}
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
	if(fileName.size() >= 5){
		if(fileName.substr(fileName.size()-4,4) != ".sri"){
			cout << "Please enter a valid .sri file\n";
			return;
		}
	}else{
		cout << "Please enter a valid .sri file\n";
		return;
	}

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
	if(fileName.size() >= 5){
		if(fileName.substr(fileName.size()-4,4) != ".sri") fileName += ".sri";
	}else{
		fileName += ".sri";
	}
	cout << fileName << endl;
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

/*int main(){
  KB* knowledge = new KB();
  RB* rules = new RB();
  //Query* query = new Query(knowledge, rules);
  Parse* Parser = new Parse(knowledge,rules);//, query);
  Parser->ParseTerminalInput();
}*/