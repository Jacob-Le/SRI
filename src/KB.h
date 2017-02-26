#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Fact.cpp"
using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<Fact*> > FactMap;
	KB();
	~KB();
	void Add(Fact * fact);
	Fact* Remove(Fact * fact);
	Fact* Fetch(string r, vector<string> actors);
	vector<Fact*>* Find(string findKey);
	//toString();
	//void Dump();
	//void Load();
};
