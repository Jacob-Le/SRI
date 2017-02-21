//Parse.h
#include<string>
#include<vector>
#include "Fact.h"
#include "RB.cpp"

class Parse{
	public:
	RB* RuleBase;
	//KB* KnowledgeBase;
	Parse(RB* ruleBase, KB* knowledgeBase);
	std::vector<string> RuleVector; 
	std::vector<string> FactVector;
	std::vector<string> Relationship; //Always will be a 1:2 ratio for indices b/w these two
	std::vector<string> Entry;
	std::vector<bool> Logic;
	int searchLength(int start, int end);
	void ParseFunction(string input);
	int numFunctions(string input);
	void ParseLine(string input);
	void ParseFile(string fileName);
	void ParseTerminalInput();
	Fact* MakeFact();
	void AddFact();
	void AddRule(int numFcns);
};