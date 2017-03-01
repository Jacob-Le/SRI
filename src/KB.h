#include <stdlib.h>
#include <vector>
#include<map>
#include "Predicate.cpp"

using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<Fact*> > FactMap;
	KB();
	~KB();

	void Add(Fact * fact);
	void Remove(std::string r);
	Fact* Fetch(string r, vector<string> actors);
	vector<Fact*>* Find(string findKey);
	string toString();
	//void Dump();
	//void Load();
};
