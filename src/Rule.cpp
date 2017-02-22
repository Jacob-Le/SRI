//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg>
//#include "Fact.h"

Rule::Rule(Fact * f1, Fact * f2, std::string n, bool inputLogic){
  Fact * e1 = f1;
  Fact * e2 = f2;
  logic = inputLogic; //1 is AND, 0 is OR
  name = n;
  std::vector<rule_component> components;
}

void add_components(int count, ...){
  va_list cmp;
  for(int i = 0; i < count; i++) components.pushback(va_arg(cmp, rule_component));
  va_end(cmp);
}
