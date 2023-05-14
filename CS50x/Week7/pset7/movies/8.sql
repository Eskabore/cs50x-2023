-- List the names of all people who starred in Toy Story
SELECT name FROm people JOIN stars ON people.id = stars.person_id WHERE movie_id = (SELECT id FROM movies WHERE title = "Toy Story");