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