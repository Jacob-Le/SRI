//Predicate.h
#include<vector>
#ifndef stdlib_h
#include <stdlib.h>
#endif
#include<cstdarg>
#include<string>
using namespace std;

class Ops {
public:
	virtual bool AND(const bool a, const bool b);
	virtual bool OR(const bool a, const bool b);
};


//AKA FACT OR RULE, DEPENDING ON WHAT RULE IT IS CALLED IN
typedef struct Predicate{
  string Relationship;
  vector<string> components;
  Ops * ops;

  Predicate();
  Predicate(string relationship, int argCount, ... );
  bool evaluate(vector<string> actors);
  //bool (*AND)(Predicate one, Predicate two);
  //bool (*OR)(Predicate one, Predicate two);
}Predicate;

typedef struct Fact : Predicate {

  string Relationship;
  vector<string> actors;

  Fact(vector<string> r, string name);
  bool evaluate(vector<string> actors);

}Fact;

typedef struct Rule : Predicate{
  string name;
  //Vector of predicate components (Rules or facts) that make up this rule
  vector<Predicate*> components;

  //Function pointers that point to functions that emulate boolean operators
  //vector<void (*op)(Rule, Rule)> ops;

  //Variadic constructor that accepts any number of conditions
  Rule(string name, int count, ...);
  //copy and move constructors: later!

  bool evaluate(vector<string> actors);
  bool enact(vector<string> actors);

  //Operator overloads: shortcuts for calculating condition fufullment
  //bool operator &&(const &Rule r);
  //bool operator ||(const &Rule r);
}Rule;
