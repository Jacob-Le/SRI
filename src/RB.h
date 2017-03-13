//Rule database
#pragma once
#include "Rule.cpp"

using namespace std;

class RB{
public:
  RB();
  RB(const RB &otherRB);
  ~RB();

  map<string, Rule*> rules;

  void Add(Rule * r);
  void Remove(string name);
  string toString();
};