#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string inputText(const string& dat) {
	ifstream input(dat);
	stringstream ss;
	if (!input.is_open()) {
		return string();
	}

	ss << input.rdbuf();
	return ss.str();
}

void izpis(vector<unsigned int>indexes, vector<unsigned int> BCH) {
	ofstream output("out.txt");

	for (int i = 0; i < BCH.size(); i++)
		output << BCH[i] << ' ';
	output << '\n';
	for (auto index : indexes)
		output << index << " ";
}

void sundayAlgorithm(string x, string y, vector<unsigned int> BCH, vector<unsigned int> &indexes ,int m) {
	int i = 0;
	for(int j = 0; j < y.length() || j > y.length(); j++) {
		while (x[i] != '\0') {
			if (x[i] != y[j + i]) {
				j += BCH[y[j + m]];
				i = 0;
				break;
			}
			i++;
		}
		if (x == y.substr(j, m)) {
			indexes.push_back(j);
			j += m;
		}
	}
}


int main(int argc, const char* argv[]) {
	if (argc != 3) return -1;

	string y = inputText(argv[2]);
	string x = argv[1];
	int m = x.length();
	vector<unsigned int> BCH(256, m + 1);
	vector<unsigned int> indexes;

	for (int i = 0; i < m; i++)	BCH[x[i]] = m - i;

	sundayAlgorithm(x, y, BCH, indexes, m);
	izpis(indexes, BCH);
	return 0;
}