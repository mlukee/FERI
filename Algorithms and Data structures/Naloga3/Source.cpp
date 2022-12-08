#include <iostream>
#include <list>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Element {
	int key;
	Element* prev, * next;
};

void menu() {
	cout << "----------------------------------------" << endl;
	cout << "Dvojno povezan seznam - izbira: " << endl << endl;
	cout << "1) Iskanje podatka" << endl;
	cout << "2) Vnos podatka v glavo" << endl;
	cout << "3) Vnos podatka za elementom" << endl;
	cout << "4) Vnos podatka za repom" << endl;
	cout << "5) Brisanje podatka" << endl;
	cout << "6) Izpis seznama od glave proti repu" << endl;
	cout << "7) Izpis seznama od repa proti glavi" << endl;
	cout << "8) Testiraj hitrost" << endl;
	cout << "9) Konec" << endl << endl;
	cout << "----------------------------------------" << endl;
	cout << "Izbira: ";
}

void printForward(Element* head) {
	Element* current = head;
	while (current != NULL) {
		cout << current->key << " ";
		current = current->next;
	}
	cout << endl;
}

void printBackward(Element* tail) {
	Element* current = tail;
	while (current != NULL) {
		cout << current->key << " ";
		current = current->prev;
	}
	cout << endl;
}

Element* find(Element* head, int key) {
	Element* current = new Element();
	current = head;
	while (current != NULL && current->key != key) {
		current = current->next;
	}
	return current;
}

void insertAfter(Element* A, int key, Element** tail) {
	Element* B = new Element;
	B->key = key;
	B->prev = A;
	B->next = A->next;
	A->next = B;
	if (B->next != NULL)
		B->next->prev = B;
	else
		*tail = B;
}

void insertInHead(Element** head, int key, Element** tail) {
	Element* new_el = new Element();
	new_el->key = key;
	new_el->next = *head;
	new_el->prev = NULL;
	if (*head != NULL)
		(*head)->prev = new_el;
	else
		*tail = new_el;
	*head = new_el;
}

void insertAtTheEnd(Element** head, Element** tail, int key) {
	Element* element = new Element();
	element->key = key;
	if ((*tail) == NULL) {
		element->prev = NULL;
		element->next = NULL;
		*head = element;
		*tail = element;
	}
	else {
		(*tail)->next = element;
		element->prev = *tail;
		element->next = NULL;
		*tail = element;
	}
}

void deleteElement(Element** head, int key, Element** tail) {
	Element* elem = new Element;
	elem = find(*head, key);
	if (elem == NULL) {
		cout << "Elementa (" << key << ") ni v seznamu, zato ga ne mores izbrisati!" << endl;
		exit;
	}
	else {
		if (elem->prev == NULL && elem->next == NULL) {
			*head = NULL;
			*tail = NULL;
		}
		else {
			if (elem->prev != NULL)
				elem->prev->next = elem->next;
			else {
				*head = elem->next;
				(*head)->prev = NULL;
			}
			if (elem->next != NULL) {
				elem->next->prev = elem->prev;
			}
			else {
				*tail = elem->prev;
				(*tail)->next = NULL;
			}
		}
	}
	delete elem;
}

void moveRight(int* array, int N) {
	for (int i = N; i > 0; i--) {
		array[i] = array[i - 1];
	}
}

void insertAtTheFrontArray(int* array, int N) {
	for (int i = 0; i < N; i++) {
		moveRight(array, N);
		array[0] = i + 1;
	}
}

void fillArray(int* array, int N) {
	for (int i = 0; i < N; i++)
		array[i] = i + 1;
}

long long sumOfElements(list<int> a) {
	long long sum = 0;
	for (int it : a)
		sum += it;
	return sum;
}

long long sumOfArray(int* array, int N) {
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		sum += array[i];
	}
	return sum;
}

void writeToFile(string line) {
	ofstream myFile("out.txt");
	if (myFile.is_open()) {
		myFile << line;
		myFile.close();
	}

}

void calculateTime(int* polje, int N, list<int> a) {
	string line = "------------------------------------\nRacunanje casa za: " + to_string(N) + " elementov\n------------------------------------\n";
	stringstream ss;
	long long sum = 0;
	auto start = chrono::steady_clock::now();
	for (int i = 1; i <= N; i++) a.push_front(i); //vstavljanje v glavo seznama
	auto end = chrono::steady_clock::now();
	ss << "Cas trajanja vstavljanja na prvo mesto v seznamu: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << " ms." << endl;

	start = chrono::steady_clock::now();
	sum = sumOfElements(a); //racunanje vsote seznama
	end = chrono::steady_clock::now();
	ss << "Cas trajanja racunanje vsote seznama: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << " ms." << endl;

	start = chrono::steady_clock::now();
	insertAtTheFrontArray(polje, 100000); //vstavljanje na prvo mesto v polju
	end = chrono::steady_clock::now();
	ss << "Cas trajanja vstavljanja na prvo mesto v polju: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << " ms." << endl;

	sum = 0;
	start = chrono::steady_clock::now();
	sum = sumOfArray(polje, N); //vsota elementov polja
	end = chrono::steady_clock::now();
	ss << "Cas trajanja racunanje vsote polja: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << " ms." << endl;

	start = chrono::steady_clock::now();
	fillArray(polje, N); //vstavljanje na konec polja
	end = chrono::steady_clock::now();
	ss << "Cas trajanja vstavljanja na zadno mesto v polju: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << " ms." << endl;
	line.append(ss.str());

	cout << line << endl;
	writeToFile(line);
}

int main(int argc, char* argv[]) {

	Element* head = NULL;
	Element* tail = NULL;
	Element* elem = new Element;

	int choice, input, input2, N = 0;
	bool running = true;

	while (running) {
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Vnesi vrednost, ki jo zelis poiskati: "; cin >> input;
			if (find(head, input) == NULL)
				cout << "Vrednost (" << input << ") se ne obstaja" << endl;
			else
				cout << "Vrednost (" << input << ") ze obstaja" << endl;
			break;
		case 2:
			cout << "Vnesi vrednost: "; cin >> input;
			insertInHead(&head, input, &tail);
			break;
		case 3:
			cout << "Vnesi vrednost, ki jo zelis vstavit: "; cin >> input;
			cout << "Vnesi vrednost, za katero zelis vstaviti element: "; cin >> input2;
			elem = find(head, input2);
			if (elem == NULL) {
				cout << "Podatek (" << input2 << ") ne obstaja v seznamu!" << endl;
			}
			else
				insertAfter(elem, input, &tail);
			break;
		case 4:
			cout << "Vnesi vrednost, ki jo zelis vstaviti na konec: "; cin >> input;
			insertAtTheEnd(&head, &tail, input);
			break;
		case 5:
			cout << "Vnesi vrednost, ki jo zelis izbrisati: "; cin >> input;
			deleteElement(&head, input, &tail);
			break;
		case 6:
			printForward(head);
			break;
		case 7:
			printBackward(tail);
			break;
		case 8: {
			int* polje;
			list<int>a;

			cout << "Vnesi velikost seznama in polja: "; cin >> N;
			polje = new int[N];
			calculateTime(polje, N, a);
		}
			  break;
		case 9:
			running = false;
			cout << "GoodBye!" << endl;
			break;
		default:
			cout << "Napacna izbira!" << endl;
			break;
		}
	}
	return 0;
}