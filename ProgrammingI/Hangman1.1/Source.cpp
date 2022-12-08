#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <iomanip>

using namespace std;

struct Igralec {
	int stev; //Stevilka igralca
	int stPoskusov = 0;
	string ime;
	string geslo;
	string ugib;
	bool zgodovina[26]; //Zgodovina ugibanih crk
	//bool ugotovil = true; //Predpostavim da vsi ugotovijo geslo
	time_t cas; //Zacetek igre
	time_t elapsed; //Konec igre
	Igralec* next;
};

string gesla[100];  //pred definiram polje dolzine 100
void logika_igre(Igralec* ig, int dol_gesla);

int beri_gesla(int L) {
	string line; //spremenljivka za vrstico
	ifstream GeslaTXT("gesla.txt"); //odprem datoteko gesla.txt
	int n = 0;
	if (GeslaTXT.is_open()) {
		while (getline(GeslaTXT, line)) { //pridobim vrstico v datoteki
			if (line.length() == L) { //ce je vrstica dolga L znakov - L pridobim od uporabnika
				gesla[n] = line; //vstavim vrstico oz. geslo v polje gesel
				n++; //se pomaknem naprej
			}
		}
		GeslaTXT.close(); //zaperem datoteko gesla.txt
	}
	else {
		return -1; //ni gesla
	}
	return n; //stevilo gesel v polju
}

//Izpisem vse igralce iz enosmernega seznama
void izpisiIgralce(Igralec* head) {
	Igralec* ptr = head;
	ofstream izpisi("statistika.txt");
	string line;
	if (izpisi.is_open())
	{
		izpisi << setfill('-') << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << endl;
		izpisi << setfill(' ') << setw(1) << "|" << setw(5) << left << "St" << setw(1) << "|" << setw(15) << left << "Tekmovalec" << setw(1) << "|" << setw(15) << left << "Geslo" << setw(1) << "|" << setw(5) << left << "Cas" << setw(1) << "|" << setw(15) << left << "St. poskusov" << setw(1) << "|" << endl;
		while (ptr != NULL) {
			izpisi << setfill('-') << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << endl;
			izpisi << setfill(' ') << setw(1) << "|" << setw(5) << left << ptr->stev << setw(1) << "|" << setw(15) << left << ptr->ime << setw(1) << "|" << setw(15) << left << ptr->geslo << setw(1) << "|" << setw(5) << left << ptr->elapsed << setw(1) << "|" << setw(15) << right << ptr->stPoskusov << setw(1) << "|" << endl;
			ptr = ptr->next;
		}
		izpisi << setfill('-') << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << endl;
		izpisi.close();
	}
}

//Izpisuje scenarije
void izpisScenarija(int n) {
	ifstream scenariji("scenariji.txt");
	string line;
	if (scenariji.is_open()) {
		//Stran s katero sem si pomagal, da berem dolocene vrstice iz datoteke: https://www.codespeedy.com/cpp-program-to-create-a-text-file-open-and-read-a-particular-line/
		for (int lineNumber = 1; getline(scenariji, line) && lineNumber < 91; lineNumber++)
			if (lineNumber == (n * 9) + 1) {
				int st_vrstic = lineNumber + 8;
				for (int i = lineNumber; i < st_vrstic; i++)
				{
					getline(scenariji, line);
					cout << line << endl;
				}
			}

		scenariji.close();
	}
	else {
		cout << "Napaka v odpiranju datoteke scenariji!";
	}
}

//Vnesem podatke o igralcu
void VnosIgralec(int i, Igralec* ig) {
	string ime, geslo, znak = "";
	int st, st_gesel, random, dol_gesla = 0;
	//Pridobim ime za igralca		
	cout << "Vnesi ime: "; cin >> ime;
	//Preverjam dolzino gesla		
	do {
		try {
			//izbira dolzine gesla
			cout << "vnesi dolzino gesla(med 3 in 13 znakov): ";
			cin >> st;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Vse ki ni stevilka al pa special character ignorira
			if (!(st >= 3 && st <= 13)) {
				cout << "Napaka! Ni gesla ki ustreza vasi dolzini. Vnesite stevilko med 3 in 13." << endl;
			}
			else {
				throw(st);
			}
		}
		catch (...) {
			cout << "Napaka, nisi vneso stevilke!" << endl;
		}

	} while (st < 3 || st >13);

	st_gesel = beri_gesla(st); //stevilo gesel n-dolzine
	random = rand() % st_gesel;
	geslo = gesla[random];

	//Pridobim dolzino besede(gesla) v podcrtajih(_)
	dol_gesla = geslo.length();
	for (int j = 0; j < dol_gesla; j++) {
		znak += '_';
	}
	ig->stev = i;
	ig->ime = ime;
	ig->geslo = geslo;
	ig->ugib = znak;
	ig->next = NULL;

}

void logika_igre(Igralec* ig) {

	//zacnem steti sekunde igralcu
	ig->cas = time(NULL);
	char crka; //pridobim od uporabnika
	int napake = 0; //stevilo narobnih crk
	string uporabljeneCrke = "";

	do
	{
		int vsebujeCrko = 0;
		izpisScenarija(napake); //Izrisujem sliko vislic
		cout << endl << endl;
		cout << ig->ime << ", tvoja skrita beseda je: " << ig->ugib << endl; //Izpisem ime igralca in njegovo besedo v _
		cout << "Imas toliko napak:\t " << napake << endl;
		cout << "Ze uporabljene crke: " << uporabljeneCrke << endl;
		cout << "Vnesi crko: "; cin >> crka;	//Pridobim crko od uporabnika
		ig->stPoskusov = ig->stPoskusov + 1;

		if (!(tolower(crka) >= 'a' && tolower(crka) <= 'z')) {
			goto Preveri;
		}
		else if (uporabljeneCrke.find(tolower(crka)) == string::npos) { //string::npos vrne -1, se pravi ce ne najde crke, jo doda v string
			uporabljeneCrke.push_back(tolower(crka)); //Dodam na konec stringa crko
			uporabljeneCrke.push_back(' '); //Za crko dodam space

		}
		else { //Crka je ze bila vnesena, in da ne stejem kot za napako, ga sprasujem tako dolgo, dokler ne poda nove crke..Lahko bi dal tudi napake++ in mu stel kot napako

		Preveri:
			do {
				cout << "Vnesel si naroben znak...Probaj se enkrat: "; cin >> crka; //Pridobim novo crko
				ig->stPoskusov = ig->stPoskusov + 1;

			} while (uporabljeneCrke.find(tolower(crka)) != string::npos || !(tolower(crka) >= 'a' && tolower(crka) <= 'z'));
			uporabljeneCrke.push_back(tolower(crka)); //Nato novo crko dodam na konec stringa
			uporabljeneCrke.push_back(' '); //Za crko dodam presledek
		}

		//Pridobim index crke od 0-25 da jo lahko vstavim v polje.. minus 97 je zato ker je vrednost ASCII 'a'=97..Primerjam male crke toraj
		int index = tolower(int(crka)) - 97;

		//For zanka, katera gre od zacetka do konca gesla(skrite besede)
		int dol_gesla = ig->geslo.length();
		for (int i = 0; i < dol_gesla; i++) {
			//Ce je vnesena crka enaka crki iz skrite besede, namesto _ postavi vneseno crko
			if (tolower(crka) == tolower(ig->geslo[i])) {
				ig->ugib[i] = ig->geslo[i];
				vsebujeCrko++; //Preverjam ali vsebuje crko ali ne
			}
		}
		//Ce geslo ne vsebuje crke je narobna
		if (vsebujeCrko == 0) {
			ig->zgodovina[index] = true;
			napake++; //Mu pristejem napako
		}
		//system clear screen
		system("CLS");
	} while ((ig->ugib != ig->geslo) && napake != 9);
	//Ce ugotovi geslo ali ce je imel 10 napak, mu vstavim cas
	ig->elapsed = time(NULL) - ig->cas;
	if (napake == 9) {
		system("CLS");
		izpisScenarija(9); //Izrisujem sliko vislic
		cout << endl << endl;
		cout << ig->ime << ", tvoja skrita beseda je bila: " << ig->geslo << endl;
		cout << "Ugotovil si samo: " << ig->ugib << endl;
		cout << "Imel si toliko napak:\t " << napake + 1 << endl;
		cout << "\tVEC SRECE PRIHODNJIC!" << endl;
		system("pause");
		system("CLS");
	}
	else {
		system("CLS");
		izpisScenarija(napake); //Izrisujem sliko vislic
		cout << endl << endl;
		cout << ig->ime << ", CESTITAM, da si ugotovil besedo: " << ig->geslo << endl;
		cout << "Imel si toliko napak:\t " << napake << endl;
		cout << "\tNASVIDENJE!" << endl;
		system("pause");
		system("CLS");
	}
}

Igralec* add(Igralec* head, Igralec* ig) {
	Igralec* igralec = new Igralec;
	igralec = ig;
	Igralec* pred = NULL;
	Igralec* trenutni = head;
	while (trenutni != NULL && ig->stPoskusov > trenutni->stPoskusov)
	{
		pred = trenutni;
		trenutni = trenutni->next;
	}

	ig->next = trenutni;

	//Ce je list prazen
	if (pred == NULL) {
		head = igralec;
	}
	else {
		pred->next = igralec;
	}
	return head;
}

//Izbrises zadnjega - najslabsega igralca
Igralec* zbrisi_zadnjega(Igralec* head) {
	Igralec* predzadnji = head;

	while (predzadnji->next->next != NULL) { //gledam za 2 naprej
		predzadnji = predzadnji->next;
	}
	delete(predzadnji->next);
	predzadnji->next = NULL;
	return head;
}


int enter(Igralec** head, Igralec* ig, int n_ig) {
	if (*head == NULL) {
		Igralec* ptr = new Igralec;
		ptr = ig;
		ptr->next = NULL;
		*head = ptr;
	}
	else {
		*head = add(*head, ig);
	}
	if (n_ig > 4) {
		*head = zbrisi_zadnjega(*head);
	}
	else {
		n_ig++;
		return n_ig;
	}
}

int main() {
	srand(time(NULL));
	Igralec* head = NULL;
	string ime, geslo, znak = "";
	int st, st_gesel, random, dol_gesla, n_igralec = 0;

	for (int i = 1; i <= 10; i++) {

		Igralec* ig = new Igralec;
		VnosIgralec(i, ig); //dodam igralca v enosmerno povezan seznam
		logika_igre(ig);
		n_igralec = enter(&head, ig, n_igralec);
	}
	izpisiIgralce(head);
	return 0;
}