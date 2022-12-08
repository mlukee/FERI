#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

void menu() {
	cout << "Hitro uredi - Izbira:" << endl << endl;
	cout << "1) Generiraj nakljucno zaporedje" << endl;
	cout << "2) Generiraj narascujoce zaporedje" << endl;
	cout << "3) Generiraj padajoce zaporedje" << endl;
	cout << "4) Izpis zaporedja" << endl;
	cout << "5) Preveri ali je zaporedje urejeno" << endl;
	cout << "6) Uredi s hitrim urejanjem brez mediane" << endl;
	cout << "7) Uredi s hitrim urejanjem z mediano" << endl;
	cout << "8) Uredi z drugim algoritmom za urejanje" << endl;
	cout << "9) Konec" << endl << endl;
	cout << "Izbira: ";
}

void writeToFile(string line) {
	ofstream myFile("out.txt");
	if (myFile.is_open()) {
		myFile << line;
		myFile.close();
	}

}

int deliZMediano(vector<int>& array, int dno, int vrh) {
	int m = dno + (vrh - dno) / 2;
	swap(array[dno], array[m]);
	int pe = array[dno];
	int l = dno;
	int d = vrh;
	while (l <= d && d > l) {
		while (array[l] <= pe && l < vrh)
			l++;
		while (array[d] >= pe && d > dno)
			d--;
		if (l < d)
			swap(array[l], array[d]);
	}
	swap(array[dno], array[d]);
	return d;
}

void urediZIzbiranjem(vector<int>& array, unsigned int size) {
	for (int i = 0; i < size - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < array[minIndex])
				minIndex = j;
		}
		if (minIndex > i)
			swap(array[i], array[minIndex]);
	}
}

void hitro_urediZMediano(vector<int>& array, int dno, int vrh) {
	int j = 0;
	if (dno < vrh) {
		j = deliZMediano(array, dno, vrh);
		hitro_urediZMediano(array, dno, j - 1);
		hitro_urediZMediano(array, j + 1, vrh);
	}
}

int deli(vector<int>& array, int dno, int vrh) {
	int pe = array[dno];
	int l = dno;
	int d = vrh;
	while (l <= d && d > l) {
		while (array[l] <= pe && l < vrh)
			l++;
		while (array[d] >= pe && d > dno)
			d--;
		if (l < d)
			swap(array[l], array[d]);
	}
	swap(array[dno], array[d]);
	return d;
}

void hitro_uredi(vector<int>& array, int dno, int vrh) {
	int j = 0;
	if (dno < vrh) {
		j = deli(array, dno, vrh);
		hitro_uredi(array, dno, j - 1);
		hitro_uredi(array, j + 1, vrh);
	}
}

void izpisiPolje(vector<int>& array) {
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << " ";
	}
}

bool preveri(vector<int>& array, int dno, int vrh) {
	for (int i = dno; i < vrh - 1; i++) {
		if (array[i] > array[i + 1]) {
			cout << "Zaporedje ni urejeno" << endl << endl;
			return false;
		}
	}
	cout << "Zaporedje je urejeno" << endl << endl;
	return true;
}

int returnRandom() {
	return rand() % 100 + 1;
}

void generateNumbers(vector<int>& array, int size) {
	for (int i = 0; i < size - 1; i++) {
		array.push_back(returnRandom());
	}
}

void generateAscending(vector<int>& array, int size) {
	for (int i = 0; i < size - 1; i++)
		array.push_back(i + 1);
}

void generateDescending(vector<int>& array, int size) {
	for (int i = 0; i < size - 1; i++)
		array.push_back(size - i);
}

int main() {
	srand(time(NULL));
	bool running = true;
	int choice, size;
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	vector<int>randArray;
	string line;
	stringstream ss;
	randArray.reserve(10);
	while (running) {
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Vnesi velikost polja: "; cin >> size;
			randArray.clear();
			generateNumbers(randArray, size);
			break;
		case 2:
			cout << "Vnesi velikost polja: "; cin >> size;
			randArray.clear();
			generateAscending(randArray, size);
			break;
		case 3:
			cout << "Vnesi velikost polja: "; cin >> size;
			randArray.clear();
			generateDescending(randArray, size);
			break;
		case 4:
			izpisiPolje(randArray);
			cout << endl << endl;
			break;
		case 5:
			preveri(randArray, 0, randArray.size());
			break;
		case 6:
			start = chrono::steady_clock::now();
			hitro_uredi(randArray, 0, randArray.size() - 1);
			end = chrono::steady_clock::now();
			cout << "Cas izvajanja hitro_uredi brez mediane z " << randArray.size() + 1 << " elementi: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " us." << endl << endl;
			break;
		case 7:
			start = chrono::steady_clock::now();
			hitro_urediZMediano(randArray, 0, randArray.size() - 1);
			end = chrono::steady_clock::now();
			cout << "Cas izvajanja hitro_uredi z mediano z " << randArray.size() + 1 << " elementi: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " us." << endl << endl;
			break;
		case 8:
			start = chrono::steady_clock::now();
			urediZIzbiranjem(randArray, randArray.size());
			end = chrono::steady_clock::now();
			cout << "Cas izvajanja uredi z izbiranjem " << randArray.size() + 1 << " elementi: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " us." << endl << endl;
			break;
		case 9:
			running = false;
			break;
		default:
			cout << "napacna stevilka" << endl << endl;
			break;
		}
	}
	writeToFile(line);
	return 0;
}