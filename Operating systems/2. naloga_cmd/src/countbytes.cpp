#include <iostream>
#include <stdlib.h>  //getenv
#include <map>
#include <string>
#include <getopt.h>
#include <fstream>
#include <functional>
#include <cstring>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::map;

bool jeStevilka(char ch){
	return isdigit(ch);
}

bool jeCrka(char ch){
	return isalpha(ch);
}

bool vsiZnaki(char ch){
	return true;
}

void decToHexa(char crka){
	int n = crka;
	char hexaNumber[100];
	string converted="0x";
	int i = 0;
	while(n!=0){
		int tmp = 0;
		tmp = n % 16;
		if(tmp < 10){
			hexaNumber[i] = tmp + 48;
			i++;
		}
		else{
			hexaNumber[i] = tmp + 87; //male crke
			//hexaNumber[i] = tmp + 55; //velike crke
			i++;
		}
		n /= 16;
	}
	
	for(int j = i-1;j>=0; j--)
		converted += hexaNumber[j];
		
	char arr[converted.length()+1];
	strcpy(arr, converted.c_str());
		
	for(long unsigned int i = 0; i < converted.length();i++)
		std::cout << arr[i];
}

void izpis(map<char, int> map, std::map<char, int>::iterator itr){
	//izpis statistike
	for(itr=map.begin();itr!=map.end();itr++)
		cout << itr->first << ": " << itr->second << endl;
}

void izpisHex(map<char, int> map, std::map<char,int>::iterator itr){
	for(itr=map.begin();itr!=map.end();itr++){
		decToHexa(itr->first);
		cout << ": ";
		cout << itr->second << endl;
	}
}
	
void countbytes(map<char, int> &m, const string bes, std::function<bool(char)> func){	
	for(long unsigned int i = 0; i < bes.length();i++){
		if(func(bes[i]))
			m[bes[i]]++;
		}
}

void countbytesSelect(map<char, int> &m, string bes, string crke){
	size_t found;
	for(long unsigned int i = 0; i< crke.length();i++)
		m[crke[i]]= 0;
		
	for(long unsigned int i = 0; i < bes.length();i++){
		found = crke.find(bes[i]);
		if(found != string::npos)
			m[bes[i]]++;
		}			
}


void print_help(const char*argv0){
	cout << "Uporaba: "
	<< argv0
	<< " [-h --help]"
	<< " [-l --letters]"
	<< " [-n --numbers]"
 	<< " [-x --hex]"
	<< " [-s <> --select=<>]"
	<< endl;
}

int main(int argc, char** argv){
	int opt;
	string s1;
	string selectArg;
	
	map<char, int> map; //uporaba mape za izpis statistike	
	std::map<char, int>::iterator itr; //iterator, da lahko grem skozi celo mapo
	
	
	bool flagL = false;
	bool flagN = false;
	bool flagX = false;
	bool flagS = false;
	
	 //pridobim environment variable
	if(char * envVar = getenv("SELECT")){
		selectArg = envVar;
		flagS = true;
	}
	
	
	static struct option longopt[]{
		{"help", no_argument, NULL, 'h'},
		{"letters", no_argument, NULL, 'l'},
		{"numbers", no_argument, NULL, 'n'},
		{"hex", no_argument, NULL, 'x'},
		{"select", required_argument, NULL, 's'},
	};

	while(( opt = getopt_long(argc, argv, "hs:lnx", longopt, NULL)) != 1){
	
		if(opt == -1)
			break;
			
		switch(opt){
			case 'h':
				print_help(argv[0]);
				return 0;
				break;
			case 's':
				flagS = true;
				selectArg = optarg;
				break;
			case 'l':
				flagL = true;
				break;
			case 'n':
				flagN = true;	
				break;
			case 'x':
				flagX = true;
				break;
			default: //?
				print_help(argv[0]);
		}
	}

	//pridobim input
	std::getline(std::cin, s1);
	
	if(flagS){
		countbytesSelect(map, s1, selectArg);
		if(flagX){
			izpisHex(map, itr);
			return 0;
		}
	}else if(flagL || flagN){
		if(flagL){
			countbytes(map, s1, &jeCrka);
			if(flagX){
				izpisHex(map, itr);
				return 0;
			}
		}
		if(flagN){
			countbytes(map, s1, &jeStevilka);
			if(flagX){
				izpisHex(map,itr);
				return 0;
			}
		}		
	}else{
		countbytes(map, s1, &vsiZnaki);
		if(flagX){
			izpisHex(map ,itr);
			return 0;
		}
		}
	
	
	if(optind < argc){
		cerr << "ERROR: wrong arguments" << endl;
		print_help(argv[0]);
	}
	
	izpis(map, itr);
	
	return 0;
}
