#include <stdlib.h>
#include <vector>
#include<map>

using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	std::map <string, vector<Fact*> > FactMap;
	KB();
	~KB();

	void Add(Fact * fact);
	Fact* Remove(Fact * fact);
	void Remove(string f);
	Fact* Fetch(string r, vector<string> actors);
	vector<Fact*>* Find(string findKey);
	string toString();
	bool Exists(string r);
};
