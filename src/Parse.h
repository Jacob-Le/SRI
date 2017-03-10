//Parse.h
#include<string>
#include<vector>

//#include "Predicate.h"
//#include "KB.h"
#include "Query.cpp"


class Parse{
	public:
	RB* RuleBase;
	KB* KnowledgeBase;
	int numRuns;

	Parse(KB* knowledgeBase, RB* ruleBase); //, KB* knowledgeBase)
	std::vector<string> RuleVector;

	std::vector<string> FactVector;
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
	void AddRule(int numFcns);
};
