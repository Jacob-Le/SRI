#include "KB.h"
#include<algorithm>
#include<iostream>
using namespace std;

KB::KB(){
	map<string, vector<vector<string> > >* FactMap;
}

//Destructor
KB::~KB(){
	FactMap.clear();
}

void KB::Add(vector<string> theFact){
	string name = theFact.at(0);
	if(FactMap.count(name) == 0){ //if fact is not already in KB
		vector<vector<string> > temp; //create vector of vector of strings
		for(int i=0; i<theFact.size(); i++){
			int j;
			if(i == theFact.size()-1) break; //because [0] is the rule name, j needs to be +1 than i, also want to run 1 less time than size of the vector
			else j = i + 1; //sets vertical level we are at
			vector<string> evenTemper; //create vector to go into the vector of vector of strings
			temp.push_back(evenTemper); //puts it onto that vector
			temp.at(i).push_back(theFact.at(j)); //populate temp
		}
		FactMap[name] = temp; //map the fact to temp
	}else{ //if it is in KB
		for(int i=0; i<FactMap[name].size(); i++){
			int j;
			if(i == theFact.size() -1) break;
			else j = i + 1;
			FactMap[name].at(i).push_back(theFact.at(j)); //add the new fact actors onto their corresponding vector
		}
	}
		
}

void KB::Remove(string r){
	if(FactMap.count(r) == 0){ //if its not there
		cout<< "'" << r << "' does not exist in Knowledge Base and so cannot be removed."<< endl;
	}else{
		FactMap.erase(r);
	}
}


//Converts Knowledge database to string
//Input: void
//Output: string representation of knowledge database
string KB::toString(){
	string output = "";
	map<string, vector<vector<string> > > ::iterator it = FactMap.begin();
	for(; it!= FactMap.end(); it++){
		cout << "j.size() =" << it->second.at(0).size() << endl;
		cout << "i.size() =" << it->second.size() << endl;
		int j = 0; //Can't do nested for loop because trying to traverse left to right then down
		while(j < it->second.at(0).size()){
			output = output + "FACT " + it->first + "(";
			for(int i=0; i< it->second.size();i++){
				cout << "[" << i<< "][" << j << "]: " << it->second.at(i).at(j) << " ";
				output += it->second.at(i).at(j);
				if(i != it->second.size()-1) output += ","; 
			}
			cout << endl; //Comment these out if want to see how navigating KB
			output += ")\n";
			j++;
			//else break; //initially had loop above in the while loop condition but it broke when j was larger than the vector indices
		}
	}
	return output;
}

//Converts Knowledge database to string
//Input: void
//Output: string representation of knowledge database
vector<string> KB::serverToString(){
	vector<string> temp;
	map<string, vector<vector<string> > > ::iterator it = FactMap.begin();
	for(; it!= FactMap.end(); it++){
		int j = 0; //Can't do nested for loop because trying to traverse left to right then down
		while(j < it->second.size()){
			string output = "";
			output = output + "FACT " + it->first + "(";
			for(int i=0; i< it->second.at(j).size();i++){
				cout << "[" << j<< "][" << i << "]: " << it->second.at(j).at(i) << " " << endl;
				output += it->second.at(j).at(i);
				if(i != it->second.size()-1) output += ","; 
			}
			//cout << endl; Comment these out if want to see how navigating KB
			output += ")\n";
			temp.push_back(output);
			//if(j < it->second.size()) j++;
			//else break; //initially had loop above in the while loop condition but it broke when j was larger than the vector indices
			j++;
		}
	}
	return temp;
}


/*int main(){
	KB* Keiba = new KB();
	vector<string> Father1 = {"Father","Tom","Blake"};
	vector<string> Father2 = {"Father","Tom","Brake"};
	vector<string> Mother1 = {"Mother","Jane","Bruce"};
	Keiba->Add(Father1);
	Keiba->Add(Father2);
	Keiba->Add(Mother1);
	cout << Keiba->toString();
	Keiba->Remove("Father");
	Keiba->Remove("Dinosaur");
	cout << Keiba->toString();
}*/

