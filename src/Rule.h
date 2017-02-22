//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg>
#include "Fact.h"

class Rule{
private:
  std::string name;
  Fact e1;
  Fact e2;
  bool logic;
  std::vector<rule_component> components;
public:
  Rule(Fact e1, Fact e2, std::string name);
  //copy and move constructors


  void setFacts(std::pair facts);
  void add_components(int count, ...);
  //Operator overloads
};
