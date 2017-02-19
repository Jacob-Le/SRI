//Rule database

#include <stdlib.h>
#include "RB.h"

struct duplicate_rule : public exception{
  const char * msg() const throw(){
    return "duplicate rule exception";
  }
}

RB::RB(){
  std::vector<Rule> rules = null;
}

void RB::Add(Rule * r){
  try{
    for(auto const &rule : rules){
      if(rule == r) throw duplicate_rule();
    }
    rules.pushback(r);
  }catch(duplicate_rule &e){
      std::cout << e.msg() <<std::endl;
    }
}

Rule* Rule::Remove(std::string name){
  Rule * temp = nullptr;
  for(int i = 0; i < rules.size(); i++){
    if(rules[i]->name == name){
      temp = rules[i]; //MAKE SURE TO IMPLEMENT COPY CONSTRUCTOR
      rules[i].~rule();
      rules.erase(i);
    }
  }
  return temp;
}


std::string RB::toString(){
  std::string s = "";
    for(auto & rule : rules){
      rule.toString();
    }
    return s;
}

void RB::Load(std::string filepath){

}

std::string Dump(std::string filepath){

}
