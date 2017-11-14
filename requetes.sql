





























--@requetes.sql

--GROUP BY : la moyenne des notes utilisateurs pour le tag ?
SELECT AVG(rating) as moyenne, userTag
FROM (Rating JOIN Tagging ON (Rating.userId = Tagging.userId and Rating.movieId = Tagging.movieId)) NATURAL JOIN Movies
GROUP BY (userTag)
ORDER BY (moyenne);

--GROUP BY CUBE : le nombre de films sortis en dvd par année, si des films n'ont pas de date de sortie on connaitra le nombre de fims qui ne sont pas sortis en dvd
SELECT movieDVD, count(movieId)
FROM Movies
GROUP BY CUBE (movieDVD,movieCountry);