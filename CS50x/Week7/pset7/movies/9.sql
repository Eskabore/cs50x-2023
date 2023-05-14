-- List the names of all people who starred in a movie released in 2004, ordered by birth year
SELECT DISTINCT name FROM people JOIN stars ON people.id = stars.person_id WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004) ORDER BY birth ASC;