#pragma once
#include <string>
#include <vector>
#include "RB.cpp"
#include "KB.cpp"

//#include "Predicate.cpp"

using namespace std;

//Categorized according to Evie's plan
class Query {
private:
	KB * kb;
	RB * rb;
public:
	//something var currentQuery <--THE THING THAT QUERY PASSES AROUND IDK WHAT IT IS THO
	vector<string> predNames; //Relevant relationship names
	vector<string> ToBind; //Variables that need actors

	Query(KB * kb, RB * rb);

	//FACT--------------------------------------------------------------------------
	vector<Fact*>* listFact(KB* Knowledge, string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	//void listSimpleRule(/*something*/);
	void printResults();
	vector<Fact*> concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB);
	//vector<Fact*> preventDupes(vector<Fact*>* A, vector<Fact*> B);

	void inference(vector<string> newFact);
	bool ruleEvaluate(Rules * r, vector<string> actors);
	bool ruleEvalHelper(string name, vector<string> actors);
	bool factEvaluate(vector<string> actors, string name);
	vector< vector<string> > traverse(vector<string> actors, vector<string> actorList);

	//void CreatePredNames(Rule* r);
	//vector< vector<Fact*>*> PermutateAndBind(KB* kb);
	//vector<string> Bind(KB* KnowledgeBase);
	//vector<int> BuildID();

	//Part 3: evaluate Rules -------------------------------------------------------
	bool enact(Rule * r, vector<string> s, KB * kb);

};
