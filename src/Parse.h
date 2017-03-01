//Parse.h
#include<string>
#include<vector>
#include<map>
#include "RB.cpp"//"../sources/RB.cpp"
#include "KB.cpp"//"../sources/KB.cpp"
#include "Query.cpp"//"../sources/Query.cpp"

class Parse{
	public:
	RB* RuleBase;
	KB* KnowledgeBase;
	Query* Q;
	int numRuns;
	Parse(KB* knowledgeBase, RB* ruleBase, Query* Q);
	std::vector<string> RuleVector; 
	std::vector<string> FactVector;
	//std::map<string,vector<int> > Relationship; //Maps the number of args it had
	//std::vector<string> Entry;
	std::vector<Predicate*> Preds;
	std::vector<bool> Logic;
	int searchLength(int start, int end);
	void ParsePred(string input, bool FactMode);
	void ParseRule(string input);
	int numPreds(string input);
	void ParseLine(string input);
	void ParseFile(string fileName);
	void DumpToFile(string fileName,string input);
	void ParseTerminalInput();
	void AddFact(Fact* factptr);
	void AddRule();
};
