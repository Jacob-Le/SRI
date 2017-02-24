
//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg.h>
#include "Fact.h"

template <typename T, typename O>
Rule::Rule(std::string n, const &std::vector<O*> Ops, int count, ...){
  std::string name = n;
  va_list cmp;
  std::vector<T*> components;
  for(int i = 0; i < count, i++) components.pushback(va_arg(cmp, T));
  std::vector<O*> ops = Ops;
  va_end(cmp);
}

bool Rule::evaluate(std::vector<std::string> actors){
  Predicate first = components[0]; // LHS component to be evaluated
  Predicate next = components[1]; // RHS component to be evaluated

  //range of actors to take from actors vector
  std::vector<std::string> range = std::vector<std::string>(components.begin(), components.begin() + first.components.size());

  bool truth = first.evaluate(range); //evaluate using the range of actors that pertain to the particular component
  int count = 0;
  while(next != null && count + 1 <= actors.size()){
    //Take range of actors for the next vector
    std::vector<std::string> next_range = std::vector<std::string>(range.end(), range.end() + next.components.size());
    bool temp = (*ops[count])(first, next.evaluate(next_range)); //Perform boolean operation using function pointer
    first = temp;
    count += 1;
    next = comp[count]; //advance to next one
  }
  return first;
}

bool Rule::enact(){
  if(evaluate()){
    //KB.add(Fact(this->name, &a, &b));
    return true;
  }
  return false;
}

bool Rule::operator && (const &Rule r){
  return this->evaluate() && r.evaluate();
}

bool Rule::operator || (const &Rule r){
  return this->evaluate() || r.evaluate();
}
