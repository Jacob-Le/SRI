//Parse.cpp
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#include<fstream>
#include "Parse.h"
//#include "Rule.cpp"
using namespace std;

Parse::Parse(KB* knowledgeBase){ //RB* ruleBase,
	//RuleBase = ruleBase;
	KnowledgeBase = knowledgeBase;
}

//substr's second argument is how far from first character to search to, not from what char to 
//what char so this function calculates that
int Parse::searchLength(int start, int end){
	//cout << end << "-" << start << "=" << end-start <<endl;
	return end - start;
}

void Parse::ParsePred(string input,bool factMode){
	//start parsing input
	//cout << "input in Pred: " << input << endl;
	vector<string> Entries;
	string currEntry;
	int nextLen;
	bool oneArg;
	int delimiter1 = input.find("(");
	string relationship = input.substr(0, delimiter1);
	//cout << relationship << endl;
	
	int delimiter2 = input.find(",",delimiter1); //.find() sets to -1 if not found I hope
	if(delimiter2 == -1) oneArg = true;
	int delimiter3 = input.find(")",delimiter2);
	if(delimiter3 == -1) delimiter3 = input.size();
	//cout << "when " << delimiter2 << "<" << delimiter3 << endl;
	while(delimiter2 < delimiter3){
		if(delimiter2 == -1){
			if(oneArg){
				delimiter2 = delimiter1;
			}
			delimiter1+=1;
			delimiter3;
			nextLen = searchLength(delimiter1,delimiter3);
			currEntry = input.substr(delimiter1,nextLen);
			//cout << "PredLast:" << currEntry << endl;
			Entries.push_back(currEntry);
			break;
		}
		nextLen = searchLength(delimiter1,delimiter2) -1; //determine search length
		currEntry = input.substr(delimiter1+1,nextLen); //parse out actor
		//cout << "PredLoop:" << currEntry << endl;
		Entries.push_back(currEntry); //add to vector of actors
		delimiter1 = delimiter2;
		delimiter2 = input.find(",",delimiter2+1);
	}
	if(factMode){
		Fact* newFact = new Fact(Entries, relationship);
		AddFact(newFact);
	}else{
		/*for(int i=0; i < Entries.size(); i++){
			//cout << "Entries: " << Entries.at(i) << endl;
			Entry.push_back(Entries.at(i));
		}
		if(Relationship.count(relationship) == 0){
			vector<int> temp;
			temp.push_back(Entries.size());
			Relationship[relationship] = temp;
		}else{
			vector<int>* temp = &(Relationship.at(relationship));
			//cout << temp->size();
			temp->push_back(Entries.size());
			//cout << temp->size();
		}*/
		Predicate* newPred = new Predicate(relationship,Entries);
		Preds.push_back(newPred);
	}
}

void Parse::ParseRule(string input){
	cout << "input: " << input << endl;
	//ParsePred(input,false);
	int numRuns = numPreds(input);
	int searchStart;
	int searchEnd = input.find(")",0);
	int nextLen;
	//cout << "input: " << input;
	
	for(int i=0; i<numRuns-1; i++){
	  searchStart = searchEnd+1;
	  //cout << "searchStart:" << searchStart << endl;
	  searchEnd = input.find(")",searchEnd+1);
	  if(searchEnd == -1) searchEnd = input.size(); 
	  //cout << "searchEnd:" << searchEnd <<endl;
	  
	  //Gets Logic Operator and updates searchStart past it
	  if(i%2 == 0){
		  //First Logical Operator
		  if(input[searchStart] == ':'){
			  if(input[searchStart+3] == 'A'){ //Need to have store as boolean in Rule Component
				//cout<<"AND"<<endl;
				Logic.push_back(1);
				searchStart += 6;
			  } 
			  else if(input[searchStart+3] == 'O'){
				//cout<<"OR" << endl;
				Logic.push_back(0);
				searchStart += 5;
			  }
		  //If additional Logical Operator
		  }else if(input[searchStart+1] == 'A' || input[searchStart+1] == 'O'){
			  if(input[searchStart+1] == 'A'){
				//cout<<"AND"<<endl;
				Logic.push_back(1);
				searchStart += 4;
			  } 
			  else if(input[searchStart+1] == 'O'){
				//cout<<"OR" << endl;
				Logic.push_back(0);
				searchStart += 3;
			  }
		  }
	  }
	  nextLen = searchLength(searchStart+1,searchEnd);
	  //cout << "searching: " << input.substr(searchStart+1, nextLen) << endl;
	  ParsePred(input.substr(searchStart+1, nextLen),false);
	}
	/*for(int i=0; i<Preds.size();i++){
		cout << Preds.at(i)->Relationship << endl;
		for(int j=0; j<Preds.at(i)->components.size(); j++){
			cout << Preds.at(i)->components.at(j) << endl;
		}
	}*/
	Preds.clear();
	//for(int i=0; i<Logic.size();i++) cout<<Logic.at(i)<<endl;
	Logic.clear();
}


//Lets ParseLine know how many times to run ParseFunction on input
int Parse::numPreds(string input){
	//cout << "Inside numFunctin(): "<<input << endl;
	int numOpenParens = count(input.begin(),input.end(), '(');
	return numOpenParens;	
}


//Oversees all parsing on a single line of input
void Parse::ParseLine(string input){
	
	bool LOAD = false;
	bool DUMP = false;
	bool FACT = false;
	bool RULE = false;
	bool INFE = false; //short for INFERENCE
	bool DROP = false;
	
	int numRuns = numPreds(input);
	//cout << numRuns;
	//cout<< "input: " << input <<endl;
	int searchStart = 0;
	int searchEnd = input.find(")");
	int nextLen = searchLength(searchStart, searchEnd);
	
	//Determine Command
	string command = input.substr(searchStart, 4);
	//cout << "command: " << command << endl;
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
		ParseFile(input.substr(searchStart, nextLen));
		return;
	}else if(DUMP){
		string fileDump = KnowledgeBase->toString();
		DumpToFile(input.substr(searchStart, nextLen),fileDump);
		return;
	}else if(FACT){
		ParsePred(input.substr(searchStart, nextLen), true); 
		return;
	}else if(RULE){
		//cout<< "input: "<< input << endl;
		//cout<< "nextLen: "<< nextLen << endl;
		nextLen = searchLength(searchStart, input.size());
		//cout << "searchStart:" << searchStart <<endl;
		//cout << "Before Rule:" << input << endl;
		ParseRule(input.substr(searchStart, nextLen));
		return;
	}
	/*
	ParseFunction(input.substr(searchStart, nextLen));
	if (numRuns-1 == 0){
		//cout<<"chicky nugs\n";
		AddFact();
		return;
	}
	
*/
	
}

//Parses a file
void Parse::ParseFile(string fileName){
	string input;
	fstream file;
	file.open(fileName.c_str(),std::fstream::in);
	//Relationship.clear();
	//Entry.clear();
	cout<<"From File:\n";
	while(!file.eof()){
	  getline(file,input);
	  ParseLine(input);
	}
	file.close();
}

//Called by DUMP command
void Parse::DumpToFile(string fileName,string input){
	fstream file;
	file.open(fileName.c_str(),std::fstream::out);
	file.write(input.c_str(),input.size());
	file.close();
}

//Parses single line of input from terminal
void Parse::ParseTerminalInput(){
	cout << "Enter 'q' to quit\n";
	string quit = "q";
	while(true){
		string input;
		getline(cin, input);
		//cout << input << endl;
		if(input.compare(quit) == 0) break;
		ParseLine(input);
	}
}

//Add Fact to KB once function is built
void Parse::AddFact(Fact* f){
	KnowledgeBase->Add(f);
}

//Creates rule from FactVector, Logic, and Relationship and puts it into the RB
/*void Parse::AddRule(int numFcns){
	for(int i=numFcns-1; i>0; i--){
		Fact* newFact = MakeFact();
		FactVector.push_back();
	}
	string fcnName = "";
	while(numFcns>0){
		if(numFcns == 1){
			fcnName = Relationship.end();
			Relationship.pop_back();
			numFcns--;		
		}
		Fact* Fact1 = FactVector.end();
		FactVector.pop_back();
		Fact* Fact2 = FactVector.end();
		bool logic = Logic.end();
		Logic.pop_back();
		Rule* newRule = new Rule(Fact1,Fact2,fcnName,logic);
		RuleVector.push_back(newRule);
		numFcns-=2;
	}
	Rule* domRule = RuleVector.end();
	RuleVector.pop_back();
	while(RuleVector.size()!=0){
		Rule* subRule = RuleVector.end();
		RuleVector.pop_back();
		domRule->add_components(1,subRule);
	}
	RuleBase->add(domRule);
	}
}*/

main(){
	KB* kb = new KB();
	Parse Parser = Parse(kb);
	Parser.ParseFile("Dummy.SRL");
	string input = "FACT Alive(Roger)";
	string input2 = "FACT Father(Roger,John)";
	string input3 = "FACT Triplets(Roger,John,Jake)";
	string input4 = "FACT Quadruplets(Roger,John,Jake,Peter)";
	Parser.ParseLine(input);
	Parser.ParseLine(input2);
	Parser.ParseLine(input3);
	Parser.ParseLine(input4);
	Parser.ParseTerminalInput();
	cout << kb->toString();
	//for(int i=0; i<argc; i++) cout << "["<< i << "]: " << argv[i] << " ";
	cout << endl;
}
