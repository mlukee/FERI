USE 2021_pb_un_matic_lukezic;

#1. Katera zenska, nekadilka, rada hodi v hribe?
SELECT stranka.id_stranka, stranka.ime, stranka.priimek, hobi.naziv AS hobi FROM stranka JOIN stranka_ima_hobi ON stranka.id_stranka = stranka_ima_hobi.stranka_idStranka JOIN hobi ON hobi.id_hobi = stranka_ima_hobi.hobi_idHobi WHERE stranka.spol='ženski' AND stranka.kadilec_nekadilec=0 AND hobi.naziv='Pohodi v hribe';

#2. Izpisite vse kategorije prireditev in pripadajoce prireditve. Kategorije naj se izpisejo, tudi ce v njih ni se nobene prireditve
SELECT tip_prireditev.naziv as tip_prireditev, prireditev.naziv as prireditev FROM tip_prireditev LEFT JOIN prireditev ON (tip_prireditev.id_tipPrireditev = prireditev.tipPrireditev_idTipPrireditev);

#3. Izracunanje trenutno starost vsakega clana glede na datum rojstva.
SELECT stranka.ime, stranka.priimek, timestampdiff(YEAR, datum_roj, CURRENT_DATE()) AS starost FROM stranka;

#4. Koliko samskih oseb se je udelezilo posameznih prireditev in izletov?
SELECT * FROM 
(SELECT  prireditev.naziv, COUNT(prireditev.naziv) as stLjudi FROM stranka
LEFT JOIN stranka_se_udelezi_prireditev ON stranka.id_stranka=stranka_se_udelezi_prireditev.stranka_idStranka 
LEFT JOIN prireditev ON prireditev.id_prireditev=stranka_se_udelezi_prireditev.prireditev_idPrireditev 
JOIN uspesnost ON stranka.id_stranka=uspesnost.stranka_idStranka
JOIN tip_zveze ON tip_zveze.id_tipZveze=uspesnost.tip_zveze_idTipZveze WHERE tip_zveze.naziv='samski/a' GROUP BY prireditev.naziv) t1
union
(SELECT izlet.naziv, COUNT(izlet.naziv) as stLjudi FROM stranka 
LEFT JOIN stranka_se_udelezi_izlet ON stranka.id_stranka=stranka_se_udelezi_izlet.stranka_idStranka 
LEFT JOIN izlet ON izlet.id_izlet=stranka_se_udelezi_izlet.izlet_idIzlet
JOIN uspesnost ON stranka.id_stranka=uspesnost.stranka_idStranka
JOIN tip_zveze ON tip_zveze.id_tipZveze=uspesnost.tip_zveze_idTipZveze WHERE tip_zveze.naziv='samski/a' GROUP BY izlet.naziv);

# 5. Katero interesno podrocje ima najvec oseb?
SELECT * FROM (SELECT interesno_podrocje.naziv, COUNT(interesno_podrocje.naziv) as st_oseb FROM stranka 
JOIN stranka_ima_interesno_podrocje ON stranka_ima_interesno_podrocje.id_strankaImaInteresnoPodrocje=stranka.id_stranka 
JOIN interesno_podrocje ON interesno_podrocje.id_interesnoPodrocje=stranka_ima_interesno_podrocje.interesnoPodrocje_idInteresnoPodrocje 
GROUP BY interesno_podrocje.naziv) as st_ljudi 
HAVING st_oseb=(SELECT MAX(st_oseb) FROM (SELECT interesno_podrocje.naziv, COUNT(interesno_podrocje.naziv) as st_oseb FROM stranka 
JOIN stranka_ima_interesno_podrocje ON stranka_ima_interesno_podrocje.id_strankaImaInteresnoPodrocje=stranka.id_stranka 
JOIN interesno_podrocje ON interesno_podrocje.id_interesnoPodrocje=stranka_ima_interesno_podrocje.interesnoPodrocje_idInteresnoPodrocje 
GROUP BY interesno_podrocje.naziv) as st_ljudije);
                    
#6. Izpisi moske, ki so starejsi od povprecne starosti vseh oseb v podatkovni bazi
SELECT ime, priimek, timestampdiff(YEAR, datum_roj, CURRENT_DATE()) as starost, (SELECT AVG(timestampdiff(YEAR, datum_roj, CURRENT_DATE())) FROM stranka) as avg_starost 
FROM stranka WHERE spol='moški' GROUP BY id_stranka HAVING starost > (SELECT AVG(timestampdiff(YEAR, datum_roj, CURRENT_DATE())) FROM stranka);

#7. Spremeni ime osebe Maja Mihelič v Maja Mihelič Mali
UPDATE stranka SET stranka.priimek = 'Mihelič Mali' WHERE (ime='Maja' and priimek='Mihelic' and id_stranka <> 0);

#8. Izbrisi prireditev z nazivom 3. srecanje najdenih in porocenih
DELETE FROM prireditev WHERE (naziv = '3. srecanje najdenih in porocenih' and id_prireditev <> 0);