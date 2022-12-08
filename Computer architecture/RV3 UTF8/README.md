Napišite program (npr. v C++, dovoljena uporaba cin, cout in string brez ostalih knjižnic!), ki bo **kodiral in dekodiral** znake po standardu Unicode v kodiranju UTF-8.

Univerzalni nabor znakov (UCS - Universal Character Set, ISO/IEC 10646), ki jih UTF-8 kodira, obsega 1114111 znakov, tj. 10FFFF (hex).

- Pri tem kodi 0xFF in 0xFE nista dovoljeni in ob dekodiranju takšne kode izpišite opozorilo o napaki.
- Ob izpisu kontrolnih znakov izpišite samo njihovo zaporedno kodno številko UCS-4. (Če imate vnos/izpis HEX ali BIN, lahko preskočite to točko.)
- Pri dekodiranju opozorite na dekodiranje manjšega števila, kot dovoljuje bajtni nabor (npr. 0xC0, 0x80 je enako 0x00)


Vnos podatkov: pri kodiranju lahko vnesete binarni niz, heksadecimalni ali kar celo desetiško število (integer), izpis pa naj bo število v binarni ali heksadecimalni obliki **(koda UTF-8 ni potrebno izpisati v obliki znaka na ekran)**. Pri dekodiranju vnesite heksadecimalno število ali binarno število, kot rezultat izpišete lahko tudi celo desetiško število. IZBERITE **ENEGA OD** načinov vnosa/izpisa (HEX ali BIN ali DEC), ni potrebno vseh kombinacij (npr. HEX+BIN).

PRIMER:

Vnesite število za kodiranje: 03 A9

Rezultat kodiranja UTF-8 je: CE A9

Vnesite kod UTF-8 za dekodiranje: CE A9

Rezultat dekodiranja UTF-8 je: 03 A9


----------------

English
---------------
Write a program (such as C ++ using cin, cout, and string, without other libraries!) to encode and decode characters by the standard Unicode encoding UTF-8.

Universal character set (UCS - Universal Character Set, ISO / IEC 10646) that is in the UTF-8 encodes 1,114,111 characters, ie. 10FFFF (hex).

- The code 0xff and 0xFE are not allowed and the decoding of such codes has to display an error.
- When displaying control characters write out only their serial code number of UCS-4. (If your input/output is HEX or BIN, you can skip this bullet.)
- When decoding, alert about lower value of decoding, then permitted by decoded byte range (eg, 0xC0, 0x80 equals 0x00)

Data Entry: You may enter a binary string, hexadecimal or even a decimal number (integer), when encoding; the printout should be in binary or hexadecimal form **(no UTF-8 code needs to be printed as a character on the screen)**. When decoding, enter a hexadecimal number or binary number, and you may also print out result as a decimal number. CHOOSE **ONE OF** ways to enter/print data (HEX or BIN or DEC), it is not necessary to program all combinations (e.g. HEX+BIN).

EXAMPLE:

Enter number for encoding: 03 A9

Result of UTF-8 encoding is: CE A9

Enter code UTF-8 for coding: CE A9

Result of decoding UTF-8 is: 03 A9
