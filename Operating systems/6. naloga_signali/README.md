## Navodila
Napišite program za zaganjanje poslov z imenom **simplecron**.
 Posamezen posel je sestavljen iz želenega datuma in časa izvedbe ter 
ukaza. Program seznam vseh poslov prebere iz konfiguracijske datoteke, 
ki jo podamo kot prvi argument pri zagonu programa. Vsak posel v 
konfiguracijski datoteki se nahaja v svoji vrstici, vrednosti pa so med 
seboj ločene z enojnimi presledki. Simbol "#" označuje komentar. Oblika 
zapisa posameznega posla je naslednja:
```
.-------------- sekunda (0 - 59)
| .------------ minuta (0 - 59)
| | .---------- ura (0 - 23)
| | | .-------- dan (1 - 31)
| | | | .------ mesec (1 - 12)
| | | | | .---- leto (0 - 99)
| | | | | | .-- ukaz
| | | | | | |
s m h d m y cmd
```
Primer treh poslov v konfiguracijski datoteki:
```
# 1.2.2023 ob 07:04:10 izvedi ukaz 'echo "job_3"'
10 4 7 1 2 23 echo "job_3"

# 3.4.2021 ob 08:05:20 izvedi ukaz 'echo "job_1"'
20 5 8 3 4 21 echo "job_1"

# 5.6.2022 ob 09:06:30 izvedi ukaz 'echo "job_2"'
30 6 9 5 6 22 echo "job_2"
```
Branje poslov iz konfiguracijske datoteke je že pripravljeno v 
paketu s projektom in preizkusi. Funkcija za branje "struct job_node 
*read_job_list(const char *path)" kot edini argument prejme pot do 
konfiguracijske datoteke ter vrne enojno povezan seznam poslov. 
Posamezen element v seznamu je predstavljen s strukturo "struct 
job_node", ki vsebuje datum in čas izvedbe, ukaz ter kazalec na 
naslednji element. Datum in čas izvedbe sta v strukturi predstavljena 
kot število preteklih sekund od 1.1.1970 00:00:00 +0000 (UTC) oziroma v 
obliki kot ga vrne funkcija "time". Zadnji element kaže na NULL. Pred 
zaključkom glavnega programa morate seznam ustrezno sprostiti, kar 
storite z že pripravljeno funkcijo "void free_job_list(struct job_node 
*job_list)", ki kot argument prejme prej pridobljeni seznam. V funkciji 
"int main(int argc, char **argv)" glavne datoteke "main.c" se nahaja 
primer uporabe zgoraj omenjenih dveh funkcij in izpis vsebine seznama.

 

Vaša naloga je, da se sprehodite čez seznam poslov, in ob želenem 
datumu ter času izvedbe zaženete podan ukaz. Če sta datum in čas izvedbe
 v prihodnosti, uporabite funkcijo "alarm" in lovljenje signala SIGALRM,
 da posel zaženete ob podanem datumu in času. V primeru, da sta datum in
 čas izvedbe v preteklosti, posel zaženite takoj. Za zagon ukaza 
posameznega posla lahko uporabite funkcijo "system". Med čakanjem na 
signal lahko proces pošljete v spanje s funkcijo "pause", po prejetem 
signalu pa se bo izvajanje procesa nadaljevalo.

 

Program naj podpira lovljenje signalov SIGINT in SIGTERM. V 
primeru, da prestreže katerega izmed njiju, program izpiše seznam 
poslov, ki se še niso izvedli, nato pa se zaključi. Za posamezen 
neizveden posel izpišite datum in čas izvedbe posla ter njegov ukaz iz 
strukture "struct job_node", ločeno s presledkom.

 

Pazite, da se program ne obesi, če v konfiguracijski datoteki ni nobenega posla.

 

Če program zaženemo brez argumentov (konfiguracijske datoteke) ali v
 primeru pojava katere izmed ostalih napak, program na standardni izhod 
za napake izpiše opozorilo in vrne vrednost 1. Če do napake ni prišlo, 
program vrne vrednost 0.

## Primeri delovanja
Primer zagona programa, kjer se prvi posel izvede takoj, drugi čez 5 sekund in tretji čez 10 sekund:
```
$ echo $(date +"%-S %-M %-H %-d %-m %-y" -d "-5 seconds") "echo job_1" > simplecron.conf \
&& echo $(date +"%-S %-M %-H %-d %-m %-y" -d "+5 seconds") "echo job_2" >> simplecron.conf \
&& echo $(date +"%-S %-M %-H %-d %-m %-y" -d "+10 seconds") "echo job_3" >> simplecron.conf \
&& ./exec/simplecron simplecron.conf
job_1
job_2
job_3
```
Primer zagona programa, kjer se prvi posel izvede takoj, drugi čez 3 
sekunde, po 5 sekundah pa se programu pošlje signal SIGTERM:

```
$ echo $(date +"%-S %-M %-H %-d %-m %-y" -d "-5 seconds") "echo job_1" > simplecron.conf \
&& echo $(date +"%-S %-M %-H %-d %-m %-y" -d "+3 seconds") "echo job_2" >> simplecron.conf \
&& echo $(date +"%-S %-M %-H %-d %-m %-y" -d "+10 seconds") "echo job_3" >> simplecron.conf; \
./exec/simplecron simplecron.conf & sleep 5; kill -SIGTERM $!; wait
job_1
job_2
1668682602 echo job_3
```
## Funkcionalnosti rešitve

- argumenti
  - pot do konfiguracijske datoteke
- lovljenje signalov
  - lovljenje signala SIGALRM
  - lovljenje signala SIGINT
  - lovljenje signala SIGTERM
- zagon poslov
  - takojšnji zagon preteklih poslov
  - zagon prihodnjih poslov ob želenem datumu in času
  - zagon hkratnih poslov
  - izpis neizvedenih poslov
- napake
  - manjkajoč argument s konfiguracijsko datoteko
