#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
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

int minElement(int* array, unsigned int size) {
	int min = array[0];
	for (int i = 0; i < size; i++) {
		if (array[i] < min)
			min = array[i];
	}
	return min;
}

int maxElement(int* array, unsigned int size) {
	int max = array[0];
	for (int i = 0; i < size; i++) {
		if (array[i] > max)
			max = array[i];
	}
	return max;
}

void initArray(int* array, long int size) {
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
}

void Izpis_Stevil(int* array, unsigned int size) {
	ofstream output("out.txt");

	for (int i = 0; i<size; i++)
		output << array[i] << ' ';
}

int main(int argc, const char* argv[]) {
	vector<int> A;

	if (argc < 3) return 0;
	if (!Branje_Stevil(A, argv[2])) return 0;

	int min = minElement(&A[0], A.size());
	int max = 0;
	int* C;
	int* B = new int[A.size()];

	if (argv[1][0] == '0') {
		//counting sort
		if (min < 0) {
			for (int i = 0; i < A.size(); i++) {
				A[i] += (min * -1);
			}
			max = maxElement(&A[0], A.size());
			C = new int[max + 1];
			initArray(C, max+1);
			for (int i = 0; i < A.size(); i++) {
				C[A[i]]++;
			}
			for (int i = 1; i < max + 1; i++) {
				C[i] += C[i - 1];
			}
			for (int i = A.size()-1; i >= 0; i--) {
				B[C[A[i]] - 1] = A[i];
				C[A[i]]-=1;
			}
			for (int i = 0; i < A.size(); i++) {
				B[i] += min;
			}
		}
		else {
			max = maxElement(&A[0], A.size());
			C = new int[max + 1];
			initArray(C, max+1);
			for (int i = 0; i < A.size(); i++) {
				C[A[i]]++;
			}
			for (int i = 1; i < max + 1; i++) {
				C[i] += C[i - 1];
			}
			for (int i = A.size() - 1; i >= 0; i--) {
				B[C[A[i]] - 1] = A[i];
				C[A[i]] -= 1;
			}

		}
	}
	else {
		//Roman sort
		int count = 0;
		if (min < 0) {
			for (int i = 0; i < A.size(); i++) {
				A[i] += (min * -1);
			}
			max = maxElement(&A[0], A.size());
			C = new int[max + 1];
			initArray(C, max+1);
			for (int i = 0; i < A.size(); i++) {
				C[A[i]]+=1;
			}
			for (int i = 0; i < max+1; i++) {
				if (C[i] > 0) {
					for (int j = 0; j<C[i]; j++) {
						B[count] = i;
						count++;
					}
				}
			}
			for (int i = 0; i < A.size(); i++) {
				B[i] += min;
			}
		}
		else {
			max = maxElement(&A[0], A.size());
			C = new int[max + 1];
			initArray(C, max + 1);
			for (int i = 0; i < A.size(); i++) {
				C[A[i]] += 1;
			}
			for (int i = 0; i < max + 1; i++) {
				if (C[i] > 0) {
					for (int j = 0; j < C[i]; j++) {
						B[count] = i;
						count++;
					}
				}
			}
		}
	}
	Izpis_Stevil(B, A.size());
	delete[] C;
	delete[] B;
	return 0;
}
