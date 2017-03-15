//Client.cpp
#include<fstream>
#include<iostream>

#include "Client.h"
using namespace std;

void Client::UploadFile(string fileName){
	if(fileName.size() >= 5){
		if(fileName.substr(fileName.size()-4,4) != ".sri"){
			cout << "Please enter a valid .sri file\n";
			return;
		}
	}else{
		cout << "Please enter a valid .sri file\n";
		return;
	}

	string input;
	fstream file;
	file.open(fileName.c_str(),std::fstream::in);
	cout<<"Inputting From File: "<< fileName << endl;
	
	while(!file.eof()){
	  getline(file,input);
	  if(input.size() == 0) break;
	  //ParseLine(input); Send to the server
	}
	file.close();
}