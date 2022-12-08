#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

struct Vozlisce {
	int ime,predhodnik, cena_poti;
};

struct Povezava {
	int u, v, cena;
};

void beri_iz_datoteke(int& st_vozlisc, vector<Povezava*>& povezave, vector<Vozlisce*>&vozlisca, string fileName) {
	vozlisca.clear();
	povezave.clear();
	ifstream f(fileName);
	f >> st_vozlisc;
	int cena = 0;
	for (int i = 0; i < st_vozlisc; i++) {
		for (int j = 0; j < st_vozlisc; j++) {
			f >> cena;
			if (cena == 0)
				continue;
			if (cena == 9999)
				continue;
			Povezava* p = new Povezava;
			p->u = i;
			p->v = j;
			p->cena = cena;
			povezave.push_back(p);
		}
	}	
}

vector<Vozlisce*> bellmanFord(int st_vozlisc, vector<Vozlisce*>& vozlisca, vector<Povezava*>& povezave, int s) {
	//Reset seznam vozlisc
	for (auto& vozlisce : vozlisca)
		delete vozlisce;
	vozlisca.clear();
	for (int i = 0; i < st_vozlisc; i++) {
		Vozlisce* v = new Vozlisce;
		v->cena_poti = INT32_MAX / 2;
		v->predhodnik = -1;
		v->ime = i;
		vozlisca.push_back(v);
	}
	
	for (int i = 0; i < vozlisca.size(); i++) {
		if (vozlisca[i]->ime == s-1){
				vozlisca[i]->cena_poti = 0;
				vozlisca[i]->predhodnik = -1;
			}
	}

	for (int i = 1; i < vozlisca.size(); i++) {
		for (auto& povezava : povezave) {
			if((vozlisca[povezava->u]->cena_poti + povezava->cena) < vozlisca[povezava->v]->cena_poti){
				if (i < vozlisca.size()-1) {
					vozlisca[povezava->v]->cena_poti = vozlisca[povezava->u]->cena_poti + povezava->cena;
					vozlisca[povezava->v]->predhodnik = vozlisca[povezava->u]->ime;
				}
				else {
					cout << "Napaka!" << endl;
					return vozlisca;
				}
			}
		}
	}
	return vozlisca;
}


void izpis_poti(int s, int v, vector<Vozlisce*>& vozlisca) {
	if (v == s) {
		cout << "Pot je: " << v+1 << " ";
	}
	else {
		if (vozlisca[v]->predhodnik == -1) {
			cout << "Med " << s+1 << " in " << v+1 << " ni poti!\n";
			return;
		}
		else {
			izpis_poti(s, vozlisca[v]->predhodnik, vozlisca);			
			cout << v+1 << " ";
			return;
		}
	}
}

void meni() {
	cout << "Bellman-Fordov algoritem - izbira:\n"
		"1) Preberi graf iz datoteke\n"
		"2) Generiraj nakljucni graf z n vozlisci in cenami od a do b\n"
		"3) Pozeni algoritem\n"
		"4) Izpisi seznam vozlisc\n"
		"5) Izpisi najkrajso pot\n"
		"6) Konec\n"
		"Izbira : ";
}

int main() {
	int choice = 0, st_vozlisc = 0, fileChoice = 0, zacVozlisce = 0, konVozlisce = 0, cena = 0, s = 0, d = 0;
	bool running = true;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	vector<Vozlisce*> vozlisca;
	vector<Povezava*> povezave;
	vector<Vozlisce*> resitev;
	while (running) {
		meni();
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Na izbiro je: \n" << "1: graf1.txt" << "\n2: graf2.txt\n3: grafBig.txt" << "\n";
			cin >> fileChoice;
			switch (fileChoice)
			{
			case 1:
				beri_iz_datoteke(st_vozlisc, povezave, vozlisca, "graf1.txt");
				break;
			case 2:
				beri_iz_datoteke(st_vozlisc, povezave, vozlisca, "graf2.txt");
				break;
			case 3:
				beri_iz_datoteke(st_vozlisc, povezave, vozlisca, "grafBig.txt");
				break;
			default:
				cout << "Napacna izbira...\n";
				break;
			}
			break;
		case 2:
			cout << "Vozlisca: " << endl;
			for (auto vozlisce : vozlisca) {
				cout << vozlisce->predhodnik << " - "  << vozlisce->ime+1 << " -> " << vozlisce->cena_poti << endl;
			}
			cout << endl << "Povezave: \n";
			for(auto povezava: povezave)
				cout << povezava->u+1 << " " << povezava->v+1 << " -> " << povezava->cena << endl;
			break;
		case 3:
			cout << endl << "St vozlisc: " << st_vozlisc << endl << endl;
			do {
				cout << "Vnesi zacetno vozlisce: "; cin >> zacVozlisce;
			} while (zacVozlisce > st_vozlisc || zacVozlisce < 1);
			start = std::chrono::steady_clock::now();
			bellmanFord(st_vozlisc, vozlisca, povezave, zacVozlisce);
			end = std::chrono::steady_clock::now();
			cout << "Cas trajanja algoritma: " << chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << endl << endl;
			break;
		case 4:
			for (auto& vozlisce : vozlisca)
				cout << vozlisce->predhodnik+1 << " - " << vozlisce->ime+1 << " -> " << vozlisce->cena_poti << endl;
			break;
		case 5:
			do {
				cout << "Vnesi koncno vozlisce: "; cin >> konVozlisce;
			} while (konVozlisce > st_vozlisc || konVozlisce < 1);
			cout << "Iz " << zacVozlisce << " v " << konVozlisce << ":\n";
			cena = 0;
			izpis_poti(zacVozlisce-1, konVozlisce-1, vozlisca);
			cout << "\nCena poti je: " << vozlisca[konVozlisce-1]->cena_poti << endl << endl;
			break;
		case 6:
			running = false;
			break;
		default:
			cout << "Narobna izbira\n";
			break;
		}
	}
	return 0;
}