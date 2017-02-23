//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg.h>
#include "Fact.h"

template <typename T, typename O>
Rule::Rule(std::string n, const &std::vector<O*> Ops, int count, ...){
  std::string name = n;
  va_list cmp;
  std::vector<T> components;
  for(int i = 0; i < count, i++) components.pushback(va_arg(cmp, T));
  std::vector<O*> ops = Ops;
  va_end(cmp);
}

boolean Rule::evaluate(){
  std::vector<bool> truths;
	for(const auto & r : components) truths.push_back(r.evaluate());
  int count = 0
  for(const auto& bool a: truths){
  	if(a != boolList[count]) return false; //This would account for ANDs and ORs CHANGE THIS
    count++;
  }
  return true;
}

bool Rule::enact(){
  if(evaluate()){
    //add to KB here
    return true;
  }
  return false;
}
