#pragma once

#include <stdlib.h>
#include <vector>
#include<map>
#pragma once

using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<vector<string> > > FactMap;
	KB();
	~KB();

	void Add(vector<string> theFact);
	void Remove(string name);
	string toString();
};