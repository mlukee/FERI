USE 2021_pb_un_matic_lukezic;
DROP TRIGGER IF EXISTS izr_starost_bef_insert;

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

INSERT INTO stranka VALUES(NULL, 'Enej', 'Petrovic', 'moški', '2002-05-09',NULL, 0, 1, 5);
INSERT INTO stranka VALUES(NULL, 'Mato', 'Kovacic', 'moški', '2002-05-09',18, 0, 1, 5);
INSERT INTO stranka VALUES(NULL, 'Erazem', 'Ceh', 'moški', '1992-08-01',NULL, 0, 1, 5); 


START TRANSACTION;
SAVEPOINT sp;
INSERT INTO stranka VALUES(NULL, 'Luka', 'Gomilsek', 'moški', '1989-11-09',NULL, 0, 4, 3);
SELECT @maxID:=MAX(id_stranka) FROM stranka;
INSERT INTO uspesnost VALUES(NULL, @maxID, 1, '2006-03-13', NULL);

SAVEPOINT sp1;
INSERT INTO stranka VALUES(NULL, 'Gorazd', 'Gavez', 'moški', '2001-05-18',NULL, 0, 4, 3);
SELECT @maxID:=MAX(id_stranka) FROM stranka;
INSERT INTO uspesnost VALUES(NULL, @maxID, 4, '2001-05-18', NULL);
ROLLBACK TO sp1;

