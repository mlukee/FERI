#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fcntl.h>  //open
#include <unistd.h> //close
#include <getopt.h>
#include <errno.h> //errno
#include <fstream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

void print_help()
{
    cout << "Uporaba: "
         << " [-h] "
         << " [-i zbirka] "
         << " [-I oprimek] "
         << " [-o zbirka] "
         << " [-O oprimek] "
         << endl;
}

string char_to_hex(char c)
{
    string hex = "0x";
    hex += "0123456789ABCDEF"[c >> 4];
    hex += "0123456789ABCDEF"[c & 0xF];

    return hex;
}

int main(int argc, char *argv[])
{
    int opt;
    int fd;
    int fd_in = 0;
    int fd_out = 1;
    int r;

    bool flag_i = false; // true ce -i zastavica uporabljena
    bool flag_I = false; // true ce -I zastavica uporabljena
    bool flag_o = false; // true ce -o zastavica uporabljena
    bool flag_O = false; // true ce -O zastavica uporabljena

    char buffer[5];
    size_t len = 1;
    string inputFileName;
    string outputFileName;
    string besedilo;

    while ((opt = getopt(argc, argv, "hi:I:o:O:")) != -1)
    {

        if (opt == -1)
            break;

        switch (opt)
        {
        case 'h':
            print_help();
            return 0;
        case 'i':
            inputFileName = optarg;
            flag_i = true;
            break;
        case 'I':
            flag_I = true;
            fd_in = atoi(optarg);
            if (isalpha(*optarg) || fd_in < 0)
            {
                cerr << "Napaka! Oprimek za branje ni veljavno stevilo!" << endl;
                return 1;
            }
            break;
        case 'o':
            flag_o = true;
            outputFileName = optarg;
            break;
        case 'O':
            flag_O = true;
            fd_out = atoi(optarg);
            if (isalpha(*optarg) || fd_out < 0)
            {
                cerr << "Napaka! Oprimek za pisanje ni veljavno stevilo!" << endl;
                return 1;
            }
            break;
        default:
            print_help();
            return 1;
        }
    }

    if (flag_i)
    {
        fd_in = open(inputFileName.c_str(), O_RDONLY);
        if (fd_in == -1)
        {
            cerr << "Napaka pri odpiranju datoteke " << inputFileName << endl;
            return 1;
        }
        while (1)
        {
            int r = read(fd_in, buffer, len);
            buffer[r] = 0;
            if (r == 0)
                break;
            if (r == -1)
            {
                cerr << "Napaka pri branju datoteke " << inputFileName << endl;
                return 1;
            }
            besedilo += buffer;
        }
        close(fd_in);
    }
    if (flag_I)
    {
        while (1)
        {
            int r = read(fd_in, buffer, len);
            buffer[r] = 0;
            if (r == 0)
                break;
            if (r == -1)
            {
                cerr << "Napaka pri branju datoteke " << inputFileName << endl;
                return 1;
            }
            besedilo += buffer;
        }
    }
    if (fd_in == 0)
    {
        while ((r = read(fd_in, buffer, len)) > 0)
        {
            buffer[r] = 0;
            besedilo += buffer;
        }
        close(fd_in);
    }
    if (flag_o)
    {
        ifstream f(outputFileName);
        if (f.good())
        {
            cerr << "Napaka! Datoteka " << outputFileName << " ze obstaja!" << endl;
            return 1;
        }
        fd_out = open(outputFileName.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            cerr << "Napaka pri odpiranju datoteke " << outputFileName << endl;
            return 1;
        }
        for (int i = 0; i < besedilo.length(); i++)
        {
            string hex = char_to_hex(besedilo[i]);
            hex += "\n";
            int w = write(fd_out, hex.c_str(), hex.length());
            if (w == -1)
            {
                cerr << "Napaka pri pisanju v datoteko " << outputFileName << endl;
                return 1;
            }
        }
        close(fd_out);
    }
    if (flag_O)
    {
        for (int i = 0; i < besedilo.length(); i++)
        {
            string hex = char_to_hex(besedilo[i]);
            hex += "\n";
            int w = write(fd_out, hex.c_str(), hex.length());
            if (w == -1)
            {
                cerr << "Napaka pri pisanju" << endl;
                return 1;
            }
        }
    }
    if (fd_out == 1)
    {
        for (int i = 0; i < besedilo.length(); i++)
        {
            string hex = char_to_hex(besedilo[i]);
            hex += "\n";
            int w = write(fd_out, hex.c_str(), hex.length());
            if (w == -1)
            {
                cerr << "Napaka pri pisanju" << endl;
                return 1;
            }
        }
        close(fd_out);
    }

    return 0;
}