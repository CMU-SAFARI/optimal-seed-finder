#include "optimalSolver.h"
#include <vector>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>
#include <map>

using namespace std;

int main(int argc, const char* argv[]) {
	map <unsigned int, unsigned long long> frequencyCounter;

	OptimalSolver solver;

	if (argc == 3) {
		cout << "Loading tree " << argv[1] << " into memory.\n";
		solver.loadTree(argv[1]);
		cout << "Finished loading. \n";

		int seedNum;
		unsigned int frequency;
		//cout << "Please input number of seeds: ";
		cin >> seedNum;

		ifstream readFile;
		readFile.open(argv[2]);
		string read;

		char benchFileName[80];
		strcpy(benchFileName, argv[2]);
		char* benchName = strtok(benchFileName, ".");

		ofstream output;
		output.open( (string(benchName) + string(".hobbes") ).c_str() );

		while (seedNum > 0) {
			frequencyCounter.clear();

			readFile.clear();
			readFile.seekg(0, ios::beg);

			//Name
			getline(readFile, read);
			//Read
			getline(readFile, read);
			solver.init(read.length(), seedNum);
			//		cout << "DNA: " << read << endl;

			//Solve
			frequency = solver.solveDNA(read);
			if (frequencyCounter.find(frequency) == frequencyCounter.end() )
				frequencyCounter[frequency] = 1;
			else
				frequencyCounter[frequency]++;

			//Trash
			getline(readFile, read);
			getline(readFile, read);

			//Name
			getline(readFile, read);

			while (!readFile.eof()) {
				//Read
				getline(readFile, read);
				//			cout << "DNA: " << read << endl;

				//Solve
				if (read.find('N') == string::npos) {
					frequency = solver.solveDNA(read);
					if (frequencyCounter.find(frequency) == frequencyCounter.end() )
						frequencyCounter[frequency] = 1;
					else
						frequencyCounter[frequency]++;
				}

				//Trash
				getline(readFile, read);
				getline(readFile, read);

				//Name
				getline(readFile, read);
			}

			cout << "seedNum: " << seedNum << endl;
			output << "seedNum: " << seedNum << endl;
			for (map<unsigned int, unsigned long long>::iterator iter = frequencyCounter.begin(); iter != frequencyCounter.end(); iter++)
				output << iter->first << ": " << iter->second << endl;

			cin >> seedNum;
		}


	}
	else if (argc == 1) {
		cout << "input seedNum and readLength: " << endl;
		int seedNum;
		int readLength;
		cin >> seedNum;
		string dummy = "";
		while (seedNum > 0) {
			cin >> readLength;
			solver.init(readLength, seedNum);
			solver.feedL0();
			solver.solveDNA(dummy);
			cin >> seedNum;
		}
	}
	else
	{
		cerr << "USAGE: ./testOptimalSolver <Tree File> <Read File>" << endl;
		exit(1);
	}

//	cout << "Loading tree " << argv[1] << " into memory.\n";
//	solver.loadTree(argv[1]);
//	cout << "Finished loading. \n";
//
//	int seedNum;
//	unsigned int frequency;
//	//cout << "Please input number of seeds: ";
//	cin >> seedNum;
//
//	ifstream readFile;
//	readFile.open(argv[2]);
//	string read;
//
//	while (seedNum > 0) {
//		frequencyCounter.clear();
//
//		readFile.clear();
//		readFile.seekg(0, ios::beg);
//
//		//Name
//		getline(readFile, read);
//		//Read
//		getline(readFile, read);
//		solver.init(read.length(), seedNum);
//		//		cout << "DNA: " << read << endl;
//
//		//Solve
//		frequency = solver.solveDNA(read);
//		if (frequencyCounter.find(frequency) == frequencyCounter.end() )
//			frequencyCounter[frequency] = 1;
//		else
//			frequencyCounter[frequency]++;
//
//		//Trash
//		getline(readFile, read);
//		getline(readFile, read);
//
//		//Name
//		getline(readFile, read);
//
//		while (!readFile.eof()) {
//			//Read
//			getline(readFile, read);
//			//			cout << "DNA: " << read << endl;
//
//			//Solve
//			if (read.find('N') == string::npos) {
//				frequency = solver.solveDNA(read);
//				if (frequencyCounter.find(frequency) == frequencyCounter.end() )
//					frequencyCounter[frequency] = 1;
//				else
//					frequencyCounter[frequency]++;
//			}
//
//			//Trash
//			getline(readFile, read);
//			getline(readFile, read);
//
//			//Name
//			getline(readFile, read);
//		}
//
//		cout << "seedNum: " << seedNum << endl;
//		for (map<unsigned int, unsigned long long>::iterator iter = frequencyCounter.begin(); iter != frequencyCounter.end(); iter++)
//			cout << iter->first << ": " << iter->second << endl;
//
//		cin >> seedNum;
//	}

	return 0;
}
