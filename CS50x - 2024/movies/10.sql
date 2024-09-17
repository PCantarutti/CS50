SELECT P.name AS nome_diretor FROM people AS P
INNER JOIN directors AS D ON D.person_id = P.id
INNER JOIN ratings AS R ON D.movie_id  = R.movie_id
INNER JOIN movies AS M ON R.movie_id  = M.id
WHERE R.rating >= 9.0;
