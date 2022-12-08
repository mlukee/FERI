## Navodila
Napišite skripto **listproc**, ki poišče in izpiše seznam trenutnih procesov, ki ustrezajo iskalnim kriterijem podanim preko zastavic. Procese poiščite z neposrednim preiskovanjem zbirčnega sistema proc, običajno pripetega na /proc. Uporaba ukazov kot so ps, top, htop in ostalih, ki vrnejo že formatiran seznam procesov, ni dovoljena. Za vsak najden proces, ki ustreza iskalnim kriterijem, izpišite naslednje vrednosti: identifikator (pid), trenutno stanje, velikost virtualnega pomnilnika v zlogih in ime ukaza. Vrednosti med seboj ločite z dvopičjem ":", izpis posameznega procesa pa naj se nahaja v novi vrstici. Izpise prav tako uredite glede na vrednosti PID naraščajoče. Bodite pozorni na to, da se lahko v imenu ukaza nahajajo tudi presledki " ".
 

Primer izpisa treh procesov, ki ustrezajo iskalnim kriterijem:
```
31925:S:2416640:prog__AB
31928:S:2551808:prog__AB
31931:S:3604480:prog  C
```
Privzeto, če skripti ne podamo nobene izmed zastavic, skripta izpiše pomoč.
 
Skripta naj podpira uporabo naslednjih zastavic, s katerimi nastavimo iskalne kriterije:

-h  -> Izpis pomoči z vsemi zastavicami in njihovimi opisi.

-c ukazno_ime -> Izpis procesov, katerih program ima podano ukazno ime.

-d delovna_pot -> Izpis procesov, katerih delovna pot ustreza podani. Delovna pot je lahko podana relativno.

-e pot_programa -> Izpis procesov, ki izvajajo podan program. Pot programa je lahko podana relativno.

 
Zastavice -c, -d in -e lahko kombiniramo med seboj. V primeru uporabe več zastavic program izpiše tiste procese, ki ustrezajo vsem podanim kriterijem (logični in).
 
V primeru napake naj skripta na standardni izhod za napake izpiše kratek opis napake in vrne vrednost 1. Če do napake ni prišlo, skripta vrne vrednost 0.
## Primeri delovanja
Primer uporabe skripte z eno zastavico:
```
$ (cd bin/path_A/ && ./prog__AB) &
$ (cd bin/ && ./path_A/prog__AB) &
$ (cd bin/path_C/ && ./"prog  C") &

$ ./listproc -c prog__AB
19957:S:2416640:prog__AB
19995:S:2416640:prog__AB

$ ./listproc -c "prog  C"
20083:S:3604480:prog  C
```
Primer uporabe skripte z dvema zastavicama:
```
$ (cd bin/path_A/ && ./prog__AB) &
$ (cd bin/ && ./path_A/prog__AB) &
$ (cd bin/path_C/ && ./"prog  C") &

$ ./listproc -c prog__AB -d bin/
19995:S:2416640:prog__AB

$ ./listproc -c prog__AB -d bin/null/
```
Funkcionalnosti rešitve

- argumenti
    - poljuben vrstni red
   -  kombiniranje več argumentov
- izpis seznama procesov
   -  upoštevanje iskalnih kriterijev
    - izpis v predpisani obliki
    - delovanje pri posamezni zastavici
    - delovanje pri kombiniranih zastavicah
- napake in opozorila
   -  neveljavna zastavica
    - zastavici manjka argument

