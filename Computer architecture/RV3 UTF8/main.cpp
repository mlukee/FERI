#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

void checkInput(string &input){
    for (int i = 0; i < input.length(); i++){
        if(input[i] >= 'a' && input[i] <= 'f') //ce je lowercase, spremeni v uppercase
            input[i] = toupper(input[i]);
        if (input[i] < '0' || input[i] > 'F'){
            cerr << "Napaka: neveljavna vrednost '" << input[i] << "'." << endl;
            cerr << "Vhod mora biti v obliki [0-9A-F]" << endl;
            exit(1);
        }
    }
}

void convertedHextoBin(const string &vhod, string &binarno) {
    for (int i = 0; i < vhod.size(); i++) {
        char stevka = vhod[i];
        if (stevka >= '0' && stevka <= '9') {
            stevka -= '0';
        } else if (stevka >= 'A' && stevka <= 'F') {
            stevka -= 'A' - 10;
        } else {
            cerr << "Napaka: neveljavna heksadecimalna številka." << endl;
            exit(1);
        }
        for (int j = 3; j >= 0; j--) {
            binarno += (stevka & (1 << j)) ? '1' : '0';
        }
    }
}

void convertBinaryToHex(const string &binarno, string &izhod){
    izhod = "";
    for(int i = 0;i < binarno.size();i+=4){
        string stevka = binarno.substr(i,4);
        if(stevka == "0000")
            izhod += '0';
        else if(stevka == "0001")
            izhod += '1';
        else if(stevka == "0010")
            izhod += '2';
        else if(stevka == "0011")
            izhod += '3';
        else if(stevka == "0100")
            izhod += '4';
        else if(stevka == "0101")
            izhod += '5';
        else if(stevka == "0110")
            izhod += '6';
        else if(stevka == "0111")
            izhod += '7';
        else if(stevka == "1000")
            izhod += '8';
        else if(stevka == "1001")
            izhod += '9';
        else if(stevka == "1010")
            izhod += 'A';
        else if(stevka == "1011")
            izhod += 'B';
        else if(stevka == "1100")
            izhod += 'C';
        else if(stevka == "1101")
            izhod += 'D';
        else if(stevka == "1110")
            izhod += 'E';
        else if(stevka == "1111")
            izhod += 'F';
    }
}

void kodiraj(const string &vhod, string &izhod){
    string binarno;
    convertedHextoBin(vhod, binarno);

    for(int i = 0;i < binarno.size();i++){
        if(binarno[0] == '0')
            binarno.erase(0,1);
    }

    //1-byte encoding - 0xxxxxxx
    //2-byte encoding - 110xxxxx 10xxxxxx
    //3-byte encoding - 1110xxxx 10xxxxxx 10xxxxxx
    //4-byte encoding - 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

    if(binarno.size() < 8) //1-byte coding
        for(int i = 0;binarno.size() < 8;i++)
            binarno = '0' + binarno;

    else if(binarno.size() <= 11) {//2-byte coding
        for (int i = 0; binarno.size() < 11; i++)
            binarno = '0' + binarno;
        binarno = "110" + binarno.substr(0,5) + "10" + binarno.substr(5,6);
    }
    else if(binarno.size() <= 16) {//3-byte coding
        for (int i = 0; binarno.size() < 16; i++)
            binarno = '0' + binarno;
        binarno = "1110" + binarno.substr(0,4) + "10" + binarno.substr(4,6) + "10" + binarno.substr(10,6);
    }
    else if(binarno.size() <= 21) {//4-byte coding
        for (int i = 0; binarno.size() < 21; i++)
            binarno = '0' + binarno;
        binarno = "11110" + binarno.substr(0,3) + "10" + binarno.substr(3,6) + "10" + binarno.substr(9,6) + "10" + binarno.substr(15,6);
    }
    else{
        cerr << "Napaka! Prevelika vrednost!" << endl;
        exit(1);
    }
    convertBinaryToHex(binarno, izhod);
}

void dekodiraj(const string &vhod, string &izhod) {
    string binarno;
    convertedHextoBin(vhod, binarno); //pretvorimo heksadecimalno v binarno

    if (binarno.substr(0, 3) == "110") { //2-byte coding
        if(binarno.size() < 16 && binarno.substr(8,2) != "10"){
            cerr << "Napaka! " << endl;
            exit(1);
        }
        binarno = binarno.substr(3, 5) + binarno.substr(10, 6);
    } else if (binarno.substr(0, 4) == "1110"){ //3-byte coding
        if(binarno.size() < 24 && binarno.substr(8,2) != "10" && binarno.substr(16,2) != "10"){
            cerr << "Napaka! " << endl;
            exit(1);
        }
        binarno = binarno.substr(4, 4) + binarno.substr(10, 6) + binarno.substr(18, 6);
    }else if (binarno.substr(0, 5) == "11110"){ //4-byte coding
        if(binarno.size() < 32 && binarno.substr(8,2) != "10" && binarno.substr(16,2) != "10" && binarno.substr(24,2) != "10"){
            cerr << "Napaka! " << endl;
            exit(1);
        }
        binarno = binarno.substr(5, 3) + binarno.substr(10, 6) + binarno.substr(18, 6) + binarno.substr(26, 6);
    }else if (binarno[0] == '0'){ //1-byte coding
        if (binarno.size() < 8) {
            cerr << "Napaka! Premala velikost!" << endl;
            exit(1);
        }
        binarno = binarno.substr(1, 7);
    }else{
        cerr << "Napaka! Neveljavna vrednost!" << endl;
    }

    if(binarno.size() % 4 != 0){
        do{
            binarno = '0' + binarno;
        }while(binarno.size() % 4 != 0);
    }
    convertBinaryToHex(binarno, izhod);
    if(izhod[0]== '0')
        for(int i = 0;i < izhod.size();i++){
            if(izhod[0] == '0')
                izhod.erase(0,1);
        }

}

int main(){
    string vhod;
    string izhod;
    cout<< "Vnesite znak za kodiranje (hexadecimalno): ";
    std::getline(cin, vhod);
    checkInput(vhod);
    kodiraj(vhod, izhod);
    cout << "V UTF-8 zakodiran znak: " << izhod << endl;
    cout << "Vnesite znak za dekodiranje (hexadecimalno): ";
    std::getline(cin, vhod);
    checkInput(vhod);
    dekodiraj(vhod, izhod);
    cout << "V UTF-8 dekodiran znak: U+" << izhod << endl;
    return 0;
}

