//Predicate.h
#pragma once
#include <vector>
#include <string>

using namespace std;

//AKA FACT OR RULE, DEPENDING ON WHAT RULE IT IS CALLED IN
typedef struct Predicate{
  string name;
  vector<string> components;

  //Constructors
  Predicate();
  Predicate(string name, vector<string> actors);
  Predicate(const Predicate& p);
  Predicate(Predicate && p);

  bool evaluate(vector<string> components);
  void p_swap(Predicate & one, Predicate & two);
  friend void p_swap(Predicate & one, Predicate & two);

  bool AND(bool,bool);
  bool OR(bool,bool);

  ~Predicate();

  Predicate& operator = (Predicate p);
  Predicate& operator = (Predicate && p);

  string toString();
  string InKBtoString();

}Predicate;


