CREATE TABLE students (
    id INTEGER NOT NULL,
    name TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    house TEXT UNIQUE,
    head TEXT UNIQUE,
    PRIMARY KEY(house)
);

CREATE TABLE assignments (
    student_id INTEGER NOT NULL,
    house_name TEXT,
    head_name TEXT,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_name) REFERENCES houses(house)
);