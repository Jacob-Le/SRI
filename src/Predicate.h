//Predicate.h
#include<vector>
#include<cstdarg>
#include<string>
using namespace std;

typedef struct Predicate{ //AKA FACT OR RULE, DEPENDING ON WHAT RULE IT IS CALLED IN
  string Relationship;
  std::vector<string> Actors;

  Predicate(string relationship, int argCount, ... );
  bool evaluate();
}Predicate;

typedef struct Fact : Predicate {

  std::string Relationship;
  std::vector<std::string> actors;

  Fact(std::vector<std::string> r, std::vector<std::string> name);
  bool evaluate(std::vector<std::string> actors);

};

template<typename T, typename O>
class dummy_rule : Predicate{
  std::string name;
  //Vector of predicate components (Rules or facts) that make up this rule
  std::vector<T*> components;

  //Function pointer that points to a function that emulates boolean operators
  std::vector<O*> ops;

  //Variadic constructor that accepts any number of conditions
  Rule(std::string name, const &std::vector<O*> ops, int count, ...);
  //copy and move constructors: later!

  bool evaluate();
  bool enact();

  //Operator overloads: shortcuts for calculating condition fufullment
  bool operator &&(const &dummy_rule r);
  bool operator ||(const &dummy_rule r);
};

template<typename T, typename O>
using Rule = typename Rule<T, O>::dummy_rule;
