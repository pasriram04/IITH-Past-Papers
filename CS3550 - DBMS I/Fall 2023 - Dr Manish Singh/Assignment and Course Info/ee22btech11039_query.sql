/* Question 1a */
SELECT instructor.name, instructor.id, COUNT(DISTINCT teaches.course_id) as no_of_courses 
FROM instructor, teaches 
WHERE instructor.id = teaches.id 
GROUP BY instructor.id 
ORDER BY no_of_courses DESC 
LIMIT 3;

/* Question 1b */
SELECT instructor.name, instructor.id, COUNT(DISTINCT teaches.course_id) as no_of_courses 
FROM instructor, teaches 
WHERE instructor.id = teaches.id and instructor.dept_name = 'Statistics'
GROUP BY instructor.id 
ORDER BY no_of_courses DESC 
LIMIT 3; 

/* Question 2 */
SELECT 
    instructor.name, 
    instructor.dept_name, 
    teaches.course_id, 
    course.title AS course_title, 
    (
        SELECT(COUNT(takes.course_id)) 
        FROM takes 
        WHERE takes.course_ID = teaches.course_id AND takes.year = teaches.year AND takes.semester = teaches.semester AND takes.sec_id = section.sec_id
    ) AS total_enrollment, teaches.semester, teaches.year, section.sec_id 
FROM 
    instructor, 
    teaches, 
    course, 
    section 
WHERE 
    salary = (SELECT MAX(salary) FROM instructor) AND teaches.id = instructor.id AND course.course_id = teaches.course_id AND course.course_id = section.course_id 
ORDER BY 
    course.course_id ASC, teaches.semester ASC, teaches.year ASC;

/* Question 3 */
SELECT 
    course.course_id, 
    course.title AS course_title, 
    course.dept_name AS course_dept_name, 
    instructor.name AS instructor_name, 
    section.sec_id, 
    section.semester, 
    section.year, 
    section.time_slot_id, 
    COUNT(takes.id) AS no_of_students 
FROM 
    course 
    NATURAL JOIN section 
    NATURAL JOIN teaches 
    JOIN instructor ON instructor.id = teaches.id 
    JOIN takes ON takes.course_id = section.course_id AND takes.sec_id = section.sec_id AND takes.semester = section.semester AND takes.year = section.year 
WHERE 
    course.course_id = '362' 
GROUP BY 
    course.course_id, course.title, course.dept_name, instructor.name, section.sec_id, section.semester, section.year, section.time_slot_id 
ORDER BY section.year DESC;

/* Question 4 */
SELECT 
    COUNT(*) AS out_of_department_registrations
FROM 
    takes 
    NATURAL JOIN course
    JOIN student ON student.id = takes.id 
WHERE 
    course.course_id = '319' 
    AND takes.year = 2003 
    AND student.dept_name <> course.dept_name;

/* Question 5 */
SELECT 
    takes.id AS student_id, 
    student.name,  
    student.dept_name, 
    SUM(credits) AS total_credits 
FROM 
    takes 
    NATURAL JOIN course 
    JOIN student ON takes.id = student.id 
GROUP BY 
    takes.id, student.name, student.dept_name 
ORDER BY 
    total_credits DESC, 
    student.name 
LIMIT 3;

/* Question 6 */
SELECT 
    course.course_id, course.title 
FROM 
    course
    NATURAL LEFT OUTER JOIN 
        (
            SELECT 
                DISTINCT section.course_id 
            FROM 
                section
            WHERE 
                section.year IN (2003, 2004)
        ) AS courses_2003_2004
WHERE 
    courses_2003_2004.course_id IS NULL
ORDER BY 
    course.course_id ASC;


/* Question 7 */
WITH firstoffer AS 
    (
    SELECT
        section.course_id,
        MIN(year) AS first_time_offered_year
    FROM
        section
    GROUP BY
        section.course_id
    )

SELECT
    course.course_id,
    course.title,
    instructor.name AS instructor,
    firstoffer.first_time_offered_year
FROM
    firstoffer
    JOIN section ON firstoffer.course_id = section.course_id AND firstoffer.first_time_offered_year = section.year
    JOIN course ON firstoffer.course_id = course.course_id
    JOIN teaches ON section.course_id = teaches.course_id AND section.sec_id = teaches.sec_id
    JOIN instructor ON teaches.id = instructor.id
WHERE
    firstoffer.first_time_offered_year = 
    (
        SELECT 
            MAX(first_time_offered_year) 
        FROM 
            firstoffer
    )
ORDER BY
    course.course_id ASC;

/* Question 8 */
SELECT
    course_id, title
FROM
    course
WHERE
    title LIKE '_______________%'
    AND LOWER(title) LIKE '%sys%'
ORDER BY
    course_id ASC;

/* Question 9 */
SELECT
    dept_name, AVG(salary) AS average_salary
FROM
    instructor
    NATURAL JOIN department
GROUP BY
    dept_name
ORDER BY
    average_salary DESC
LIMIT 1;

/* Question 10 */
SELECT
    instructor.id, instructor.name, instructor.dept_name
FROM
    instructor
    LEFT OUTER JOIN teaches ON teaches.id = instructor.id AND teaches.year = 2003
GROUP BY
    instructor.id, instructor.name, instructor.dept_name
HAVING
    COUNT(teaches.course_id) <= 1
ORDER BY
    instructor.id ASC;