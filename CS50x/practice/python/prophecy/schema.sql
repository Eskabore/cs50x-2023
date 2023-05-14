DROP TABLE IF EXISTS students;
DROP TABLE IF EXISTS houses;
DROP TABLE IF EXISTS house_assignments;


CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    house TEXT,
    head TEXT,
    PRIMARY KEY(house)
);

CREATE TABLE house_assignments (
    id INTEGER,
    house TEXT,
    FOREIGN KEY (id) REFERENCES students(id),
    FOREIGN KEY (house) REFERENCES houses(house)
);