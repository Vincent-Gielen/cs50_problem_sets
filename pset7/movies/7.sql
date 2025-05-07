SELECT movies.title, ratings.rating
FROM movies
JOIN ratings On movies.id = ratings.movie_id
WHERE ratings.rating IS NOT NULL AND movies.year = 2010
ORDER BY ratings.rating DESC, movies.title;
