USE 2021_pb_un_matic_lukezic;
ALTER DATABASE 2021_pb_un_matic_lukezic CHARACTER SET 'utf8';
DROP TABLE IF EXISTS stranka_ima_hobi;
DROP TABLE IF EXISTS hobi;
DROP TABLE IF EXISTS stranka_ima_interesno_podrocje;
DROP TABLE IF EXISTS stranka_se_udelezi_prireditev;
DROP TABLE IF EXISTS organizator_organizira_prireditev;
DROP TABLE IF EXISTS stranka_se_udelezi_izlet;
DROP TABLE IF EXISTS destinacija_izlet;
DROP TABLE IF EXISTS izlet;
DROP TABLE IF EXISTS destinacija;
DROP TABLE IF EXISTS prireditev_cenik;
DROP TABLE IF EXISTS clanarina;
DROP TABLE IF EXISTS uspesnost;
DROP TABLE IF EXISTS stranka;
DROP TABLE IF EXISTS organizator;
DROP TABLE IF EXISTS prireditev;
DROP TABLE IF EXISTS naslov;
DROP TABLE IF EXISTS cenik;
DROP TABLE IF EXISTS posta;
DROP TABLE IF EXISTS tip_zveze;
DROP TABLE IF EXISTS interesno_podrocje;
DROP TABLE IF EXISTS sezona;
DROP TABLE IF EXISTS tip_prireditev;

DROP TRIGGER IF EXISTS izr_starost_bef_insert;

CREATE TABLE stranka(
id_stranka INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
ime VARCHAR(20) NOT NULL,
priimek VARCHAR(20) NOT NULL,
spol VARCHAR(20) NOT NULL,
datum_roj DATE NOT NULL,
starost INT,
kadilec_nekadilec TINYINT(1) NOT NULL,
naslov_idNaslov INT NOT NULL,
clanarina_idClanarina INT NOT NULL);

CREATE TABLE posta(
id_posta INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
postna_st INT NOT NULL,
posta VARCHAR(15) NOT NULL);

CREATE TABLE naslov(
id_naslov INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
ulica VARCHAR(30) NOT NULL,
hisna_st VARCHAR(5) NOT NULL,
posta_idPosta INT NOT NULL);

CREATE TABLE cenik(
id_cenik INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
cena DECIMAl(4,2) NOT NULL,
datum_od DATE NOT NULL,
datum_do DATE);

CREATE TABLE clanarina(
id_clanarina INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(20) NOT NULL,
cenik_idCenik INT NOT NULL);

CREATE TABLE tip_zveze(
id_tipZveze INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(20) NOT NULL);

CREATE TABLE uspesnost(
id_uspesnost INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
stranka_idStranka INT NOT NULL,
tip_zveze_idTipZveze INT NOT NULL,
datum_od DATE NOT NULL,
datom_do DATE);

CREATE TABLE interesno_podrocje(
id_interesnoPodrocje INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(40) NOT NULL);

CREATE TABLE stranka_ima_interesno_podrocje(
id_strankaImaInteresnoPodrocje INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
stranka_idStranka INT NOT NULL,
interesnoPodrocje_idInteresnoPodrocje INT NOT NULL);

CREATE TABLE sezona(
id_sezona INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
sezona VARCHAR(15) NOT NULL);

CREATE TABLE hobi(
id_hobi INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(20) NOT NULL,
sezona_idSezona INT NOT NULL);

CREATE TABLE stranka_ima_hobi(
id_strankaImaHobi INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
stranka_idStranka INT NOT NULL,
hobi_idHobi INT NOT NULL);

CREATE TABLE organizator(
id_organizator INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(25) NOT NULL,
tel_st VARCHAR(15) NOT NULL,
elek_naslov VARCHAR(45) NOT NULL,
naslov_idNaslov INT NOT NULL);

CREATE TABLE tip_prireditev(
id_tipPrireditev INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(40) NOT NULL);

CREATE TABLE prireditev(
id_prireditev INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(50) NOT NULL,
datum DATE NOT NULL,
st_ljudi INT NOT NULL,
opis VARCHAR(70) NOT NULL,
tipPrireditev_idTipPrireditev INT NOT NULL,
naslov_idNaslov INT NOT NULL);

CREATE TABLE stranka_se_udelezi_prireditev(
id_strankaPrireditev INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
stranka_idStranka INT NOT NULL,
prireditev_idPrireditev INT NOT NULL);

CREATE TABLE prireditev_cenik(
id_prireditevCenik INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
prireditev_idPrireditev INT NOT NULL,
cenik_idCenik INT NOT NULL);

CREATE TABLE organizator_organizira_prireditev(
id_organizatorOrgPrireditev INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
organizator_idOrganizator INT NOT NULL,
prireditev_idPrireditev INT NOT NULL);

CREATE TABLE izlet(
id_izlet INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
naziv VARCHAR(30) NOT NULL,
datum_od DATE NOT NULL,
datum_do DATE,
opis VARCHAR(50) NOT NULL,
dolzina_poti VARCHAR(10) NOT NULL,
organizator_idOrganizator INT NOT NULL);

CREATE TABLE stranka_se_udelezi_izlet(
id_strankaIzlet INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
stranka_idStranka INT NOT NULL,
izlet_idIzlet INT NOT NULL);

CREATE TABLE destinacija(
id_destinacija INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
drzava VARCHAR(30) NOT NULL);

CREATE TABLE destinacija_izlet(
id_destinacijaIzlet INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
destinacija_idDestinacija INT NOT NULL,
izlet_idIzlet INT NOT NULL);

DELIMITER $$
CREATE TRIGGER izr_starost_bef_insert
    BEFORE INSERT
    ON stranka
    FOR EACH ROW
    BEGIN
	IF NEW.starost IS NULL THEN
        SET NEW.starost = timestampdiff(YEAR, NEW.datum_roj, CURRENT_DATE());
	END IF;
    END $$
DELIMITER ;

ALTER TABLE naslov ADD CONSTRAINT FK_naslov_posta FOREIGN KEY (posta_idPosta) REFERENCES posta (id_posta) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka ADD CONSTRAINT FK_stranka_naslov FOREIGN KEY (naslov_idNaslov) REFERENCES naslov (id_naslov) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE clanarina ADD CONSTRAINT FK_clanarina_cenik FOREIGN KEY(cenik_idCenik) REFERENCES cenik(id_cenik) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE uspesnost ADD CONSTRAINT FK_uspesnost_stranka FOREIGN KEY(stranka_idStranka) REFERENCES stranka(id_stranka) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE uspesnost ADD CONSTRAINT FK_uspesnost_tipZveze FOREIGN KEY(tip_zveze_idTipZveze) REFERENCES tip_zveze(id_tipZveze) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_ima_interesno_podrocje ADD CONSTRAINT FK_strInterPodrocje_interesnoPodrocje FOREIGN KEY(interesnoPodrocje_idInteresnoPodrocje) REFERENCES interesno_podrocje(id_interesnoPodrocje) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_ima_interesno_podrocje ADD CONSTRAINT FK_strInterPodrocje_stranka FOREIGN KEY(stranka_idStranka) REFERENCES stranka(id_stranka) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE hobi ADD CONSTRAINT FK_hobi_sezona FOREIGN KEY(sezona_idSezona) REFERENCES sezona(id_sezona) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_ima_hobi ADD CONSTRAINT FK_strankaImaHobi_stranka FOREIGN KEY(stranka_idStranka) REFERENCES stranka(id_stranka) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_ima_hobi ADD CONSTRAINT FK_strankaImaHobi_hobi FOREIGN KEY(hobi_idHobi) REFERENCES hobi(id_hobi) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE organizator ADD CONSTRAINT FK_organizator_naslov FOREIGN KEY(naslov_idNaslov) REFERENCES naslov(id_naslov) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE prireditev ADD CONSTRAINT FK_prireditev_naslov FOREIGN KEY(naslov_idNaslov) REFERENCES naslov(id_naslov) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE prireditev ADD CONSTRAINT FK_prireditev_tipPrireditev FOREIGN KEY(tipPrireditev_idTipPrireditev) REFERENCES tip_prireditev(id_tipPrireditev) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_se_udelezi_prireditev ADD CONSTRAINT FK_strankaUdeleziPrired_naslov FOREIGN KEY(stranka_idStranka) REFERENCES stranka(id_stranka) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_se_udelezi_prireditev ADD CONSTRAINT FK_strankaUdeleziPrired_prireditev FOREIGN KEY(prireditev_idPrireditev) REFERENCES prireditev(id_prireditev) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE prireditev_cenik ADD CONSTRAINT FK_prireditevCenik_prireditev FOREIGN KEY(prireditev_idPrireditev) REFERENCES prireditev(id_prireditev) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE prireditev_cenik ADD CONSTRAINT FK_prireditevCenik_cenik FOREIGN KEY(cenik_idCenik) REFERENCES cenik(id_cenik) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE organizator_organizira_prireditev ADD CONSTRAINT FK_organizatorOrgPrireditev_organizator FOREIGN KEY(organizator_idOrganizator) REFERENCES organizator(id_organizator) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE organizator_organizira_prireditev ADD CONSTRAINT FK_organizatorOrgPrireditev_prireditev FOREIGN KEY(prireditev_idPrireditev) REFERENCES prireditev(id_prireditev) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE izlet ADD CONSTRAINT FK_izlet_organizator FOREIGN KEY(organizator_idOrganizator) REFERENCES organizator(id_organizator) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_se_udelezi_izlet ADD CONSTRAINT FK_strankaUdeleziIzlet_stranka FOREIGN KEY(stranka_idStranka) REFERENCES stranka(id_stranka) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE stranka_se_udelezi_izlet ADD CONSTRAINT FK_strankaUdeleziIzlet_izlet FOREIGN KEY(izlet_idIzlet) REFERENCES izlet(id_izlet) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE destinacija_izlet ADD CONSTRAINT FK_destinacijaIzlet_destinacija FOREIGN KEY(destinacija_idDestinacija) REFERENCES destinacija(id_destinacija) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE destinacija_izlet ADD CONSTRAINT FK_destinacijaIzlet_izlet FOREIGN KEY(izlet_idIzlet) REFERENCES izlet(id_izlet) ON DELETE CASCADE ON UPDATE NO ACTION;

INSERT INTO sezona VALUES (NULL, 'Letni');
INSERT INTO sezona VALUES(NULL,'Jesenski');
INSERT INTO sezona VALUES(NULL,'Pomladni');
INSERT INTO sezona VALUES(NULL,'Zimski');
INSERT INTO sezona VALUES(NULL, 'Vsi letni časi');

INSERT INTO hobi VALUES(NULL, 'Nogomet', 1);
INSERT INTO hobi VALUES(NULL, 'Košarka', 1);
INSERT INTO hobi VALUES(NULL, 'Rokomet', 5);
INSERT INTO hobi VALUES(NULL, 'Mali nogomet', 5);
INSERT INTO hobi VALUES(NULL, 'Pohodi v hribe', 1);
INSERT INTO hobi VALUES(NULL, 'Tek', 5);
INSERT INTO hobi VALUES(NULL, 'Fotografija', 5);
INSERT INTO hobi VALUES(NULL, 'Branje knjig', 1);
INSERT INTO hobi VALUES(NULL, 'Programiranje', 5);
INSERT INTO hobi VALUES(NULL, 'Kanujanje', 3);

INSERT INTO interesno_podrocje VALUES(NULL, 'Sport');
INSERT INTO interesno_podrocje VALUES(NULL, 'Volitve');
INSERT INTO interesno_podrocje VALUES(NULL, 'Promet in javne povrsine');
INSERT INTO interesno_podrocje VALUES(NULL, 'Kultura');
INSERT INTO interesno_podrocje VALUES(NULL, 'Finance');
INSERT INTO interesno_podrocje VALUES(NULL, 'Gospodarstvo');

INSERT INTO posta VALUES(NULL, 2250, 'Ptuj');
INSERT INTO posta VALUES(NULL, 2000, 'Maribor');
INSERT INTO posta VALUES(NULL, 1000, 'Ljubljana');
INSERT INTO posta VALUES(NULL, 2258, 'Sveti Tomaz');
INSERT INTO posta VALUES(NULL, 2270, 'Ormoz');
INSERT INTO posta VALUES(NULL, 2286, 'Podlehnik');

INSERT INTO tip_zveze VALUES(NULL, 'samski/a');
INSERT INTO tip_zveze VALUES(NULL, 'v zvezi');
INSERT INTO tip_zveze VALUES(NULL, 'odprta zveza');

INSERT INTO cenik VALUES(NULL, 5.99, '2022-01-01', '2022-06-01');
INSERT INTO cenik VALUES(NULL, 4.50, '2022-01-01', NULL);
INSERT INTO cenik VALUES(NULL, 5.50, '2022-04-18', '2022-05-01');
INSERT INTO cenik VALUES(NULL, 3.50, '2022-06-01', '2022-07-01');
INSERT INTO cenik VALUES(NULL, 4.99, '2022-07-06', NULL);
INSERT INTO cenik VALUES(NULL, 0.00, '2022-01-01', NULL);
INSERT INTO cenik VALUES(NULL, 10, '2022-01-01', NULL);

INSERT INTO clanarina VALUES(NULL, 'Trial', 6);
INSERT INTO clanarina VALUES(NULL, 'Popust Junij-Julij', 4);
INSERT INTO clanarina VALUES(NULL, 'VIP', 1);
INSERT INTO clanarina VALUES(NULL, 'Navadni člani', 5);
INSERT INTO clanarina VALUES(NULL, 'Študenti', 2);
INSERT INTO clanarina VALUES(NULL, 'Velikonocni popust',3);

INSERT INTO tip_prireditev VALUES(NULL, 'Koncert');
INSERT INTO tip_prireditev VALUES(NULL, 'Delavnica');
INSERT INTO tip_prireditev VALUES(NULL, 'Kulturna prireditev');
INSERT INTO tip_prireditev VALUES(NULL, 'Javna prireditev');
INSERT INTO tip_prireditev VALUES(NULL, 'Privatna prireitev');
INSERT INTO tip_prireditev VALUES(NULL, 'Veselica');

INSERT INTO naslov VALUES(NULL, 'ulica 5. prekomorske', '2', 1);
INSERT INTO naslov VALUES(NULL, 'Langusova', '19a', 1);
INSERT INTO naslov VALUES(NULL, 'Gornji Ključarovci', '9a', 4);
INSERT INTO naslov VALUES(NULL, 'Podlehnik', '4b', 6);
INSERT INTO naslov VALUES(NULL, 'Podlehnik', '10a', 6);
INSERT INTO naslov VALUES(NULL, 'Mariborski trg', '1a', 2);
INSERT INTO naslov VALUES(NULL, 'Koroska cesta', '46', 2);
INSERT INTO naslov VALUES(NULL, 'ulica 25. maja', '19', 1);
INSERT INTO naslov VALUES(NULL, 'Ptujska cesta' ,'12', 5);
INSERT INTO naslov VALUES(NULL, 'Večna pot', '113', 3);
INSERT INTO naslov VALUES(NULL, 'Žnidaričevo nabrežje' , '2', 1);

INSERT INTO prireditev VALUES(NULL, 'EASTERFEST', '2022-04-17', 2000, 'DJ JNX, DJ DOUBLEZ, Vlko nočni spektakel', 5,  11);
INSERT INTO prireditev VALUES(NULL, 'Veselica v Lancovi vasi', '2022-04-13', 2000, 'Domen Kumer, Grupa Vigor In Gadi', 6,  8);
INSERT INTO prireditev VALUES(NULL, 'Xtime easter', '2022-04-17', 1000, 'DINNA, INAS, Povabi cim vec prijateljev', 6,  9);
INSERT INTO prireditev VALUES(NULL, 'Pokanje 2022 v Cirkulanah', '2022-04-15', 500, 'Prinesite veliko dobre volje', 6,  10);
INSERT INTO prireditev VALUES(NULL, 'Noč čarovnic', '2022-10-05', 3000, 'Z nami bo nagajiva Tanja Žagar', 6,  7);
INSERT INTO prireditev VALUES(NULL, 'Razstava lutk', '2022-07-07', 100, 'Predstava lutk od Andreje Čelan', 2,  6);
INSERT INTO prireditev VALUES(NULL, 'Kako trogovati s kriptovalutami', '2022-04-17', 200, 'Pogovarjali se bomo o osnovah trgovanja s kriptovalutami', 2,  5);
INSERT INTO prireditev VALUES(NULL, 'Beer Pong', '2022-06-01', 300, 'Prijavi sebe in prijatelja, ter se potegujta za nagrado ;)', 6,  4);
INSERT INTO prireditev VALUES(NULL, 'Materinski dan', '2022-03-08', 100, 'Dan za naše mame', 4,  3);
INSERT INTO prireditev VALUES(NULL, 'House Party v Ormožu', '2022-08-08', 2000, 'DJ JNX, DJ DOUBLEZ', 5,  2);
INSERT INTO prireditev VALUES(NULL, '3. srecanje najdenih in porocenih', '2022-08-08', 1500, 'Srecno poroceni', 5,1);

INSERT INTO stranka VALUES(NULL, 'Matic', 'Lukežič', 'moški', '1995-11-07',NULL, 0, 1, 5);
INSERT INTO stranka VALUES(NULL, 'Gal', 'Jeza', 'moški', '2002-09-8', NULL,1, 7, 5);
INSERT INTO stranka VALUES(NULL, 'Jure', 'Miklošič', 'moški', '2001-07-01',NULL, 1, 9, 1);
INSERT INTO stranka VALUES(NULL, 'Simon', 'Plazar', 'moški', '2002-05-02', NULL,1, 10, 1);
INSERT INTO stranka VALUES(NULL, 'Nika', 'Visenjak', 'ženski', '2002-07-07', NULL,0, 3, 5);
INSERT INTO stranka VALUES(NULL, 'Maša', 'Gašparič', 'ženski', '2002-01-18', NULL,0, 3, 3);
INSERT INTO stranka VALUES(NULL, 'Vid', 'Čabrian', 'moški', '2002-09-11',  NULL,0,2, 6);
INSERT INTO stranka VALUES(NULL, 'Klara', 'Toplak', 'ženski', '1994-05-18',NULL,0, 4, 4);
INSERT INTO stranka VALUES(NULL, 'Nejc', 'Lukežič', 'moški', '1990-05-18', NULL,0, 8, 4);
INSERT INTO stranka VALUES(NULL, 'Ema', 'Bratušek', 'ženski', '2004-11-07', NULL,0, 1, 1);
INSERT INTO stranka VALUES(NULL, 'Maja', 'Mihelič', 'ženski', '1997-02-15', NULL,0,2,3);
INSERT INTO stranka VALUES(NULL, 'Franc', 'Vrbančič', 'moški', '1956-06-18',  NULL,0,4,1);
INSERT INTO stranka VALUES(NULL, 'Marjan', 'Čeh', 'moški', '1972-04-19', NULL,0, 3,5);

INSERT INTO uspesnost VALUES(NULL, 1, 1, '2021-02-14', NULL);
INSERT INTO uspesnost VALUES(NULL, 2, 1, '2017-06-12', NULL);
INSERT INTO uspesnost VALUES(NULL, 3, 2, '2021-09-01', NULL);
INSERT INTO uspesnost VALUES(NULL, 4, 1, '2021-01-18', NULL);
INSERT INTO uspesnost VALUES(NULL, 5, 1, '2022-05-19', NULL);
INSERT INTO uspesnost VALUES(NULL, 6, 1, '2022-02-14', NULL);
INSERT INTO uspesnost VALUES(NULL, 7, 2, '2019-04-19', NULL);
INSERT INTO uspesnost VALUES(NULL, 8, 3, '2018-07-07', '2020-03-03');
INSERT INTO uspesnost VALUES(NULL, 9, 1, '2015-12-25', NULL);
INSERT INTO uspesnost VALUES(NULL, 10, 2, '2012-11-07', NULL);

INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 1, 1);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 2, 1);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 3, 2);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 4, 3);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 5, 3);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 6, 7);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 7, 7);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 8, 8);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 9, 9);
INSERT INTO stranka_se_udelezi_prireditev VALUES(NULL, 10, 10);

INSERT INTO stranka_ima_hobi VALUES(NULL, 1, 1);
INSERT INTO stranka_ima_hobi VALUES(NULL, 1, 3);
INSERT INTO stranka_ima_hobi VALUES(NULL, 10, 9);
INSERT INTO stranka_ima_hobi VALUES(NULL, 3, 2);
INSERT INTO stranka_ima_hobi VALUES(NULL, 5, 3);
INSERT INTO stranka_ima_hobi VALUES(NULL, 6, 4);
INSERT INTO stranka_ima_hobi VALUES(NULL, 2, 5);
INSERT INTO stranka_ima_hobi VALUES(NULL, 2, 6);
INSERT INTO stranka_ima_hobi VALUES(NULL, 7, 3);
INSERT INTO stranka_ima_hobi VALUES(NULL, 8, 6);
INSERT INTO stranka_ima_hobi VALUES(NULL, 9, 7);
INSERT INTO stranka_ima_hobi VALUES(NULL, 5,5);
INSERT INTO stranka_ima_hobi VALUES(NULL, 6,5);

INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 5, 1);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 6, 5);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 2, 5);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 3, 2);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 7, 3);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 8, 5);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 1, 6);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 1, 2);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 6, 4);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 9, 4);
INSERT INTO stranka_ima_interesno_podrocje VALUES(NULL, 10, 3);

INSERT INTO prireditev_cenik VALUES(NULL, 1, 7);
INSERT INTO prireditev_cenik VALUES(NULL, 2, 7);
INSERT INTO prireditev_cenik VALUES(NULL, 3, 7);
INSERT INTO prireditev_cenik VALUES(NULL, 4, 2);
INSERT INTO prireditev_cenik VALUES(NULL, 5, 7);
INSERT INTO prireditev_cenik VALUES(NULL, 6, 2);
INSERT INTO prireditev_cenik VALUES(NULL, 7, 7);
INSERT INTO prireditev_cenik VALUES(NULL, 8, 2);
INSERT INTO prireditev_cenik VALUES(NULL, 9, 2);
INSERT INTO prireditev_cenik VALUES(NULL, 10, 7);

INSERT INTO organizator VALUES(NULL, 'EASTERFEST', '051432678', 'efest@gmail.com', 2);
INSERT INTO organizator VALUES(NULL, 'Cirkulane', '030784321', 'obcinacirkulane@gmail.com', 5);
INSERT INTO organizator VALUES(NULL, 'Sonček', '032467009', 'soncek@gmail.com', 1);
INSERT INTO organizator VALUES(NULL, 'Xtime', '050678443', 'xtime@gmail.com', 8);
INSERT INTO organizator VALUES(NULL, 'DJ JNX', '041334678', 'jnx@gmail.com', 4);
INSERT INTO organizator VALUES(NULL, 'Relax', '040674554', 'relax@gmail.com', 9);
INSERT INTO organizator VALUES(NULL, 'Moškajnci', '051332456', 'obcinamoskajnci@gmail.com', 7);
INSERT INTO organizator VALUES(NULL, 'Lancova vas', '031678904', 'lancovavas@gmail.com', 6);
INSERT INTO organizator VALUES(NULL, 'Campus Ptuj', '041235789', 'ptuj.campus@gmail.com', 10);
INSERT INTO organizator VALUES(NULL, 'OŠ Ljudski vrt', '030223111', 'osljudski-vrt@gmail.com', 3);

INSERT INTO organizator_organizira_prireditev VALUES(NULL, 1, 1);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 4, 3);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 4, 5);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 10, 6);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 10, 7);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 7, 8);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 8, 2);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 10, 9);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 9, 6);
INSERT INTO organizator_organizira_prireditev VALUES(NULL, 1, 10);

INSERT INTO izlet VALUES(NULL, 'Izlet na ptujski grad', '2022-05-04', NULL, 'Pridružite se nam na kratek pohod na ptujski grad', '23km', 10);
INSERT INTO izlet VALUES(NULL, 'Izlet na Donačko goro', '2022-05-01', NULL, 'Pridružite se nam na kratkem pohodu na Donačko', '12km', 10);
INSERT INTO izlet VALUES(NULL, 'Španija', '2022-09-08', '2022-09-15', 'Eno tedenski izlet nv Španijo', '450km', 6);
INSERT INTO izlet VALUES(NULL, 'Izlet v Ljubljano', '2022-06-01', NULL, 'Šolski izlet v Ljubljano', '150km', 10);
INSERT INTO izlet VALUES(NULL, 'Terme topolščica', '2022-04-21', '2022-04-023', 'Izlet v terme topolščica', '23km', 3);
INSERT INTO izlet VALUES(NULL, 'Izlet na Tenerife', '2022-07-08', NULL, 'Izlet na Tenerife', '1001km', 6);
INSERT INTO izlet VALUES(NULL, 'Izlet na Irsko', '2022-05-05', '2022-05-10', 'Izlet na Irsko', '1500km', 6);
INSERT INTO izlet VALUES(NULL, 'Izlet v London', '2022-04-04', '2022-04-11', 'Izlet v London', '999km', 3);
INSERT INTO izlet VALUES(NULL, 'Izlet na Havaje', '2022-09-09', '2022-09-13', 'Izlet na HAVAJEEEEEE', '709km', 3);
INSERT INTO izlet VALUES(NULL, 'Izlet v Maribor', '2022-05-04', NULL, 'Izlet v Maribor', '40km', 6);

INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 1, 1);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 2, 5);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 3, 6);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 4, 2);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 5, 7);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 6, 7);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 7, 5);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 8, 5);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 9, 1);
INSERT INTO stranka_se_udelezi_izlet VALUES(NULL, 10, 1);

INSERT INTO destinacija VALUES(NULL, 'Slovenija');
INSERT INTO destinacija VALUES(NULL, 'Havaji');
INSERT INTO destinacija VALUES(NULL, 'Tenerifi');
INSERT INTO destinacija VALUES(NULL, 'Irska');
INSERT INTO destinacija VALUES(NULL, 'Velika Britanija');
INSERT INTO destinacija VALUES(NULL, 'Španija');

INSERT INTO destinacija_izlet VALUES(NULL, 1,1);
INSERT INTO destinacija_izlet VALUES(NULL, 1,2);
INSERT INTO destinacija_izlet VALUES(NULL, 6,3);
INSERT INTO destinacija_izlet VALUES(NULL, 1,4);
INSERT INTO destinacija_izlet VALUES(NULL, 1,5);
INSERT INTO destinacija_izlet VALUES(NULL, 3,6);
INSERT INTO destinacija_izlet VALUES(NULL, 4,7);
INSERT INTO destinacija_izlet VALUES(NULL, 5,8);
INSERT INTO destinacija_izlet VALUES(NULL, 2,9);
INSERT INTO destinacija_izlet VALUES(NULL, 1,10);
