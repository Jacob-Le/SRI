//Parse.h
#include<string>
#include<vector>
#include<map>
//#include "Fact.h"
//#include "RB.cpp"
#include "KB.h"
#include "Predicate.h"

class Parse{
	public:
	//RB* RuleBase;
	KB* KnowledgeBase;
	vector<(*)(const bool, const bool)> ops;
	Parse(KB* knowledgeBase); //(RB* ruleBase, KB* knowledgeBase)
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
	void AddRule(int numFcns);
};

class Ops{
	virtual bool (*AND)(bool, bool);
	virtual bool (*OR)(bool, bool);
};
