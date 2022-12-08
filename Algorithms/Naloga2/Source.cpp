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

void KMPNext(int* kmpNext, const string iskanNiz) {
	kmpNext[0] = -1;
	kmpNext[1] = 0;

	for (int i = 2; i < iskanNiz.length(); i++) {
		kmpNext[i] = kmpNext[i - 1] + 1;
		while (kmpNext[i] > 0 && iskanNiz[i] != iskanNiz[kmpNext[i] - 1])
			kmpNext[i] = kmpNext[kmpNext[i] - 1] + 1;
	}
}

void KMP(string vhodnoBes, int* kmpNext, string niz, vector<int>& indexes) {
	int i = 0;
	for (int j = 0; j < vhodnoBes.length() || j > vhodnoBes.length(); j++) {
		while (niz[i] != '\0') {
			if (niz[i] != vhodnoBes[j + i]) {
				j += i - kmpNext[i];
				i = 0;
				break;
			}
			i++;
		}
		if (niz == vhodnoBes.substr(j, niz.length())) {
			indexes.push_back(j);
			j += niz.length();
		}
	}
}

void izpis(int* kmpNext, vector<int>indexes, int size) {
	ofstream output("out.txt");

	for (int i = 0; i < size; i++)
		output << kmpNext[i] << ' ';
	output << '\n';
	for (auto index : indexes)
		output << index << " ";
}

int main(int argc, const char* argv[]) {
	if (argc != 3) return -1;

	string vhodnoBes = inputText(argv[2]);
	vector<int>indexes;


	string iskanNiz = argv[1];

	int* kmpNext = new int[iskanNiz.length()];
	KMPNext(kmpNext, iskanNiz);

	KMP(vhodnoBes, kmpNext, iskanNiz, indexes);
	izpis(kmpNext, indexes, iskanNiz.length());

	return 0;
}