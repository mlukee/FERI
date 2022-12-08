#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;

struct Tree {
	int key;
	Tree* father;
	Tree* leftSon;
	Tree* rightSon;
};

void menu() {
	cout << "--------------------------------------" << endl;
	cout << "\tBinarno iskalno drevo" << endl;
	cout << "--------------------------------------" << endl;
	cout << "1) Vnos podatka" << endl;
	cout << "2) Urejen izpis vrednosti" << endl;
	cout << "3) Izpis povezav" << endl;
	cout << "4) Iskanje" << endl;
	cout << "5) Izpisi minimum in maksimum" << endl;
	cout << "6) Izpisi predhodnika in naslednika" << endl;
	cout << "7) Brisi vrednost" << endl;
	cout << "8) Testiraj pravilnost delovanja" << endl;
	cout << "9) Konec" << endl << endl;
	cout << "Izbira: ";
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

void insert(Tree*& root, int key) {
	Tree* current = root;
	Tree* fatherCurrent = NULL;
	while (current != NULL) {
		fatherCurrent = current;
		if (key < current->key)
			current = current->leftSon;
		else if (key > current->key)
			current = current->rightSon;
		else {
			cout << "Napaka!" << endl;
			exit;
		}
	}

	Tree* tmp = new Tree();
	tmp->key = key;
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
	if (root != NULL) {
		urejen_izpis(root->leftSon);
		cout << root->key << " ";
		urejen_izpis(root->rightSon);
	}
}

void izpis_povezav(Tree* root) {
	if (root->leftSon != NULL) {
		cout << root->key << " -> " << root->leftSon->key << endl;
		izpis_povezav(root->leftSon);
	}
	if (root->rightSon != NULL) {
		cout << root->key << " -> " << root->rightSon->key << endl;
		izpis_povezav(root->rightSon);
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

int generateNumber() {
	return rand() % 15 + 1;
}

int main() {
	srand(time(NULL));

	int choice, input, rand, min, max;
	bool running = true;

	Tree* root = new Tree();
	root = nullptr;

	Tree* treeNode;
	while (running) {
		menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Vnesi vrednost, ki jo zelis vnest: "; cin >> input;
			treeNode = find(root, input);
			if (treeNode == NULL)
				insert(root, input);
			else
				cout << "Vrednost ze obstaja! Podvojenih vrednosti ne mores imet!" << endl << endl;
			break;
		case 2:
			if (root == NULL)
				cout << "Drevo je prazno..." << endl;
			else
				urejen_izpis(root);
			cout << endl << endl;
			break;
		case 3:
			if (root == NULL)
				cout << "Drevo je prazno..." << endl;
			else
				izpis_povezav(root);
			cout << endl << endl;
			break;
		case 4:
			cout << "Vnesi vrednost, ki jo zelis poiskat: "; cin >> input;
			treeNode = find(root, input);
			if (treeNode == NULL)
				cout << "Vrednost se ne obstaja" << endl << endl;
			else
				cout << "Vrednost ze obstaja" << endl << endl;
			break;
		case 5:
			if (root == NULL)
				cout << "Drevo je prazno..." << endl;
			else {
				treeNode = maksimum(root);
				cout << "Maksimalna vrednost: " << treeNode->key << endl;
				treeNode = minimum(root);
				cout << "Minimalna vrednost: " << treeNode->key << endl << endl;
			}
			break;
		case 6:
			cout << "Vnesi vrednost, od katerega zelis predhodnik in naslednik: "; cin >> input;
			if (root == NULL)
				cout << "Drevo je prazno..." << endl;
			else if (find(root, input) == NULL)
				cout << "Element ne obstaja..." << endl;
			else {
				treeNode = predhodnik(find(root, input));
				if (treeNode == NULL)
					cout << "Ni predodnika..." << endl;
				else
					cout << "Predhodnik(" << find(root, input)->key << "): " << treeNode->key << endl;
				treeNode = naslednik(find(root, input));
				if (treeNode == NULL)
					cout << "Ni naslednika..." << endl << endl;
				else
					cout << "Naslednik(" << find(root, input)->key << "): " << treeNode->key << endl << endl;
			}
			break;
		case 7:
			cout << "Vnesi vrednost za brisanje: "; cin >> input;
			treeNode = find(root, input);
			if (treeNode == NULL)
				cout << "Elementa ni v seznamu, zato ga ne mores izbrisat" << endl << endl;
			else {
				deleteNode(root, treeNode);
				cout << "IZBRISANO" << endl << endl;
			}
			break;
		case 8:
			cout << "---------------------------------" << endl;
			cout << "\tTESTIRANJE DELOVANJA" << endl;
			cout << "---------------------------------" << endl;
			cout << "Brisanje podatka 4..." << endl;										//Brisanje podatka v praznem drevesu
			treeNode = find(root, 4);
			if (treeNode == NULL)
				cout << "Elementa ni v seznamu..." << endl << endl;
			else {
				deleteNode(root, treeNode);
				cout << "IZBRISANO" << endl << endl;
			}
			cout << "Vstavljanje podatkov...." << endl;										//Vstavljanje podatkov	
			for (int i = 0; i < 10; i++) {
				rand = generateNumber();
				cout << "Vstavljanje " << rand << "..." << endl;
				treeNode = find(root, rand);
				if (treeNode != NULL)
					cout << "Vrednost ze obstaja! Podvojenih vrednosti ne mores imet!" << endl;
				else
					insert(root, rand);
			}
			cout << endl << "Maksimum in minimum..." << endl;								//Maksimum in minimum drevesa
			treeNode = minimum(root);
			min = treeNode->key;
			cout << "Minimalna vrednost: " << min << endl;
			treeNode = maksimum(root);
			max = treeNode->key;
			cout << "Maksimalna vrednost: " << max << endl << endl;
			cout << "Iskanje naslednika in predhodnika(" << max << "): " << endl;			//Iskanje predhodnika in naslednika od max
			treeNode = predhodnik(find(root, max));
			cout << "Predhodnik(" << max << "): " << treeNode->key << endl;
			treeNode = naslednik(find(root, max));
			if (treeNode == NULL)
				cout << "Ni naslednika..." << endl << endl;
			cout << "Iskanje naslednika in predhodnika(" << min << "): " << endl;		//Iskanje predhodnika in naslednika od min
			treeNode = predhodnik(find(root, min));
			if (treeNode == NULL)
				cout << "Ni predhodnika..." << endl;
			treeNode = naslednik(find(root, min));
			cout << "Naslednik (" << min << "): " << treeNode->key << endl << endl;
			cout << "Izpis urejenih vrednosti..." << endl;									//Izpis urejenih vrednosti
			urejen_izpis(root);
			cout << endl << endl;
			cout << "Izpis povezav..." << endl;												//Izpis povezav
			izpis_povezav(root);
			cout << endl << endl;
			cout << "Brisanje korena (" << root->key << ")..." << endl;						//Brisanje korena
			treeNode = find(root, root->key);
			deleteNode(root, treeNode);
			cout << "IZBRISANO..." << endl << endl;
			cout << "Izpis povezav..." << endl;												//Izpis povezav
			izpis_povezav(root);
			cout << endl;
			urejen_izpis(root);
			cout << endl;
			cout << "---------------------------------" << endl;
			cout << "\tTESTIRANJE KONCANO" << endl;
			cout << "---------------------------------" << endl;
			break;
		case 9:
			running = false;
		default:
			break;
		}
	}
}