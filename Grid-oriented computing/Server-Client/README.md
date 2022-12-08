## Vaja2 - TCP Vtičnice

Na teh vajah se boste seznanili s komunikacijo programov z **vtičnicami** (sockets). Implementirali boste **dve konzolni aplikaciji** (strežnik in odjemalec). Za komunikacijo med njima boste uporabili **vtičnice**, po katerih si boste pošiljali sporočila. Sporočila lahko pošiljate v obliki nizov ali binarno. Pri programiranju poskrbite za robustnost obeh aplikacij (uporaba izjem, lep izpis napak pri komunikaciji, ...).

Strežnik naj vedno čaka na nove odjemalce. Vsak dogodek (nov odjemalec, novo prejeto sporočilo, novo poslano sporočilo) naj se ustrezno izpiše v ukazni vrstici. Odjemalec naj omogoča pošiljanje sporočil na strežnik. Pri tem se naj vsa prejeta sporočila izpisujejo v ukazni vrstici. 

Za uspešno implementacijo naloge boste morali definirati **protokol**. To je **dogovor o načinu pošiljanja in obliki** sporočil. Protokol zasnujte sami. Pri protokolu uporabite obliko **glava-vsebina** (header-payload), kjer glava sporočila hrani tip, preostanek pa vsebino sporočila. Kadar strežnik prejme ustrezno sporočilo, naj vrača naslednje:

- A. Niz "Pozdravljen [IP NASLOV ODJEMALCA:VRATA ODJEMALCA]"
- B. Trenutni datum in čas
- C. Trenutni delovni direktorij
- D. Sporočilo, ki ga je pravkar prejel
- E. Sistemske informacije (ime računalnika in verzija operacijskega sistema)
- F. Obdelava in lep izpis Forsyth-Edwards notacije (FEN)  stanja šahovskih figur na šahovnici (primer: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1)
- G. Šifriranje sporočila s TripleDES algoritmom; na odjemalcu omogočite dešifriranje; ključ za šifriranje določite sami
