SELECT title
FROM movies
WHERE id IN
(SELECT movie_id
FROM stars
JOIN people ON stars.person_id = people.id
WHERE people.name = "Helena Bonham Carter")
AND id IN
(SELECT movie_id
FROM stars
JOIN people ON stars.person_id = people.id
WHERE people.name = "Johnny Depp");