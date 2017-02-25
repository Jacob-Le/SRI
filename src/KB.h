#include <stdlib.h>
#include <vector>
#include<map>
#include "Fact.h"

using namespace std;

class KB{
private:
	//map, stored facts categorized by relationship
	std::map <std::string, std::vector<*Fact>> FactMap;
public:
	KB();
	~KB();
	void Add(Fact * fact);
	Fact* Remove(std::string cat, int index);
	Fact* Fetch(std::string r, std::vector<std::string> actors);
	//toString();
	//void Dump();
	//void Load();
};
