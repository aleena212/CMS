# CMS
This Campus Management System is a C++ console application that enables the management of student and course information, as well as student enrollments in courses. The system is designed to handle administrative tasks, such as adding, deleting, and updating student and course records, as well as managing enrollments.
Features:
1. Student Management
Add Student: Allows the addition of student records by entering the student's name, roll number, and department.
Delete Student: Enables the deletion of a student by searching for the student's name.
Update Student: Allows updating student records by entering their roll number and changing the name or department.
Search Student: Provides functionality to search for a student by their roll number and displays their details.
2. Course Management
Add Course: Enables the addition of courses by specifying the course title and code.
Delete Course: Allows deletion of a course by searching for the course title.
Update Course: Facilitates updating the course title by searching with the course code.
Search Course: Provides functionality to search for a course by its code and displays the course details.
3. Enrollment Management
Enroll Student: Enables the enrollment of students in courses by entering the student's name, roll number, and course title.
View Enrollments: Displays all student enrollments along with their course details.
File Handling:
student.txt: Stores student data, including name, roll number, and department.
course.txt: Stores course data, including course title and course code.
enrolment.txt: Stores enrollment data, including student name, roll number, and course title.

Additional Features:
Console Sleep (Loading Screen): A loading screen appears before the main menus.
Error Handling: Checks if files are successfully opened before performing any read/write operations.
