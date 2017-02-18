//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg.h>
#include "Fact.h"

Rule::Rule(Fact * f1, Fact * f2, std::string n){
  Fact * e1 = f1;
  Fact * e2 = f2;
  std::string name = n;
  std::vector<rule_component> components;
}

void add_components(int count, ...){
  va_list cmp;
  for(int i = 0; i < count; i++) components.pushback(va_arg(cmp, rule_component));
  va_end(cmp);
}
