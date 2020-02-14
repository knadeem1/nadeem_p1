#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;
/*
class Simulation{
	public:
		void readingInput(char*,char*);
		void nfa(int, string, vector<int>, multimap<int,pair<string,string>>);
};	
*/

void nfa(int startState, string input, vector<int> acceptStates, multimap<int,pair<string,string>> transitions){
	vector<int> current;
	current.push_back(startState);

	for(char c:input){
		vector<int> next;
		for(int i:current){
			for(auto itr = transitions.begin(); itr != transitions.end(); itr++){
				if(itr->first == i){
					string str(1,c);
					if((itr->second).first == str){ 
						int n = stoi((itr->second).second);
						next.push_back(n);
					}
				}
			}
		}
		current.clear();
		current = next;
	}

	vector<int> intersection;
	bool check = false;
	for(int state:acceptStates){
		for(int i:current){
			if(state == i){
				for(int y=0;y<intersection.size();y++){
					if(state==intersection.at(y)){
						check = true;
					}
				}
				if(!check){
					intersection.push_back(state);
				}
			}
			check = false;
		}
	}

	if(!intersection.empty()){
		cout<<"accept ";
		for(int i:intersection){
			cout<<i;
			cout<<" ";
		}
		cout<<endl;
	} else{
		cout<<"reject ";
		for(int i:current){
			cout<<i;
			cout<<" ";
		}
		cout<<endl;
	}

}

void readingInput(char* argv1, char* argv2){
		
	//cout<< "argv[1] = " << argv1 <<endl;
	
	ifstream infile(argv1);

	int i = 0;
	vector<string> vars;
	vector<int> acceptStates;
	int startState = 0;
	multimap<int,pair<string,string>> transitions;

	if (infile.is_open() && infile.good()){
		//cout<<"File is open\n";
		string line = "";
		while (getline(infile, line)){
			istringstream ss(line);
			string var;
			//vector<string> vars;
			while(getline(ss,var,'\t')){
				//ss.ignore();
				vars.push_back(var);
			}
			
			if(vars.at(0) == "state"){
				if(vars.size() == 3){
					if(vars.at(2) > "start"){
						startState = stoi(vars.at(1));
					} else if(vars.at(2) > "accept"){
						int s = stoi(vars.at(1));
						acceptStates.push_back(s);
					} else if(vars.at(2) > "acceptstart"){
						startState = stoi(vars.at(1));
						acceptStates.push_back(startState);
					}
				} else if(vars.size() == 4){
					startState = stoi(vars.at(1));
					acceptStates.push_back(startState);
				}
			} else if(vars.at(0) == "transition"){
				int key = stoi(vars.at(1));
				pair<string,string> val(vars.at(2),vars.at(3));
				transitions.insert({key,val});
			}

			vars.clear();
		}
	} else{
		cout<<"Failed to open\n";
	}

	//infile.close();

	string input(argv2);

	nfa(startState, input, acceptStates, transitions);

}

int main(int argc, char* argv[]){
	
	readingInput(argv[1], argv[2]);

	return 0;
}

