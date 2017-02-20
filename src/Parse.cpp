//Parse.cpp
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<fstream>
#include "Fact.cpp"
using namespace std;

//std::vector<string> Rule; Delete these?
//std::vector<string> Fact;

class Parse{
	public:
	//std::vector<string> Rule; Probably delete these
	//std::vector<string> Fact;
	std::vector<string> Relationship; //Always will be a 1:2 ratio for indices b/w these two
	std::vector<string> Entry;
	int searchLength(int start, int end);
	void ParseFunction(string input);
	int numFunctions(string input);
	void ParseLine(string input);
	void ParseFile(string fileName);
	void ParseTerminalInput();
	void AddRule();
	void AddFact(int numFcns);
};

//substr's second argument is how far from first character to search to, not from what char to 
//what char so this function calculates that
int Parse::searchLength(int start, int end){
	return end - start;
}

//Parses up to the end of "function(param,param)"
void Parse::ParseFunction(string input){

	//start parsing input
	int delimiter1 = input.find("(");
	string CurrentRuleName = input.substr(0, delimiter1);
	Relationship.push_back(CurrentRuleName);
	
	//get actors
	int delimiter2 = input.find(",",delimiter1);
	int nextLen = searchLength(delimiter1,delimiter2) -1;
	string firstEntry = input.substr(delimiter1+1,nextLen);
	Entry.push_back(firstEntry);
	
	int delimiter3 = input.find(")",delimiter2) -1;
	nextLen = searchLength(delimiter2,delimiter3);
	string secondEntry = input.substr(delimiter2+1,nextLen);
	Entry.push_back(secondEntry);
	
	cout<<input<<endl;
	
	for(int i=0; i<Relationship.size(); i++) cout<<" ["<<i<<"]: "<<Relationship[i];
	cout<<endl;
	for(int i=0; i<Entry.size(); i++) cout<<" ["<<i<<"]: "<<Entry[i];
	cout<<endl;
}

//Lets ParseLine know how many times to run ParseFunction on input
int Parse::numFunctions(string input){
	//cout << "Inside numFunctin(): "<<input << endl;
	int numOpenParens = count(input.begin(),input.end(), '(');
	return numOpenParens;	
}

//Oversees all parsing on a single line of input
void Parse::ParseLine(string input){
	int numRuns = numFunctions(input);
	//cout << numRuns;
	int searchStart = 0;
	int searchEnd = input.find(")");
	int nextLen = searchLength(searchEnd,searchStart);
	ParseFunction(input.substr(searchStart, nextLen));
	if (numRuns-1 == 0){
		cout<<"chicky nugs\n";
		return;
	}
	
	//For Rules
	for(int i=0; i<numRuns-1; i++){  
	  searchStart = searchEnd+1;
	  searchEnd = input.find(")",searchEnd+1);
	  
	  //Gets Logic Operator and updates searchStart past it
	  if(i%2 == 0){
		  //First Logical Operator
		  if(input[searchStart] == ':'){
			  if(input[searchStart+3] == 'A'){ //Need to have store as boolean in Rule Component
				cout<<"AND\n";
				searchStart += 6;
			  } 
			  else if(input[searchStart+3] == 'O'){
				cout<<"OR\n";
				searchStart += 5;
			  }
		  //If additional Logical Operator
		  }else if(input[searchStart+1] == 'A' || input[searchStart+1] == 'O'){
			  if(input[searchStart+1] == 'A'){
				cout<<"AND\n";
				searchStart += 4;
			  } 
			  else if(input[searchStart+1] == 'O'){
				cout<<"OR\n";
				searchStart += 3;
			  }
		  }
	  }
	  nextLen = searchLength(searchStart+1,searchEnd);
	  ParseFunction(input.substr(searchStart+1, nextLen));
	}
	
	
}

//Parses a file
void Parse::ParseFile(string fileName){
	string input;
	fstream file;
	file.open("Dummy.SRL",std::fstream::in);
	Relationship.clear();
	Entry.clear();
	cout<<"From File:\n";
	//cout<<input7<<endl;
	while(!file.eof()){
	  getline(file,input);
	  ParseLine(input);
	}
	file.close();
}

//Parses single line of input from terminal
void Parse::ParseTerminalInput(){
	string input;
	getline(cin, input);
	Parser.ParseLine(input6);
}

//Puts the last two entries and last relationship into a rule that goes onto the RB
void Parse::AddRule(){
	string actor1 = Entry.end();
	Entry.pop_back();
	string actor2 = Entry.end();
	Entry.pop_back;
	string relationship = Relationship.end();
	Relationship.pop_back();
	Fact newFact = new Fact(Entry[0],Entry[1],Relationship[0]);
	//Add Fact to KB once function is built
}

//Creates rule from Entries and Relationship and puts it into the RB
void Parse::AddFact(int numFcns){
	
}

main(){
	Parse Parser = Parse();
	/*string input = "GrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y)";
	string input2 = "Father(Roger,John)";
	string input3 = "GreatGrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y) AND Father($X,$Z) Parent($Z,$Y)";
	string input4 = "GrandFather($X,$Y):- OR Father($X,$Z) Parent($Z,$Y)";
	string input5 = "GreatGrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y) OR Father($X,$Z) Parent($Z,$Y)";
	Parser.ParseLine(input);
	Parser.ParseLine(input2);
	Parser.ParseLine(input3);
	Parser.ParseLine(input4);
	Parser.ParseLine(input5);
	string input6;
	getline(cin, input6);
	Parser.ParseLine(input6);*/
	Parser.ParseFile("Dummy.SRL");
}
