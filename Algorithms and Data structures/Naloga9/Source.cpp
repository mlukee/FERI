#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>

using namespace std;

struct povezava {
	int p, q, cena;
};

void beri_iz_datoteke(int& st_vozlisc, int& st_povezav, vector<povezava*>& povezave, vector<int> &mnozice, string fileName) {
	if (!povezave.empty())
		povezave.clear();
	ifstream f(fileName);
	f >> st_vozlisc;
	f >> st_povezav;
	for (int i = 0; i < st_vozlisc; i++) {
		mnozice.push_back(0);					//inicializiram tabelo mnozic na 0
	}
	int indeksV1, indeksV2, cena;
	for (int i = 0; i < st_povezav; i++) { //grem skozi vse povezave in jih shranjujem v vektor
		f >> indeksV1 >> indeksV2 >> cena;
		povezava* tmp = new povezava;
		tmp->p = indeksV1;
		tmp->q = indeksV2;
		tmp->cena = cena;
		povezave.push_back(tmp);
	}
}

int deli(vector<povezava*>& povezave, int dno, int vrh) {
	int pe = povezave[dno]->cena;
	int l = dno;
	int d = vrh;
	while (l < d) {
		while (povezave[l]->cena <= pe && l < vrh) l++;
		while (povezave[d]->cena >= pe && d > dno) d--;
		if (l < d)
			swap(povezave[l], povezave[d]);
	}
	swap(povezave[dno], povezave[d]);
	return d;
}

void hitro_uredi(vector<povezava*>& povezave, int dno, int vrh) {
	if (dno < vrh) {
		int j = deli(povezave, dno, vrh);
		hitro_uredi(povezave, dno, j - 1);
		hitro_uredi(povezave, j + 1, vrh);
	}
}

vector<povezava*> kruskal(vector<povezava*> &povezave, vector<int> &mnozice, int st_vozlisc) {
	if (!mnozice.empty())
		fill(mnozice.begin(), mnozice.end(), 0);
	hitro_uredi(povezave, 0, povezave.size() - 1);
	vector<povezava*> resitev;
	int mnozica1 = 0, mnozica2 = 0, max =0;

	for (auto& povezava : povezave) {
		mnozica1 = mnozice[povezava->p - 1];
		mnozica2 = mnozice[povezava->q - 1];

		if (mnozica1 != 0 && mnozica2 != 0 && mnozica1 == mnozica2)						//obe mnozici pripadata isti mnozici
			continue;
		else if ((mnozica1 != 0 && mnozica2 != 0) && mnozica1 != mnozica2) {			//vozlisci sta v razlicnih mnozicah
			resitev.push_back(povezava);
			for (int i = 0; i < mnozice.size(); i++) {
				if (mnozice[i] == mnozica2)
					mnozice[i] = mnozica1;
			}
		}
		else if ((mnozica1 != 0 && mnozica2 == 0) || (mnozica1 == 0 && mnozica2 != 0)) { //ena od dveh je v mnozici
			resitev.push_back(povezava);
			if (mnozica1 == 0)															 //ce prva ni v mnozici
				mnozice[povezava->p - 1] = mnozica2;
			else									  									 //ce druga ni v mnozici
				mnozice[povezava->q - 1] = mnozica1;
		}
		else if (mnozica1 == 0 && mnozica2 == 0) {										 //nobeden ni v mnozici
			resitev.push_back(povezava);
			max = *max_element(mnozice.begin(), mnozice.end());
			mnozice[povezava->p - 1] = max + 1;
			mnozice[povezava->q - 1] = max + 1;
		}

		if (resitev.size() == st_vozlisc - 1) {
			return resitev;																//vrnem vektor povezav-resitev
		}
	}
	cout << "Ni resitev\n\n";
	return vector<povezava*>();															//vrnem prazen vektor
}

void printPovezava(povezava* povezav) {
	cout << "p: " << povezav->p << "\n";
	cout << "q: " << povezav->q << "\n";
	cout << "cena: " << povezav->cena << "\n\n";
}

void printPovezave(vector<povezava*> povezave) {
	for (int i = 0; i < povezave.size(); i++)
		printPovezava(povezave[i]);
}

void meni() {
	cout << "Kruskalov algoritem - izbira:\n"
		"1) Preberi graf iz datoteke\n"
		"2) Generiraj nakljucni graf\n"
		"3) Pozeni\n"
		"4) Izpis sprejetih povezav\n"
		"5) Konec\n\n"
		"Izbira : ";
}

int main() {
	int choice = 0, st_vozlisc = 0, st_povezav = 0, fileChoice = 0;
	bool running = true;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;

	vector<povezava*> povezave;
	vector<int> mnozice;
	vector<povezava*> resitev;
	int* C = new int[st_vozlisc * st_vozlisc];
	while (running) {
		meni();
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Na izbiro je:\n1. graf.txt\n2:grafRot.txt\n";
			cin >> fileChoice;
			switch (fileChoice) {
			case 1:
				beri_iz_datoteke(st_vozlisc, st_povezav, povezave, mnozice, "graf.txt");
				break;
			case 2:
				beri_iz_datoteke(st_vozlisc, st_povezav, povezave, mnozice, "grafRot.txt");
				break;
			default:
				cout << "Napacna izbira\n\n";
				break;
			}
			break;
		case 2:
			break;
		case 3:
			start = std::chrono::steady_clock::now();
			resitev = kruskal(povezave, mnozice, st_vozlisc);
			end = std::chrono::steady_clock::now();
			//for (int i = 0; i < resitev.size(); i++) {
			//	printPovezava(resitev[i]);
			//}
			cout << "St vhodnih vozlisc: " << st_vozlisc << endl;
			cout << "St vhodnih povezav: " << st_povezav << endl;
			cout << "St sprejetih povezav: " << resitev.size() << endl;
			cout << "Cas: " << chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n\n";
			break;
		case 4:
			printPovezave(resitev);
			break;
		case 5:
			running = false;
			break;
		default:
			break;
		}
	}
	return 0;
}