#pragma once
#include <string>
#include <vector>
//#include "KB.cpp"
using namespace std;

//Categorized according to Evie's plan
class Query {
	public:
	//something var currentQuery <--THE THING THAT QUERY PASSES AROUND IDK WHAT IT IS THO

	Query();

	//FACT--------------------------------------------------------------------------
	vector<Fact*>* listFact(KB* Knowledge, string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	void listSimpleRule(/*something*/);
	vector<string> concatenate(vector<string> resultA, vector<string> resultB);
};