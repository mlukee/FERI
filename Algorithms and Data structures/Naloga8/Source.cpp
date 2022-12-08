#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>

using namespace std;

struct Vozlisce {
	int predhodnik, dolzina, status, indeks;
	string ime;
};

void beri_iz_datoteke(int& st_vozlisc, int& st_povezav, int*& C, vector<Vozlisce*>& vozlisca, string fileName) {
	ifstream f(fileName);
	f >> st_vozlisc;
	f >> st_povezav;
	C = new int[st_vozlisc * st_vozlisc];
	//Inicializiram tabelo C na 0
	for (int i = 0; i < st_vozlisc; i++) {
		Vozlisce* v = new Vozlisce;
		v->ime = to_string(i + 1);
		v->indeks = i;
		vozlisca.push_back(v);
		for (int j = 0; j < st_vozlisc; j++) {
			C[st_vozlisc * i + j] = 0;
		}
	}
	int indeksV1, indeksV2, cena;
	for (int i = 0; i < st_povezav; i++) { //grem skozi vse povezave
		f >> indeksV1 >> indeksV2 >> cena;
		C[st_vozlisc * (indeksV1 - 1) + (indeksV2 - 1)] = cena;
		C[st_vozlisc * (indeksV2 - 1) + (indeksV1 - 1)] = cena;
	}
}

void iskanje_v_globino(vector<Vozlisce*>& vozlisca, Vozlisce* s, Vozlisce* d, stack<Vozlisce*>& stackVozlisc, int*& C, int st_vozlisc) {
	for (int i = 0; i < stackVozlisc.size(); i++) {
		stackVozlisc.pop();
	}
	for (int i = 0; i < vozlisca.size(); i++) {
		if (vozlisca[i]->ime == s->ime)	continue;

		vozlisca[i]->status = 0; //NEPREGLEDANO
		vozlisca[i]->dolzina = 1000000;
		vozlisca[i]->predhodnik = -1;
	}
	s->status = 1; //V OBDELAVI
	s->dolzina = 0;
	s->predhodnik = -1;
	stackVozlisc.push(s);
	while (!stackVozlisc.empty()) {
		Vozlisce* current;
		current = stackVozlisc.top(); stackVozlisc.pop(); //Vzamem iz sklada element
		if (current == d) return;
		for (int i = 0; i < st_vozlisc; i++) {
			if (C[st_vozlisc * ((stoi(current->ime) - 1)) + i] > 0) {
				Vozlisce* u = vozlisca[i];
				if (u->status == 0) {
					u->status = 1;
					u->dolzina = current->dolzina + 1;
					u->predhodnik = current->indeks;
					stackVozlisc.push(u);
				}
			}
		}
		current->status = 2;
	}
}

void iskanje_v_sirino(vector<Vozlisce*>& vozlisca, Vozlisce* s, Vozlisce* d, queue<Vozlisce*>& queueVozlisc, int*& C, int st_vozlisc) {
	for (int i = 0; i < queueVozlisc.size(); i++) {
		queueVozlisc.pop();
	}
	for (int i = 0; i < vozlisca.size(); i++) {
		if (vozlisca[i]->ime == s->ime)	continue;

		vozlisca[i]->status = 0; //NEPREGLEDANO
		vozlisca[i]->dolzina = 1000000;
		vozlisca[i]->predhodnik = -1;
	}
	s->status = 1; //V OBDELAVI
	s->dolzina = 0;
	s->predhodnik = -1;
	queueVozlisc.push(s);
	while (!queueVozlisc.empty()) {
		Vozlisce* current;
		current = queueVozlisc.front(); queueVozlisc.pop(); //Vzamem iz sklada element
		if (current == d) return;
		for (int i = 0; i < st_vozlisc; i++) {
			if (C[st_vozlisc * ((stoi(current->ime) - 1)) + i] > 0) {
				Vozlisce* u = vozlisca[i];
				if (u->status == 0) {
					u->status = 1;
					u->dolzina = current->dolzina + 1;
					u->predhodnik = current->indeks;
					queueVozlisc.push(u);
				}
			}
		}
		current->status = 2;
	}

}

void izpis_poti(Vozlisce*& s, Vozlisce* v, vector<Vozlisce*>& vozlisca, int& cena) {
	if (v == s) {
		cout << "Pot je: " << v->ime << " ";
		cena++;
	}
	else {
		if (v->predhodnik == -1) {
			cout << "Med " << s->ime << " in " << v->ime << " ni poti!\n";
		}
		else {
			izpis_poti(s, vozlisca[v->predhodnik], vozlisca, cena);
			cena++;
			cout << v->ime << " ";
		}
	}
}

void izpisiVozljisce(Vozlisce*& curr) {
	cout << "Prehodnik: " << curr->predhodnik << endl;
	cout << "Dolzina: " << curr->dolzina << endl;
	cout << "Status: " << curr->status << endl;
	cout << "Indeks: " << curr->indeks << endl;
	cout << "Ime: " << curr->ime << endl << endl;
}

void meni() {
	cout << "Iskanje v globino in sirino - izbira:\n"
		"1) Preberi graf iz datoteke\n"
		"2) Pozeni iskanje v globino iz vozlisca s do d\n"
		"3) Pozeni iskanje v sirino iz vozlisca s do d\n"
		"4) Konec\n"
		"Izbira : ";
}

int main() {
	int choice = 0, st_vozlisc = 0, st_povezav = 0, fileChoice = 0;
	bool running = true;
	int ime1, ime2, cena = 0;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	stack<Vozlisce*> stackVozlisc;
	queue<Vozlisce*> queueVozlisc;
	vector<Vozlisce*> vozlisca;
	//Vozlisce* s = new Vozlisce,* d = new Vozlisce;
	int* C = new int[st_vozlisc * st_vozlisc];
	while (running) {
		meni();
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Na izbiro je: \n" << "1: graf.txt" << "\n2: grafBig.txt" << "\n";
			cin >> fileChoice;
			switch (fileChoice)
			{
			case 1:
				beri_iz_datoteke(st_vozlisc, st_povezav, C, vozlisca, "graf.txt");
				break;
			case 2:
				beri_iz_datoteke(st_vozlisc, st_povezav, C, vozlisca, "grafBig.txt");
				break;
			default:
				cout << "Napacna izbira...\n";
				break;
			}
			break;
		case 2:
			cin.ignore();
			cout << "\nVnesite ime zacetnega vozlisca: "; cin >> ime1;
			cout << "\nVnesite ime koncnega vozlisca: "; cin >> ime2;
			/*s->ime = ime1;
			d->ime = ime2;*/
			start = std::chrono::steady_clock::now();
			iskanje_v_globino(vozlisca, vozlisca[ime1 - 1], vozlisca[ime2 - 1], stackVozlisc, C, st_vozlisc);
			end = std::chrono::steady_clock::now();
			cena = 0;
			izpis_poti(vozlisca[ime1 - 1], vozlisca[ime2 - 1], vozlisca, cena);
			cout << endl;
			//for (auto& vozlisce : vozlisca)
			//	izpisiVozljisce(vozlisce);
			cout << endl;
			cout << "Cena poti: " << cena - 1 << endl;
			cout << "Cas: " << chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << endl << endl;
			break;
		case 3:
			cin.ignore();
			cout << "\nVnesite ime zacetnega vozlisca: "; cin >> ime1;
			cout << "\nVnesite ime koncnega vozlisca: "; cin >> ime2;
			start = std::chrono::steady_clock::now();
			iskanje_v_sirino(vozlisca, vozlisca[ime1 - 1], vozlisca[ime2 - 1], queueVozlisc, C, st_vozlisc);
			end = std::chrono::steady_clock::now();
			cena = 0;
			izpis_poti(vozlisca[ime1 - 1], vozlisca[ime2 - 1], vozlisca, cena);
			cout << endl;
			//for (auto& vozlisce : vozlisca)
				//izpisiVozljisce(vozlisce);
			cout << endl;
			cout << "Cena poti: " << cena - 1 << endl;
			cout << "Cas: " << chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << endl << endl;
			break;
		case 4:
			running = false;
			break;
		default:
			cout << "Narobna izbira\n";
			break;
		}
	}
	for (auto& vozlisce : vozlisca) {
		delete vozlisce;
	}
	vozlisca.clear();
	return 0;
}
