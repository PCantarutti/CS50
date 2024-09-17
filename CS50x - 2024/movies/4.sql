SELECT COUNT(movies.title) AS quantity FROM movies INNER JOIN ratings on ratings.movie_id = movies.id WHERE ratings.rating = 10.0;

--SELECT COUNT(title) AS quantity FROM movies WHERE id IN
--(SELECT movie_id FROM ratings WHERE rating = 10.0);
