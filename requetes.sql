--@requetes.sql

--GROUP BY : la moyenne des notes utilisateurs pour le tag
SELECT AVG(rating) as moyenne, userTag
FROM (Rating JOIN Tagging ON (Rating.userId = Tagging.userId and Rating.movieId = Tagging.movieId)) NATURAL JOIN Movies
GROUP BY (userTag)
ORDER BY (moyenne);

--GROUP BY CUBE : le nombre de films sortis en dvd par année, si des films n'ont pas de date de sortie on connaitra le nombre de fims qui ne sont pas sortis en dvd
SELECT YEAR(movieDVD) as anneeDVD, movieCountry, count(movieId)
FROM Movies
GROUP BY CUBE (anneeDVD, movieCountry);

-- Somme de l'argent du box office de tous les films pour chaque année
SELECT movieYear AS annee, SUM(movieBoxOffice) AS boxOffice
FROM Movies
WHERE movieBoxOffice IS NOT NULL
GROUP BY GROUPING SETS (movieYear);


-- Les 10 films ayant reçus les meilleurs ratings, par rapport à leur rang dans le box office
SELECT movieTitle, MAX(avg_rating), RANK() over (ORDER BY movieBoxOffice DESC) AS rangBoxOffice
FROM ( SELECT movieId, movieTitle, AVG(rating) AS avg_rating, movieBoxOffice
      FROM Movies NATURAL JOIN Rating
      GROUP BY movieId
  )
WHERE rownum <= 10
ORDER BY rating DESC;

--Les 20 meilleurs succès au box office triés par les producteurs (partition by)
SELECT movieProduction, movieTitle, movieYear, movieBoxOffice, rank() OVER (PARTITION BY movieProduction ORDER BY movieBoxOffice DESC) AS rank
FROM Movies NATURAL JOIN Rating
WHERE rownum <= 20;

--Le film ayant reçu la meilleure notation pour chaque année
SELECT movieTitle, movieYear AS annee, MAX(avg_rating)
FROM ( SELECT movieId, movieTitle, movieYear, AVG(rating) AS avg_rating
      FROM Movies NATURAL JOIN Rating
      GROUP BY movieId
  )
WHERE movieYear IS NOT NULL
GROUP BY GROUPING SETS (movieYear);
