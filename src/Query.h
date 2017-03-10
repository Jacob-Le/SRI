#include "RB.cpp"

using namespace std;

//Categorized according to Evie's plan
class Query {
private:
	KB * kb;
	RB * rb;
public:
	//something var currentQuery <--THE THING THAT QUERY PASSES AROUND IDK WHAT IT IS THO

	Query(KB * kb, RB * rb);

	//FACT--------------------------------------------------------------------------
	vector<Predicate*>* listFact(KB* Knowledge, string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	void listSimpleRule(/*something*/);
	void printResults();
	vector<Predicate*> concatenate(vector<Predicate*>* resultA, vector<Predicate*>* resultB);
	vector<Predicate*> preventDupes(vector<Predicate*>* A, vector<Predicate*> B);


	//Part 3: evaluate Rules -------------------------------------------------------
	bool enact(Rule * r, vector<string> s, KB * kb);
};
