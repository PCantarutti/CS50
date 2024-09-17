SELECT AVG(rating) as average FROM ratings WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2012);
--SELECT AVG(ratings.rating) AS avarege FROM ratings INNER JOIN movies on movies.id = ratings.movie_id;
