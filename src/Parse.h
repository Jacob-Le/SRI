//Parse.h
#include<string>
#include<vector>
//#include "Fact.h"
//#include "RB.cpp"
#include "KB.cpp"

class Parse{
	public:
	//RB* RuleBase;
	KB* KnowledgeBase;
	Parse(KB* knowledgeBase); //(RB* ruleBase, KB* knowledgeBase)
	std::vector<string> RuleVector; 
	std::vector<string> FactVector;
	std::vector<string> Relationship; //Always will be a 1:2 ratio for indices b/w these two
	std::vector<string> Entry;
	std::vector<bool> Logic;
	int searchLength(int start, int end);
	void ParseFact(string input);
	void ParseFunction(string input);
	int numPreds(string input);
	void ParseLine(string input);
	void ParseFile(string fileName);
	void DumpToFile(string fileName,string input);
	void ParseTerminalInput();
	void AddFact(Fact* factptr);
	void AddRule(int numFcns);
};
