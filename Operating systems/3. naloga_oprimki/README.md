# Oprimki

## Navodila

Napišite ukazni program **hexprint**, ki iz vhoda bere zloge in jih izpisuje na izhod kot heksadecimalne vrednosti (s predpono 0x). Pri tem naj vsako vrednost na izhodu zapiše v novo vrstico. Pri izpisu heksadecimalnih vrednosti (0x8A) naj bo "x" v predponi "0x" zapisan z malimi črkami, števke pa z velikimi črkami.


Privzeto je vhod nastavljen na standardni vhod in izhod na standardni izhod.

 
Program naj podpira uporabo dodatnih zastavic, s katerimi lahko nastavimo drug vhod ali izhod:

 -h Izpis pomoči z vsemi zastavicami in njihovimi opisi.
 
-i zbirka - Kot vhod program odpre in uporabi zbirko/napravo s podano potjo. V primeru, da zbirka/naprava s podano potjo ne obstaja, program vrne napako.

-I oprimek - Kot vhod program uporabi podan oprimek.

-o zbirka - Kot izhod program ustvari in uporabi zbirko/napravo s podano potjo. V primeru, da zbirka/naprava s podano potjo že obstaja, program vrne napako.

-O oprimek - Kot izhod program uporabi podan oprimek.

 
V primeru napake naj program na standardni izhod za napake izpiše kratek opis napake in vrne vrednost 1. Če do napake ni prišlo, program vrne vrednost 0.
 

Program naj bo zasnovan tako, da bo obdelal poljubno dolg tok zlogov na vhodu. Nikoli naj ne hrani celotnega toka zlogov v pomnilniku naenkrat.


## Primeri delovanja
Primer branja iz standardnega vhoda in pisanja na standardni izhod (privzeto delovanje):
```
$ echo -n abcjkl | ./hexprint
0x61
0x62
0x63
0x6A
0x6B
0x6C
```
Primer branja iz podane datoteke in pisanja na podan oprimek (uporaba zastavic):
```
$ echo -n abcjkl > input.txt
$ ./hexprint -i input.txt -O 5 5>output.txt
$ cat output.txt
0x61
0x62
0x63
0x6A
0x6B
0x6C
```
## Funkcionalnosti rešitve

- argumenti
  - poljuben vrstni red
- branje
  - iz standardnega vhoda
  - iz podane zbirke
  - iz podanega oprimka
- pisanje
  - na standardni izhod
  - v podano zbirko
  - na podan oprimek
- napake in opozorila
  - kadar vhodna zbirka ne obstaja
  - kadar vhodne zbirke ne moremo odpreti za branje
  - kadar izhodna zbirka že obstaja
  - kadar ni mogoče ustvariti in odpreti izhodne zbirke za pisanje
