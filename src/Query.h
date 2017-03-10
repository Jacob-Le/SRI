
#pragma once
#include <string>
#include <vector>
#include "RB.cpp"
//#include "KB.cpp"

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

	
	vector<string> varMapping;
 	void CreateVarMapping(Rule* R);
 	
 	map<string, vector<string> > VarBounds;
 	void CreateVarBoundsMaster(Rule* R);
 	void CreateVarBounds(vector<Predicate*>* Facts);
 	string VarBoundstoString();
	void inference(Rule* r);
	
	//FACT--------------------------------------------------------------------------
	vector<Predicate*>* listFact(KB* Knowledge, string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	//void listSimpleRule(/*something*/);
	void printResults();
	vector<Predicate*> concatenate(vector<Predicate*>* resultA, vector<Predicate*>* resultB);
	vector<Predicate*> preventDupes(vector<Predicate*>* A, vector<Predicate*> B);


	//Part 3: evaluate Rules -------------------------------------------------------
	bool enact(Rule * r, vector<string> s, KB * kb);

	void CreatePredNames(Rule* r);
	vector< vector<Predicate*>*> KBSlice(KB* kb);
	vector<string> Bind(KB* KnowledgeBase);
	vector<int> BuildID();


};
