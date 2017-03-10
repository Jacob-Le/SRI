#include "Predicate.h"
#include "KB.h"
#include "RB.h"

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
	vector<Fact*>* listFact(KB* Knowledge, string factKey); //used to return vector<string>

	//SIMPLE RULE-------------------------------------------------------------------
	void listSimpleRule(/*something*/);
	void printResults();
	vector<Fact*> concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB);
	vector<Fact*> preventDupes(vector<Fact*>* A, vector<Fact*> B);


	//Part 3: evaluate Rules -------------------------------------------------------
	bool enact(Rule * r, vector<string> s, KB * kb);
};
