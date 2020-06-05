// This code includes:
// Reading files, parsing strings, differnt ways of accessing vectors, const and references intro, using accumulate to get sum


#include <iostream>
#include <vector>
#include<string>
#include <fstream>
#include <sstream>    //streamin strings into temp variables for parsing
#include <numeric>    //for accumulate 


using std::string;
using std::cout;
using std::vector;
using std::ifstream;
using std::istringstream;  //streaming strings into temp variables for parsing


void PrintBoardData(const vector<vector <int>> &b) {
	for (auto i : b) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}
}


void ReadBoardFile(string path) {
	ifstream myfile(path);

	if (myfile){
		string line;
		while (getline(myfile, line)) {
			cout << line << "\n";
		}
	}
}

void ProcessString(string s) {
	istringstream mystream(s);

	int n;
	char c;
	cout << "\nfrom ProcessString: \n";

	while (mystream >>n>> c) {
	
			cout << n << " " << c << std:: endl;
	}
	cout << "unsuccessful!";
	cout << std::endl;

}

void AdditionFunction(const vector<int> &v) {         //taking reference of v and making it const so that we dont change it
	int sum = 0;

	//style 1: Ranges based for loop
	for (const int &i : v) {
		sum += i;
	}

	int sum1 = 0;
	//style 2 iterating throgh the size
	for (int i = 0; i < v.size(); i++) {
		sum1 += v[i];
	}

	//Style3: Using a accumalator 
	cout << std::accumulate(v.begin(),v.end(), 0);       // this line can be replaced in the place of the function call and we dont need a add function anymore
	cout << sum << std::endl;
	cout << sum1 << std::endl;
}


int main() {
	vector<vector<int>> myvec{ { 1,2,3,4},{4,3,2,1}};
	vector < int> twodvec{ 1,2,3,4 };
	myvec.push_back({ 5 });

	for (auto i : myvec) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}

	cout << myvec.size() << std::endl;


	vector<vector<int>> boardA{ {0, 1, 0, 0, 0, 0},
								{0, 1, 0, 0, 0, 0},
								{0, 1, 0, 0, 0, 0},
								{0, 1, 0, 0, 0, 0},
								{0, 0, 0, 0, 1, 0} };
	PrintBoardData(boardA);
	ReadBoardFile("1.board");
	ProcessString("1,2,3");

	AdditionFunction(twodvec);
}