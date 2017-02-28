//knowledge base//
#include<map>

using namespace std;

class KnowledgeBase{
	
	KnowledgeBase();
	~KnowledgeBase();
	//map, stored facts categorized by relationship
	std::map <string,Node> FactMap;
	void Add(Fact fact*);
	Fact Remove(Fact fact);
	Fact Fetch();
	//toString();
	//void Dump();
	//void Load();
	
};

/* KnowledgeBase::KnowledgeBase(){
	

	
} */

void KnowledgeBase::Add(Fact* fact){
	
	//checking if relationship exists in the KB
	if(FactMap.find(fact.Relationship) == FactMap.end()){ //If it doesnt exist
		
		vector<Fact> v = {fact};
		FactMap[fact.Relationship] == v;
		
	}else if(FactMap.find(fact.Relationship) != FactMap.end()){ //If it does exist
		
		for(int i = 0; i<v.size(); i++){ 
			
			if(fact.Actor1 = v[i].Actor1 && fact.Actor2 = v[i].Actor2){//check if fact already exists
				cout<< "Fact already exists" << endl;
				return 0; //this is probably wrong
			}
		}
		//after traversing the vector and finding no matches
		v.push_back(fact); //add the fact to the end of the vector
		
	}
}

Fact KnowledgeBase::Remove(Fact fact*){
	
	int temp = 0;
	for(int i = 0; i<FactMap[fact.Relationship].size(); i++){
		if(FactMap[fact.Relationship][i].Actor1 = fact.Actor1 && FactMap[fact.Relationship][i].Actor2 = fact.Actor2){
			return temp;
		}
		temp++;
	}
	FactMap[fact.Relationship].erase(temp);
	
}