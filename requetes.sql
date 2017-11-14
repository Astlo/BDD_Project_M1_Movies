--@requetes.sql

--GROUP BY : la moyenne des notes utilisateurs pour le tag ?
SELECT AVG(rating), userTag
FROM Rating


-- Somme de l'argent du box office de tous les films pour chaque année
SELECT annee, SUM(movieBoxOffice) AS boxOffice
FROM Movies NATURAL JOIN Temps NATURAL JOIN Rating
WHERE movieBoxOffice IS NOT NULL AND annee IS NOT NULL
GROUP BY GROUPING SETS (annee);


-- Les 10 films ayant reçus les meilleurs ratings, par rapport à leur rang dans le box office
SELECT movieTitle, rating, RANK() over (ORDER BY movieBoxOffice DESC) AS rangBoxOffice
FROM Movies NATURAL JOIN Rating
WHERE rownum <= 10
ORDER BY rating DESC;

--Les 20 meilleurs succès au box office triés par les producteurs (partition by)
SELECT movieProduction, movieTitle, annee, movieBoxOffice, rank() OVER (PARTITION BY movieProduction ORDER BY movieBoxOffice DESC) AS rank
FROM Movies NATURAL JOIN Temps NATURAL JOIN Rating
WHERE rownum <= 20;

--Le film ayant reçu la meilleure notation pour chaque année
SELECT movieTitle, annee, MAX(rating)
FROM Movies NATURAL JOIN Rating NATURAL JOIN Temps
WHERE annee IS NOT NULL
GROUP BY GROUPING SETS (annee);
