//Parse.h
#include<string>
#include<vector>

//#include "Query.cpp" would mean not needing to inherit KB and RB anymore
#include "KB.cpp"
#include "RB.cpp"


class Parse{
	public:
	RB* RuleBase;
	KB* KnowledgeBase;
	//Query* QQ;
	int numRuns;

	Parse(KB* knowledgeBase, RB* ruleBase);//, Query* QQ); 
	std::vector<string> RuleVector;

	std::vector<string> FactVector;
	std::vector<vector<string> > Preds;
	int searchLength(int start, int end);
	void ParsePred(string input, bool FactMode);
	void ParseRule(string input);
	int numPreds(string input);
	void ParseLine(string input);
	void ParseFile(string fileName);
	void DumpToFile(string fileName,string input);
	void ParseTerminalInput();
	void AddFact(vector<string> input);
	void AddRule(bool Logic);
};
