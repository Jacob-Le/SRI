//Parse.h
#include<string>
#include<vector>
using namespace std;

#include "Query.cpp"
//#include "KB.cpp"
//#include "RB.cpp"


class Parse{
	public:
	RB* RuleBase;
	KB* KnowledgeBase;
	Query* QQ;
	int numRuns;

	Parse(KB* knowledgeBase, RB* ruleBase, Query* QQ); 
	vector<string> RuleVector;
	map<string,int> convert;

	vector<string> FactVector;
	vector<vector<string> > Preds;
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