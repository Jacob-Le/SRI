//Rule.h
#pragma once
#include <vector>
#include <string>

using namespace std;

//Rules are made up of components (which can be either other rules or facts)
typedef struct Rule{

  //String name of the rule
  string name;
  //Logical operator represented by an int (OR = 0, AND = anything else)
  int ops;
  //Vector of strings representative of actors involved in the rule
  vector<string> actors;
  //Vector of predicate components (Rules or facts) that make up this rules
  vector<vector<string> > components;

  Rule();
  //Variadic constructor that accepts any number of conditions
  Rule(string name, int ops, const vector<string> actors, vector<vector<string> > cmps);
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