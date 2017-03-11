//Knowledge Base//
#include<stdlib.h>
#include<vector>
#include<map>

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
	const static int index = 2;
	FactMap<string, vector<string>, KB::index> facts;	
	

	KB();
	
	void Add(vector<string> fact);
	//void Add(FactMap<string, vector<string>, int> facts, vector<string> actors, int depth);
	void Remove(string factName);
	string toString();
	
};

