#include "sumo.h"
#include "socket/ClientSocket.h"
#include "socket/SocketException.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

ClientSocket client_socket("localhost", 30000);

void split(string str, string delim, vector<int> *results){
	int cutAt;
	while((cutAt = str.find_first_of(delim)) != str.npos){
		if(cutAt > 0) results->push_back(atoi(str.substr(0, cutAt).c_str()));
		str = str.substr(cutAt + 1);
	}
	
	if(str.length() > 0) results->push_back(atoi(str.c_str()));
}

string generateOutput(){
	// MotorLeft:MotorRight:LED
	ostringstream msg;
	msg << (int)engine[ENGINE_LEFT].getPower() << ":" 
		<< (int)engine[ENGINE_RIGHT].getPower() << ":" << 0 << endl;
	return msg.str();
}

void parseInput(string in){
	// Switch1:Switch2:Ground1:Ground2:Ground3:Ground4
	vector<int> items;
	split(in, ":", &items);
	for(int i=0; i<4; i++) setb(ground, items[i+2]);
}

void simulate(){
	try {
		string in;
		try {
			client_socket << generateOutput();
			client_socket >> in;
			parseInput(in);
		} catch (SocketException &) {}
		
	} catch (SocketException &e){
		cout << "Exception was caught: " << e.description() << endl;
	}
}