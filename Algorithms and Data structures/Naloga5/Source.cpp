#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

struct Seznam {
	string ime;
	Seznam* next;
};

struct Tree {
	int key;
	Tree* father;
	Tree* leftSon, * rightSon;
	Seznam* Seznam;
};

void menu() {
	cout << "Filmi – izbira: " << endl;
	cout << "1) Vnos filma na datum izdaje" << endl;
	cout << "2) Urejen izpis vseh filmov" << endl;
	cout << "3) Izpis filmov na datum izdaje" << endl;
	cout << "4) Izpisi najstarejse in najnovejse filme" << endl;
	cout << "5) Poisci sosednja datuma" << endl;
	cout << "6) Brisi datum" << endl;
	cout << "7) Brisi film na izbran datum" << endl;
	cout << "8) Nalaganje filmov iz datoteke" << endl;
	cout << "9) Izbrisi drevo" << endl;
	cout << "10) Konec" << endl;
	cout << "Izbira : ";
}

Tree* find(Tree* root, int key) {
	Tree* current = root;
	while (current != NULL) {
		if (key == current->key)
			return current;
		if (key < current->key)
			current = current->leftSon;
		else
			current = current->rightSon;
	}
	return current;
}


void appendToSeznam(Seznam*& head, string ime)
{
	Seznam* new_node = new Seznam();
	Seznam* last = head;
	new_node->ime = ime;
	new_node->next = NULL;
	if (head->ime == "")
	{
		head = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}

void printSeznam(Seznam* head) {
	while (head != NULL) {
		cout << head->ime << ", ";
		head = head->next;
	}
}

Seznam* searchNode(Seznam* head, string ime) {
	Seznam* current = head;
	while (current != NULL) {
		if (current->ime == ime) return current;
		current = current->next;
	}
	return current = NULL;
}

void deleteNodeFromSeznam(Seznam*& head, string ime)
{
	if (head->ime == "")
		return;
	Seznam* temp = head;
	if (head->ime == ime) {
		head = temp->next;
		free(temp);
		return;
	}
	temp = searchNode(head, ime);
	if (temp == NULL || temp->next == NULL)
		return;
	else
		delete temp;
	Seznam* next = temp->next;
	free(temp->next);
	temp->next = next;
}

void insert(Tree*& root, int key, string ime) {
	Tree* current = root;
	Tree* fatherCurrent = NULL;
	while (current != NULL) {
		fatherCurrent = current;
		if (key < current->key)
			current = current->leftSon;
		else if (key > current->key)
			current = current->rightSon;
		else {
			appendToSeznam(current->Seznam, ime);
			return;
		}
	}

	Tree* tmp = new Tree();
	tmp->key = key;
	tmp->Seznam = new Seznam();
	appendToSeznam(tmp->Seznam, ime);
	tmp->father = fatherCurrent;

	if (fatherCurrent == NULL)
		root = tmp;
	else {
		if (tmp->key < fatherCurrent->key)
			fatherCurrent->leftSon = tmp;
		else
			fatherCurrent->rightSon = tmp;
	}
}

void urejen_izpis(Tree* root) {
	if (root == NULL)
		return;
	if (root != NULL) {
		urejen_izpis(root->leftSon);
		cout << root->key << ": ";
		printSeznam(root->Seznam);
		cout << endl;
		urejen_izpis(root->rightSon);
	}
}

Tree* minimum(Tree* root) {
	Tree* current = root;
	while (current->leftSon != NULL)
		current = current->leftSon;
	return current;
}

Tree* maksimum(Tree* root) {
	Tree* current = root;
	while (current->rightSon != NULL)
		current = current->rightSon;
	return current;
}

Tree* naslednik(Tree* current) {
	if (current->rightSon != NULL)
		return minimum(current->rightSon);

	Tree* currentFather = current->father;
	while (currentFather != NULL && current == currentFather->rightSon) {
		current = currentFather;
		currentFather = currentFather->father;
	}
	return currentFather;
}

Tree* predhodnik(Tree* current) {
	if (current->leftSon != NULL)
		return maksimum(current->leftSon);

	Tree* currentFather = current->father;
	while (currentFather != NULL && current == currentFather->leftSon) {
		current = currentFather;
		currentFather = currentFather->father;
	}
	return currentFather;
}

void deleteNode(Tree*& root, Tree* treeNode) {
	Tree* nodeToDelete;
	Tree* tmp;
	if (treeNode->leftSon == NULL || treeNode->rightSon == NULL)
		nodeToDelete = treeNode;
	else
		nodeToDelete = naslednik(treeNode);

	if (nodeToDelete->leftSon != NULL)
		tmp = nodeToDelete->leftSon;
	else
		tmp = nodeToDelete->rightSon;

	if (tmp != NULL)
		tmp->father = nodeToDelete->father;

	if (nodeToDelete->father == NULL)
		root = tmp;
	else {
		if (nodeToDelete == nodeToDelete->father->leftSon)
			nodeToDelete->father->leftSon = tmp;
		else
			nodeToDelete->father->rightSon = tmp;
	}

	if (nodeToDelete != treeNode)
		treeNode->key = nodeToDelete->key;

	delete nodeToDelete;
}

void _deleteTree(Tree*& root)
{
	if (root == NULL) return;
	_deleteTree(root->leftSon);
	_deleteTree(root->rightSon);

	cout << "\n Deleting node: " << root->key;
	delete root;
}

void deleteTree(Tree*& root)
{
	_deleteTree(root);
	root = NULL;
	cout << endl;
}

void readFromFile(Tree*& root, const string filmi) {
	ifstream in(filmi);
	int N, datum;
	string ime;
	in >> N;
	for (int i = 0; i < N; i++) {
		in >> datum;
		getline(in, ime, '\n');
		insert(root, datum, ime);
		if (i % 1000 == 0) {
			cout << "*" << flush;
		}

	}
	cout << endl;
}

int main() {
	bool running = true;
	int choice, key;
	ifstream in;
	string ime;
	Tree* root = new Tree();
	root = NULL;
	Seznam* list = new Seznam();
	list = NULL;
	Tree* treeNode;
	do {
		menu();
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Vnesi vrednost(key): "; cin >> key;
			cin.ignore();
			cout << "Vnesi ime filma: "; getline(cin, ime);
			insert(root, key, ime);
			break;
		case 2:
			urejen_izpis(root);
			break;
		case 3:
		{
			cout << "Vnesi datum, od katerega zelis filme: "; cin >> key;
			auto start = chrono::steady_clock::now();
			treeNode = find(root, key);
			auto end = chrono::steady_clock::now();
			if (treeNode == NULL)
				cout << "Datum ne obstaja!" << endl << endl;
			else {
				cout << treeNode->key << ": ";
				printSeznam(treeNode->Seznam);
				cout << endl;
			}
			cout << endl << "Cas trajanja iskanja je bil: " << chrono::duration_cast<chrono::microseconds> (end - start).count() << " us" << endl << endl;
		}
		break;
		case 4:
			if (root == NULL)
				cout << "Drevo je prazno..." << endl;
			else {
				treeNode = maksimum(root);
				cout << "Najnovejsi filmi: " << endl;
				cout << treeNode->key << " ";
				printSeznam(treeNode->Seznam);
				treeNode = minimum(root);
				cout << "\nNajstarejsi filmi: " << endl;
				cout << treeNode->key << " ";
				printSeznam(treeNode->Seznam);
				cout << endl << endl;
			}
			break;
		case 5:
			cout << "Vnesi vrednost, od katerega zelis predhodnik in naslednik: "; cin >> key;
			if (root == NULL)
				cout << "Drevo je prazno..." << endl;
			else if (find(root, key) == NULL)
				cout << "Datum ne obstaja..." << endl;
			else {
				treeNode = predhodnik(find(root, key));
				if (treeNode == NULL)
					cout << "Ni predodnika..." << endl;
				else
					cout << "Predhodnik(" << find(root, key)->key << "): " << treeNode->key << endl;
				treeNode = naslednik(find(root, key));
				if (treeNode == NULL)
					cout << "Ni naslednika..." << endl << endl;
				else
					cout << "Naslednik(" << find(root, key)->key << "): " << treeNode->key << endl << endl;
			}
			break;
		case 6:
			cout << "Vnesi vrednost za brisanje: "; cin >> key;
			treeNode = find(root, key);
			if (treeNode == NULL)
				cout << "Datuma ni v seznamu, zato ga ne mores izbrisat" << endl << endl;
			else {
				deleteNode(root, treeNode);
				cout << "IZBRISANO" << endl << endl;
			}
			break;
		case 7:
			cout << "Vnesi vrednost za brisanje: "; cin >> key;
			cin.ignore();
			cout << "Vnesi ime filma: "; getline(cin, ime);
			treeNode = find(root, key);
			if (treeNode == NULL)
				cout << "Datuma ni v seznamu, zato ga ne mores izbrisat" << endl << endl;
			else {
				deleteNodeFromSeznam(treeNode->Seznam, ime);
				cout << "IZBRISANO" << endl << endl;
			}
			break;
		case 8: {
			string array[] = { "IMDB_date_name_full.list", "IMDB_date_name_full_sorted.list", "IMDB_date_name_mini.list", "IMDB_date_name_mini_sorted.list" };
			for (int i = 0; i < 4; i++) {
				cout << i + 1 << ": " << array[i] << endl;
			}
			key = 0;
			cout << "Izbira: "; cin >> key;
			switch (key)
			{
			case 1:
				if (root != NULL)
					deleteTree(root);
				else
					readFromFile(root, array[0]);
				break;
			case 2:
				if (root != NULL)
					deleteTree(root);
				else
					readFromFile(root, array[1]);
				break;
			case 3:
				if (root != NULL)
					deleteTree(root);
				else
					readFromFile(root, array[2]);
				break;
			case 4:
				if (root != NULL)
					deleteTree(root);
				else
					readFromFile(root, array[3]);
				break;
			default:
				cout << "Napacna stevilka...(1 - 4): ";
				break;
			}
		}
			  break;
		case 9:
			if (root == NULL) {
				cout << "Drevo ne obstaja..." << endl << endl;
			}
			else
				deleteTree(root);
			break;
		case 10:
			running = false;
			break;
		}
	} while (running);

	return 0;
}