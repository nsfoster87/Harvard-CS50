SELECT name
FROM people
WHERE id IN
--Select person_ids for people in Kevin Bacon movies
(SELECT person_id
FROM stars
WHERE movie_id IN
--All the movie_ids for movies Kevin Bacon was in
(SELECT movie_id
FROM stars
JOIN people ON people.id = stars.person_id
WHERE people.name = "Kevin Bacon"
AND people.birth = 1958))
AND id NOT IN
(SELECT id FROM people
WHERE name = "Kevin Bacon" AND birth = 1958);