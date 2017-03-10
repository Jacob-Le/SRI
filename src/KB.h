#include <stdlib.h>
#include <vector>
#include<map>
#pragma once
#include "Predicate.cpp"

using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<Fact*> > FactMap;
	KB();
	~KB();

	bool Add(Fact * fact);
	Fact* Remove(Fact * fact);
	void Remove(string f);
	vector<Fact*>* Find(string findKey);
	string toString();
};
