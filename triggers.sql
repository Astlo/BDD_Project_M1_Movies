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
	temps number;
BEGIN
	--SELECT YEAR(‘2014-01-01’) into temps FROM Temps;
	--SELECT extract(year from CAST(FROM_UNIXTIME(colonne_timestamp) as date2) as valeur_date) into temps FROM Temps;
	--UPDATE Temps SET jour = 01, mois = 01, annee = temps;
	SELECT colonne_timestamp, 
  FROM_UNIXTIME(colonne_timestamp) as valeur_datetime
FROM Temps;
END;
/