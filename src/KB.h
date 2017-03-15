//Knowledge Base//
#include<stdlib.h>
#include<vector>
#include<map>
#pragma once

using namespace std;

template<typename Key, typename Value, unsigned int N> //unsigned
struct nestedMap{
	typedef map<Key, typename nestedMap<Key, Value, N-1>::type> type;
};

template<typename Key, typename Value>
struct nestedMap<Key, Value, 1>{
	typedef map<Key, Value> type;
};

template<typename Key, typename Value, unsigned int N> //unsigned
using FactMap = typename nestedMap<Key, Value, N>::type; 
// USE LIKE THIS FactMap<std::string, Value, N> mapName;


class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<vector<string> > > FactMap;
	KB();
	~KB();

	void Add(vector<string> theFact);
	void Remove(string name);
	string toString();
	vector<string> serverToString();
};

