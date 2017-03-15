//SRI.h
#include "Parse.cpp"

class SRI{
  public:
  KB* knowledge;
  RB* rules;
  Query* query;
  Parse* Parser;
  
  SRI();
};