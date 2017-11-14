





























--@requetes.sql

--GROUP BY : la moyenne des notes utilisateurs pour le tag ?
SELECT AVG(rating) as moyenne, userTag
FROM (Rating JOIN Tagging ON (Rating.userId = Tagging.userId and Rating.movieId = Tagging.movieId)) NATURAL JOIN Movies
GROUP BY (userTag)
ORDER BY (moyenne);

<<<<<<< HEAD
--GROUP BY CUBE : le nombre de films sortis en dvd par année, si des films n'ont pas de date de sortie on connaitra le nombre de fims qui ne sont pas sortis en dvd
SELECT movieDVD, count(movieId)
FROM Movies
GROUP BY CUBE (movieDVD,movieCountry);
=======
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
>>>>>>> 0fab546a2db5d45465e781c1b35e4c4b7e8aaf58
