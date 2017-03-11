//Predicate.h
#pragma once
#include <vector>
#include <string>

using namespace std;

//Rules are made up of components (which can be either other rules or facts)
typedef struct Rule : Predicate{

  string Relationship;
  //Vector of strings representative of actors involved in the rule
  vector<string> actors;
  //Vector of predicate components (Rules or facts) that make up this rules
  vector<string> components;
  //Function pointers that point to functions that emulate boolean operators
  vector<bool> ops;

  Rule();
  //Variadic constructor that accepts any number of conditions
  Rule(string name, const vector<string> actors, const vector<bool> Logic, vector<string> cmps);
  //copy and move constructors
  Rule(const Rule & r);
  Rule(Rule && r);
  ~Rule();

  string toString();
  void r_swap(Rule & one, Rule & two);

  //Operator overloads
  Rule& operator = (Rule r);
  Rule& operator = (Rule && r);
  bool operator == (const Rule & r);
  bool operator != (const Rule & r);
}Rule;
