
//Rules that the SRI engine uses to make inferences

#include <cstdlib>
#include <cstdarg>
//#include "Fact.h"

using namespace std;

template <typename T, typename O>
Rule::Rule(string n, const &vector<O*> Ops, pair int count, ...){
  string name = n;
  va_list cmp;
  vector<T*> components;
  for(int i = 0; i < count, i++) components.pushback(va_arg(cmp, T));
  vector<O*> ops = Ops;
  va_end(cmp);
}

bool Rule::evaluate(vector<string> actors){
  Predicate first = components[0]; // LHS component to be evaluated
  Predicate next = components[1]; // RHS component to be evaluated

  //range of actors to take from actors vector
  vector<string> range = vector<string>(components.begin(), components.begin() + first.components.size());

  bool truth = first.evaluate(range); //evaluate using the range of actors that pertain to the particular component
  int count = 0;
  while(next != null && count + 1 <= actors.size()){
    //Take range of actors for the next vector
    vector<string> next_range = vector<string>(range.end(), range.end() + next.components.size());
    bool temp = (*ops[count])(first, next.evaluate(next_range)); //Perform boolean operation using function pointer
    first = temp;
    count += 1;
    next = comp[count]; //advance to next one
  }
  return first;
}

bool Rule::enact(vector<string> actors){
  if(evaluate(actors)){
    KB.add(new Fact());
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
