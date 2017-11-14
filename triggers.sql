--@triggers.sql

set serveroutput on;

CREATE OR REPLACE TRIGGER tr_jour_mois_annee_insert 
BEFORE INSERT ON Temps
FOR EACH ROW
DECLARE
	error_not_null EXCEPTION;
BEGIN
	IF :new.jour != NULL or :new.mois != NULL or :new.annee != NULL
	THEN raise error_not_null;
	END IF;
	EXCEPTION
	WHEN error_not_null THEN
		RAISE_APPLICATION_ERROR(-20001,'le jour, le mois et l''annee doivent être null à l''insertion');
END;
/

CREATE OR REPLACE TRIGGER tr_jour_mois_annee_maj 
AFTER INSERT ON Temps
FOR EACH ROW
DECLARE
	tannee number;
	tmois number;
	tjour number;
BEGIN
	SELECT EXTRACT(YEAR FROM :new.colonne_timestamp) into tannee FROM Temps;
	SELECT EXTRACT(MONTH FROM :new.colonne_timestamp) into tmois FROM Temps;
	SELECT EXTRACT(DAY FROM :new.colonne_timestamp) into tjour FROM Temps;
	UPDATE Temps SET jour = tjour, mois = tmois, annee = tannee;
END;
/