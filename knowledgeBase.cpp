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

class Node{
	
	Fact* fact;
	Node* prev;
	Node* next;
	Node(Fact* fact);
	~Node();
	void setptr(Node&);
	
};

Node::Node(Fact* trufacts){
	
	fact = trufacts;
	nextptr = NULL;
	
}

Node::setptr(Node& iguana){
	
	next = iguana;
	
}

/* KnowledgeBase::KnowledgeBase(){
	

	
} */

void KnowledgeBase::Add(Fact* fact){
	
	Node current = new Node;
	
	//checking if relationship exists in the KB
	if(FactMap.find(fact.Relationship) == FactMap.end()){ //If it doesnt exist
		
		Node node(fact); //Make a new node
		FactMap[fact.Relationship] = node*; //Set relationship in map equal to node ptr
		
	}else if(FactMap.find(fact.Relationship) != FactMap.end()){ //If it does exist
		
		current = node;
		while(node.next != NULL){ //iterating through all the nodes
			
			//checking if fact already exists in KB
			if(current.Actor1 = fact.Actor1 && current.Actor2 = fact.Actor2){
				cout<< "Fact already exists" <<endl;
				break;
			}
			
			current = node.next;
		}
		//reach end of linked list, make new node to add fact
		Node nodez = new Node;
		nodez.fact = fact;
		
	}
}

Fact KnowledgeBase::Remove(Fact fact*){
	
	
	
}