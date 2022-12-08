#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<unsigned char>& vec, const char s[]) {
	ifstream input(s);
	int st;

	if (!input.is_open()) {
		return false;
	}

	while (!input.eof()) {
		input >> st;
		vec.push_back(st);
		while (isspace(input.peek())) input.get();
	}
	input.close();
	return true;
}

void initArray(vector<int>& array, long int size) {
	for (int i = 0; i < size; i++)
		array[i] = 0;
}

void countingSort(vector<unsigned char>& A, int k) {
	vector<unsigned char> D(A.size());
	vector<int> C(2);
	initArray(C, 2);
	for (int i = 0; i < A.size(); i++) {
		C[(A[i] >> k) & 1]++;
	}
	C[1] += C[0];
	for (int i = A.size() - 1; i >= 0; i--) {
		D[--C[(A[i] >> k) & 1]] = A[i];
	}
	swap(A, D);
}

void Izpis_Stevil(vector<unsigned char>& A, unsigned int size) {
	ofstream output("out.txt");
	for (int i = 0; i < size; i++)
		output << (int)A[i] << ' ';
}

int main(int argc, const char* argv[]) {
	vector<unsigned char> A;

	if (argc < 2) return 0;

	if (!Branje_Stevil(A, argv[1]))	return 0;
	for (int k = 0; k < 8; k++)
		countingSort(A, k);

	Izpis_Stevil(A, A.size());
	return 0;
}