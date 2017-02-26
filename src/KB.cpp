//knowledge base//
#include <vector>

using namespace std;

class KB{
public:
	//map, stored facts categorized by relationship
	map <string,vector<*Fact>> FactMap;
private:
	KB();
	~KB();

	void Add(Fact * fact);
	Fact * Remove(Fact * fact); //pops fact
	Fact * Fetch(string r, vector<string> actors);
	//toString();
	//void Dump();
	//void Load();
};

//Constructor, initializes as empty
KB::KnowledgeBase(){
	map<string, vector<*Fact>> * FactMap = new map<string, vector<*Fact>>();
}

//Destructor
KB::~KB(){
	for(const auto &r : FactMap){
		delete[] FactMap[r];
	}
}

//Takes in a fact pointer (fact must be created outside of add) and adds it to
//the KB if it doesn't already exist
void KB::Add(Fact * fact){
	//checking if relationship exists in the KB
	if(FactMap.find(fact->Relationship) == FactMap.end()){ //If it doesnt exist
		vector<*Fact> v = {fact};
		FactMap[fact->Relationship] = v; //May or may not be null cuz temporary variable
	}else{ //If it does exist
		for(const auto &f : FactMap[fact->Relationship]){
			if(f->actors == fact->actors){//check if fact already exists
				cout<< "Fact already exists" << endl;
				return;
			}
		}
		//after traversing the vector and finding no matches
		FactMap[fact.Relationship].push_back(fact); //add the fact to the end of the vector
	}
}

Fact * KB::Fetch(string r, vector<string> a) throw(invalid_argument){
	for(const auto &f : FactMap[r]){
		if(f->actors == a) return f;
	}
	else return nullptr;
}

Fact * KB::Remove(Fact * fact){
	ptrdiff_t pos = find(FactMap[fact->Relationship].begin(), FactMap[fact->Relationship].begin(), fact) - FactMap[fact->Relationship].begin();
	Fact * temp = fact;
	FactMap[fact->Relationship].erase(pos);
	return temp;
}
