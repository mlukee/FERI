#include <iostream>

using namespace std;

struct element {
	int key;
	element* prev, * next;
};

void menu() {
	cout << "Hitro uredi dvojno-povezan seznam - izbira:" << endl << endl;
	cout << "1) Generiraj nakljucno zaporedje" << endl;
	cout << "2) Izpis zaporedja" << endl;
	cout << "3) Preveri urejenost zaporedja" << endl;
	cout << "4) Izpisi vsoto vseh elementov" << endl;
	cout << "5) Uredi" << endl;
	cout << "6) Konec" << endl;
	cout << "Vasa izbira: ";
}

element* deli(element*& dno, element*& vrh) {
	int pe = dno->key;
	element* l = dno;
	element* d = vrh;
	bool stop = false;
	while (!stop) {
		while (l->key <= pe && l != vrh) {
			l = l->next;
			if (l == d)
				stop = true;
		}
		while (d->key >= pe && d != dno) {
			d = d->prev;
			if (l == d)
				stop = true;
		}
		if (!stop)
			swap(l->key, d->key);
	}
	swap(dno->key, d->key);
	return d;
}

void hitro_uredi(element*& dno, element*& vrh) {
	if (dno == NULL && vrh == NULL)
		return;
	if (dno != vrh) {
		element* j = deli(dno, vrh);
		if (dno != j)
			hitro_uredi(dno, j->prev);
		if (vrh != j)
			hitro_uredi(j->next, vrh);
	}
}

void printForward(element* head) {
	element* current = head;
	while (current != NULL) {
		cout << current->key << " ";
		current = current->next;
	}
	cout << endl;
}

void clearList(element*& head, element*& tail) {
	if (head == NULL || tail == NULL)
		return;
	element* current = head;
	element* next = NULL;
	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
	head = NULL;
	tail = NULL;
}

void insertAtTheEnd(element*& head, element*& tail, int key) {
	element* newElement = new element();
	newElement->key = key;
	if (tail == NULL) {
		newElement->prev = NULL;
		newElement->next = NULL;
		head = newElement;
		tail = newElement;
	}
	else {
		tail->next = newElement;
		newElement->prev = tail;
		newElement->next = NULL;
		tail = newElement;
	}
}

bool checkIfSorted(element*& head) {
	if (head == NULL)
		return false;
	element* current = head;
	while (current->next != NULL) {
		if (current->key > current->next->key) {
			return false;
		}
		current = current->next;
	}
	return true;
}

int sumOfList(element*& head) {
	int sum = 0;
	element* current = head;
	while (current != NULL) {
		sum += current->key;
		current = current->next;
	}
	return sum;
}

int returnRandom() {
	return rand() % 1000 + 1;
}

int main() {
	srand(time(NULL));
	bool running = true;
	int choice, size, sum;
	element* head = NULL;
	element* tail = NULL;
	while (running) {
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Vnesi velikost polja: "; cin >> size;
			clearList(head, tail);
			for (int i = 0; i < size; i++) {
				insertAtTheEnd(head, tail, returnRandom());
			}
			break;
		case 2:
			printForward(head);
			break;
		case 3:
			if (checkIfSorted(head))
				cout << "Seznam je urejen" << endl << endl;
			else
				cout << "Seznam ni urejen" << endl << endl;
			break;
		case 4:
			sum = sumOfList(head);
			cout << "Vsota vseh elementov v seznamu je: " << sum << endl << endl;
			break;
		case 5:
			hitro_uredi(head, tail);
			break;
		case 6:
			running = false;
			break;
		default:
			cout << "napacna stevilka" << endl << endl;
			break;
		}
	}
	return 0;
}