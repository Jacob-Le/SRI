//Predicate.h
template<class t_type> class Predicate{ //AKA FACT OR RULE, DEPENDING ON WHAT RULE IT IS CALLED IN
  public:
  string Relationship;
  std::vector<t_type> Actors;
 
  Predicate(string relationship, t_type ... args);
  bool evaluate();
};  