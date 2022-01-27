SELECT name FROM
(SELECT DISTINCT person_id, name
FROM ((movies
JOIN stars ON stars.movie_id = movies.id)
JOIN people ON stars.person_id = people.id)
WHERE year = 2004
ORDER BY people.birth);