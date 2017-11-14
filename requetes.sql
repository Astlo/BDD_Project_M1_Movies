--@requetes.sql

--GROUP BY : la moyenne des notes utilisateurs pour le tag ?
SELECT AVG(rating) as moyenne, userTag
FROM (Rating JOIN Tagging ON (Rating.userId = Tagging.userId and Rating.movieId = Tagging.movieId)) NATURAL JOIN Movies
GROUP BY (userTag)
ORDER BY (moyenne)
LIMIT 10;
