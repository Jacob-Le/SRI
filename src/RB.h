//Rule database
#pragma once

using namespace std;

class RB{
public:
  RB();
  RB(const RB &otherRB);
  ~RB();

  map<string, Rule*> rules;

  void Add(Rule * r);
  Rule* Remove(Rule * r);
  string toString();
};