//Predicate.cpp
template<class t_type> Predicate<t_type>::Predicate(string relationship, t_type ... args){
  Relationship = relationship;
  Actors.push_back(args...); 
}

bool Predicate::evaluate(){
  return true;
}