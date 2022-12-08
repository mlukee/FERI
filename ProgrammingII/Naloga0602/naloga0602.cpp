#include <iostream>
#include "Guitar.h"
#include "Piano.h"
#include "Concert.h"

int main() {

    Concert c1 ("Mama mia");
    std::cout << "Welcome to the concert: " << c1.getName() << std::endl;
    c1.addInstrument(new Guitar{"13", "Alabama", 0, GuitarType::Electric});
    c1.addInstrument(new Piano{"1", "1st row",1, PianoType::Grand});
    c1.addInstrument(new Piano{"0", "2nd row", 0,PianoType::Digital});
    c1.addInstrument(new Guitar{"99", "MiniME", 1, GuitarType::Ukulele});
    c1.addInstrument(new Guitar{"77", "Rock&Roll", 1, GuitarType::Electric});
    std::cout << "\nInstruments: " << std::endl;
    c1.printAllInstruments();

}
