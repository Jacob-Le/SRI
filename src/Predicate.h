//Predicate.h
#include<vector>
#ifndef STDLIB_H
#include <stdlib.h>
#endif
#include<cstdarg>
#include<string>
using namespace std;

//AKA FACT OR RULE, DEPENDING ON WHAT RULE IT IS CALLED IN
typedef struct Predicate{
  string name;
  vector<string> components;

  //Constructors
  Predicate();
  Predicate(string name, int argCount, ... );
  Predicate(const Predicate& p);
  Predicate(Predicate && p);

  bool evaluate(vector<string> components);

  // bool (*AND)(bool one, bool two);
  // bool (*OR)(bool one, bool two);
}Predicate;

typedef struct Fact : Predicate {

  string name;
  vector<string> components;

  //Constructors
  Fact(string name, vector<string> r);
  Fact(const Fact & r);
  Fact(Fact && r);

  bool evaluate(vector<string> components);
  string toString();

}Fact;

typedef struct Rule : Predicate{
  string name;
  //Vector of predicate components (Rules or facts) that make up this rule
  vector<Predicate*> components;

  //Function pointers that point to functions that emulate boolean operators
  vector<bool (*)(bool, bool)> ops;

  //Variadic constructor that accepts any number of conditions
  Rule(string name, vector<bool (*)(bool, bool)> ops, int count, ...);
  //copy and move constructors
  Rule(const Rule & r);
  Rule(Rule && r);


  bool evaluate(vector<string> components);
  bool enact(vector<string> components);
  string toString();

  //Operator overloads: shortcuts for calculating condition fufullment
  //bool operator &&(const &Rule r);
  //bool operator ||(const &Rule r);
}Rule;
