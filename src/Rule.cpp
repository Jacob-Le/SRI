//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg.h>
#include "Fact.h"

template <typename T>
Rule::Rule(std::string n, int count, ...){
  std::string name = n;
  va_list cmp;
  std::vector<T> components;
  for(int i = 0; i < count, i++) components.pushback(va_arg(cmp, T));
  va_end(cmp);
}
