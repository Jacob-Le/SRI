#pragma once
#include <string>
#include <vector>
//#include "KB.cpp"
using namespace std;

//Categorized according to Evie's plan
class Query {
	public:
	KB* Knowledge;
	RB* ruleBase;
	
	//something var currentQuery <--THE THING THAT QUERY PASSES AROUND IDK WHAT IT IS THO
	
	vector<string> varMapping;
	void CreateVarMapping(Rule* R);
	
	map<string, vector<string> > VarBounds;
	void CreateVarBoundsMaster(Rule* R);
	void CreateVarBounds(vector<Fact*>* Facts);
	string VarBoundstoString();

	Query(KB* Knowledge, RB* ruleBase);

	//FACT--------------------------------------------------------------------------
	vector<Fact*>* listFact(string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	void listSimpleRule(/*something*/);
	void printResults();
	vector<Fact*> concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB);
	vector<Fact*> preventDupes(vector<Fact*>* A, vector<Fact*> B);
};