#include "Producer.h"
// Constructor: initializing all data members using attribute list. Notice that we have passed the BoundedBuffer Object.
Producer::Producer(Rule * r, vector<string> actor; BoundedBuffer <bool> * p_boundedBuffer){
  rule = r;
  actors = actor;
  boundedBuffer = p_boundedBuffer;
}

void Producer::produce() { // Produce function
    //Call Evaluate here
    bool finalValue = true;
  	for (int i = 0; i < r->components.size(); i++) {
  		vector<string> nextActor;
  		for (int n = 1; n < r->components[i].size(); n++) {
  			cout << "operateAND: Actor=" << actors[stoi(r->components[i][n])] << endl;
  			nextActor.push_back(actors[stoi(r->components[i][n])]);
  		}
      cout << "EVALHELPER: " << name << endl;
  		if (factEvaluate(actors, name)) {
  			cout << "Found in KB" << endl;
  			return true;
  		}else {
  			if (rb->rules.count(name) == 1) return ruleEvaluate(rb->rules[name],actors);
  			else return false;
  		}
  		cout << "RULEEVAL: finalValue: " << truthValue << endl;
  		cout << "operateAND: Name=" << r->components[i][0] << "| Test=" << test << endl;
  		if (test == false) return false;
  		else finalValue = finalValue && test;
  	}
  	cout << "RULEEVAL: finalValue: " << finalValue << endl;
  	return finalValue;
    //Debug statement

    boundedBuffer->produce(truth); // Inject item into Bounded Buffer
}

Producer::~Producer() // Destructor
{
}
