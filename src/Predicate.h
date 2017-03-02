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
  Predicate(string name, vector<string> actors);
  Predicate(const Predicate& p);
  Predicate(Predicate && p);

  bool evaluate(vector<string> components);
  void p_swap(Predicate & one, Predicate & two);
  friend void p_swap(Predicate & one, Predicate & two);

  bool AND(bool,bool);
  bool OR(bool,bool);

  ~Predicate();

  Predicate& operator = (Predicate p);
  Predicate& operator = (Predicate && p);
}Predicate;

//Facts describe relationships between Actors
typedef struct Fact : Predicate {

  string Relationship;
  vector<string> components;

  //Constructors
  Fact();
  Fact(string name, vector<string> r);
  Fact(const Fact & r);
  Fact(Fact && r);

  bool evaluate(vector<string> components); //May need to turn to virtual later
  string toString();

  Fact& operator = (Fact f);
  Fact& operator = (Fact && f);
}Fact;

//Rules are made up of components (which can be either other rules or facts)
typedef struct Rule : Predicate{
  string Relationship;
  //Vector of predicate components (Rules or facts) that make up this rule
  vector<Predicate*> components;
  //Function pointers that point to functions that emulate boolean operators
  vector<int> ops;

  Rule();
  //Variadic constructor that accepts any number of conditions
  Rule(string name, const vector<bool> Logic, vector<Predicate*> cmps);
  //copy and move constructors
  Rule(const Rule & r);
  Rule(Rule && r);
  ~Rule();


  bool evaluate(vector<string> components);
  bool enact(vector<string> components);
  string toString();
  void r_swap(Rule & one, Rule & two);

  //Operator overloads
  Rule& operator = (Rule r);
  Rule& operator = (Rule && r);
  bool operator == (const Rule & r);
  bool operator != (const Rule & r);
}Rule;
