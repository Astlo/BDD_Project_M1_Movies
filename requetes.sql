--@requetes.sql

--GROUP BY : la moyenne des notes utilisateurs pour le tag ?
SELECT AVG(rating), userTag
FROM Rating
