//Predicate.cpp
#include "Predicate.h"

Predicate::Predicate(string relationship, int argCount, ... ){
  Relationship = relationship;
  va_list args;
  va_start(args, argCount);
  for(int i=0; i<argCount; i++) Actors.push_back(va_arg(args,string));
  va_end(args);
}

bool Predicate::evaluate(){
  return true;
}

//Constructor
Fact::Fact(std::vector<std::string> a, std::string name){
  std::vector<std::string> actors = a;
  std::string Relationship = name;
}

bool Fact::evaluate(std::vector<std::string> actors){
  try{
    if(this == KB.fetch(Relationship, actors)) return true;
  }
  catch(std::invalid_argument){
    std::cout << "ERROR: Fact does not exist" + "\n" << endl;
    return false;
  }
  return false;
}

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
