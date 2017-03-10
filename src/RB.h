//Rule database
#pragma once


#include "FactRule.cpp"


using namespace std;

class RB{
public:
  RB();
  RB(const RB &otherRB);
  ~RB();

  std::vector<Rule*> rules;

  void Add(Rule * r);
  Rule* Remove(Rule * r);
  std::string toString();
  void Load(std::string filepath);
  std::string Dump(std::string filepath);
};
