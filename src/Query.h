#pragma once
#include <string>
#include <vector>
#include "KB.h"

//Categorized according to Evie's plan
class Query {
	//something var currentQuery <--THE THING THAT QUERY PASSES AROUND IDK WHAT IT IS THO

	Query();

	//FACT--------------------------------------------------------------------------
	std::vector<std::string> listFact(std::string factKey);

	//SIMPLE RULE-------------------------------------------------------------------
	void listSimpleRule(/*something*/);
	std::vector<std::string> concatenate(std::vector<std::string> resultA, std::vector<std::string> resultB);
}