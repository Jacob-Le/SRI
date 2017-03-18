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
	//vector<Fact*>* listFact(KB* Knowledge, string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	//void listSimpleRule(/*something*/);
	//void printResults();
	//vector<Fact*> concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB);
	//vector<Fact*> preventDupes(vector<Fact*>* A, vector<Fact*> B);

	map<string, vector<vector<string>> > inference(vector<string> newFact);
	bool ruleEvaluate(Rule * r, vector<string> actors);
	bool operateOR(string name, vector<string> actors, Rule * r);
	bool operateAND(string name, vector<string> actors, Rule * r);
	//bool ruleEvalHelper(string name, vector<string> actors);
	bool factEvaluate(vector<string> actors, string name);
	void traverse(vector<string> actor, vector<string> * currComponent, int currSet, map<int, vector<string>> * bindings, vector<string> * tracker);
	void eraseDuplicates(map<int, vector<string>> * binding);
	void remove(int index, map<int, vector<string>> * binding);
};