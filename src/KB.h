#pragma once

#include <stdlib.h>
#include <vector>
#include<map>
#pragma once
#include "Predicate.cpp"

using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<Predicate*> > FactMap;
	KB();
	~KB();

	bool Add(Predicate* pred);
	void Remove(string f);
	vector<Predicate*>* Find(string findKey);
	string toString();
};