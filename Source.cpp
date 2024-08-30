#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <iomanip>
using namespace std;

// Function declarations
void management();
void studentmanagement();
void addstudent();
void deletestudent();
void updatestudent();
void searchstudent();
void coursemanagement();
void addcourse();
void deletecourse();
void updatecourse();
void searchcourse();
void enrolmentmanagement();
void enrolstudent();
void viewenrolment();
void console_sleep();

/////////////////////////////   MAIN MENU   //////////////////////////
void management() {
    int choice;
    while (true) {
        cout << "\n========================================================" << endl;
        cout << "********Welcome to Campus Management System********" << endl;
        cout << "=========================================================" << endl;
        cout << "\n";
        cout << "1.Student Management" << endl;
        cout << "2.Course Management" << endl;
        cout << "3.Enrollment Management" << endl;
        cout << "4.Exit" << endl;
        cout << "\n==============================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            studentmanagement();
            break;
        case 2:
            coursemanagement();
            break;
        case 3:
            enrolmentmanagement();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again!" << endl;
            break;
        }
    }
    console_sleep();
}

////////////////////////////  STUDENT MANAGEMENT  ///////////////////
void studentmanagement() {
    int choice;
    cout << "\n================================================" << endl;
    cout << "*****Student Management System Menu*****" << endl;
    cout << "================================================" << endl;
    cout << "1.Add a student" << endl;
    cout << "2.Delete a student" << endl;
    cout << "3.Update a student" << endl;
    cout << "4.Search student" << endl;
    cout << "5.Back to Management menu" << endl;
    cout << "\n================================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        addstudent();
        break;
    case 2:
        deletestudent();
        break;
    case 3:
        updatestudent();
        break;
    case 4:
        searchstudent();
        break;
    case 5:
        return;
    default:
        cout << "Invalid choice. Please try again!" << endl;
        break;
    }
    console_sleep();
}

////////////// ADD STUDENT //////////////////////
void addstudent() {
    int num_stds;
    cout << "How many students do you want to add: ";
    cin >> num_stds;
    cin.ignore();

    ofstream outFile("student.txt", ios::app);  // open file 
    if (outFile.is_open()) {

        for (int i = 0; i < num_stds; i++) {
            string name, department;
            int rollnumber;
            cout << "Please enter student " << i + 1 << " name you want to add: ";
            getline(cin, name);
            cout << "Please enter student " << i + 1 << " roll number: ";
            cin >> rollnumber;
            cin.ignore();
            cout << "Please enter student " << i + 1 << " department: ";
            getline(cin, department);

            outFile << name << endl << rollnumber << endl << department << endl;
            cout << "Student added successfully." << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file!" << endl;
    }
    studentmanagement();
    console_sleep();
}

////////////////////////DELETE STUDENT//////////////////////////
void deletestudent() {
    int num_stds;
    cout << "How many students do you want to delete: ";
    cin >> num_stds;
    cin.ignore();

    for (int i = 0; i < num_stds; i++) {
        string name, line;
        cout << "Please enter the name of student " << i + 1 << " you want to delete: ";
        getline(cin, name);

        ifstream inFile("student.txt");
        ofstream tempFile("temp.txt");

        bool found = false;
        if (inFile.is_open() && tempFile.is_open()) {
            while (getline(inFile, line)) {
                string studentName;
                int rollnumber;
                string department;

                studentName = line;
                getline(inFile, line);
                rollnumber = stoi(line);
                getline(inFile, department);

                if (studentName == name) {
                    found = true;
                    continue;
                }
                else {
                    tempFile << studentName << endl << rollnumber << endl << department << endl;
                }
            }
            inFile.close();
            tempFile.close();

            remove("student.txt");
            rename("temp.txt", "student.txt");

            if (found) {
                cout << "Student deleted successfully." << endl;
            }
            else {
                cout << "Student not found." << endl;
            }
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }

    studentmanagement();
    console_sleep();
}

///////////////////UPDATE STUDENT/////////////////////
void updatestudent() {
    int num_stds;
    cout << "How many students do you want to update: ";
    cin >> num_stds;
    cin.ignore();

    for (int i = 0; i < num_stds; i++) {
        int rollnumber;
        string name, newName, newDepartment, line;
        bool studentFound = false;

        cout << "Please enter roll number of the student " << i + 1 << " to update: ";
        cin >> rollnumber;
        cin.ignore();

        ifstream inFile("student.txt");
        ofstream tempFile("temp.txt");

        if (inFile.is_open() && tempFile.is_open()) {
            while (getline(inFile, line)) {
                string studentName;
                string department;

                studentName = line;
                getline(inFile, line);
                int currentRollNumber = stoi(line);
                getline(inFile, department);

                if (currentRollNumber == rollnumber) {
                    studentFound = true;

                    cout << "Please enter new name (leave empty to keep current): ";
                    getline(cin, newName);
                    cout << "Please enter new department (leave empty to keep current): ";
                    getline(cin, newDepartment);

                    if (!newName.empty()) {
                        studentName = newName;
                    }
                    if (!newDepartment.empty()) {
                        department = newDepartment;
                    }

                    tempFile << studentName << endl << rollnumber << endl << department << endl;
                }
                else {
                    tempFile << studentName << endl << currentRollNumber << endl << department << endl;
                }
            }
            inFile.close();
            tempFile.close();

            remove("student.txt");
            rename("temp.txt", "student.txt");

            if (studentFound) {
                cout << "Student updated successfully." << endl;
            }
            else {
                cout << "Student not found." << endl;
            }
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }

    studentmanagement();
    console_sleep();
}

///////////////////SEARCH STUDENT///////////////////////////
void searchstudent() {
    int rollnumber;
    cout << "Please enter roll number of a student: ";
    cin >> rollnumber;
    cin.ignore();

    ifstream inFile("student.txt");
    string line;
    bool studentFound = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            string studentName;
            string department;
            int fileRollNumber;

            studentName = line;
            getline(inFile, line);
            fileRollNumber = stoi(line);
            getline(inFile, department);

            if (fileRollNumber == rollnumber) {
                studentFound = true;
                cout << "Student found" << endl;
                cout << "Name: " << studentName << endl;
                cout << "Roll Number: " << fileRollNumber << endl;
                cout << "Department: " << department << endl;
                break;
            }
        }
        inFile.close();

        if (!studentFound) {
            cout << "No student found with roll number " << rollnumber << "." << endl;
        }
    }
    else {
        cout << "Unable to open file." << endl;
    }

    studentmanagement();
    console_sleep();
}

////////////////////////////// COURSE MANAGEMENT ///////////////////////
void coursemanagement() {
    int choice;
    cout << "\n=============================================" << endl;
    cout << "*****Course Management Menu*****" << endl;
    cout << "=============================================" << endl;
    cout << "1.Add course" << endl;
    cout << "2.Delete course" << endl;
    cout << "3.Update course" << endl;
    cout << "4.Search course " << endl;
    cout << "5.Back to Management menu" << endl;
    cout << "\n=======================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        addcourse();
        break;
    case 2:
        deletecourse();
        break;
    case 3:
        updatecourse();
        break;
    case 4:
        searchcourse();
        break;
    case 5:
        return;
    default:
        cout << "Invalid choice. Please try again!" << endl;
        break;
    }
    console_sleep();
}

///////////// ADD COURSE ///////////
void addcourse() {
    int num_course;
    cout << "How many courses do you want to add: ";
    cin >> num_course;
    cin.ignore();
    //append to file
    ofstream outFile("course.txt", ios::app);
    if (outFile.is_open()) {
        for (int i = 0; i < num_course; i++) {
            string coursetitle;
            int coursecode;
            cout << "Please enter course " << i + 1 << " title: ";
            getline(cin, coursetitle);
            cout << "Please enter course " << i + 1 << " code: ";
            cin >> coursecode;
            cin.ignore();
            outFile << coursetitle << " " << coursecode << endl;
            cout << "Course added successfully." << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file!" << endl;
    }
    coursemanagement();
    console_sleep();
}

/////////// DELETE COURSE  ///////////
void deletecourse() {
    int num_course;
    cout << "How many courses do you want to delete: ";
    cin >> num_course;
    cin.ignore();

    for (int i = 0; i < num_course; i++) {
        string coursetitle, line;
        cout << "Please enter the course " << i + 1 << " title you want to delete: ";
        getline(cin, coursetitle);
        cin.ignore();

        ifstream inFile("course.txt");
        ofstream tempFile("temp.txt");

        bool found = false;
        if (inFile.is_open() && tempFile.is_open()) {
            while (getline(inFile, line)) {
                if (line.find(coursetitle + " ") != string::npos) { // checking if the course title is found in file
                    found = true;
                }
                else {
                    tempFile << line << endl;
                }
            }
            inFile.close();
            tempFile.close();

            remove("course.txt");
            rename("temp.txt", "course.txt");
            if (found) {
                cout << "Course deleted successfully." << endl;
            }
            else {
                cout << "Course not found." << endl;
            }
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }
    coursemanagement();
    console_sleep();
}

//////////  UPDATE COURSE  //////////
void updatecourse() {
    int num_course;
    cout << "How many courses do you want to update: ";
    cin >> num_course;
    cin.ignore();

    for (int i = 0; i < num_course; i++) {
        string coursetitle, newcoursetitle, line;
        int coursecode;
        bool courseFound = false;
        cout << "Please enter course " << i + 1 << " code to update: ";
        cin >> coursecode;
        cin.ignore();

        cout << "Please enter new course title: ";
        getline(cin, newcoursetitle);

        ifstream inFile("course.txt");
        ofstream tempFile("temp.txt");

        if (inFile.is_open() && tempFile.is_open()) {
            while (getline(inFile, line)) {
                // read the course title and code from the file
                istringstream iss(line);
                string fileTitle;
                int fileCode;
                iss >> fileTitle >> fileCode;

                if (fileCode == coursecode) {
                    courseFound = true;
                    // write the updated course title and code to the temp file
                    tempFile << newcoursetitle << endl << coursecode << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }
            inFile.close();
            tempFile.close();

            // replace old file with updated file
            remove("course.txt");
            rename("temp.txt", "course.txt");

            if (courseFound) {
                cout << "Course updated successfully." << endl;
            }
            else {
                cout << "Course not found." << endl;
            }
        }
        else {
            cout << "Unable to open file." << endl;
        }
    }
    coursemanagement();
    console_sleep();
}

/////////////////  SEARCH COURSE  //////////////
void searchcourse() {
    int coursecode;
    cout << "PLease enter course code to search: ";
    cin >> coursecode;
    cin.ignore();

    ifstream inFile("course.txt");
    string line;
    bool coursefound = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            istringstream iss(line);
            int filecoursecode;
            string coursetitle;

            // reading course data from file
            iss >> coursetitle >> filecoursecode;

            // check if the entered course code matches the file course code
            if (filecoursecode == coursecode) {
                cout << "Course found:" << endl;
                cout << "Course Code: " << filecoursecode << endl;
                cout << "Course Title: " << coursetitle << endl;
                coursefound = true;
                break;
            }
        }
        inFile.close();

        if (!coursefound) {
            cout << "No course found with course code " << coursecode << "." << endl;
        }
    }
    else {
        cout << "Unable to open file." << endl;
    }

    coursemanagement();
    console_sleep();
}

///////////////////// ENROLLMENT MANAGEMENT /////////////////////
void enrolmentmanagement() {
    int choice;
    cout << "\n==============================================" << endl;
    cout << "*****Enrollment Management Menu*****" << endl;
    cout << "==============================================" << endl;
    cout << "1.Enroll a student in a course" << endl;
    cout << "2.View Enrollments" << endl;
    cout << "3.Back to Management menu" << endl;
    cout << "\n============================================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        enrolstudent();
        break;
    case 2:
        viewenrolment();
        break;
    case 3:
        return;
    default:
        cout << "Invalid choice. Please try again!" << endl;
        break;
    }
    console_sleep();
}

///////////////  ENROLL STUDENT  //////////////////////
void enrolstudent() {
    int num_stds;
    cout << "How many students do you want to enrol: ";
    cin >> num_stds;
    cin.ignore();

    ofstream outFile("enrolment.txt", ios::app);
    if (outFile.is_open()) {
        for (int i = 0; i < num_stds; i++) {
            string studentname, coursetitle;
            int rollnumber;
            cout << "Please enter student " << i + 1 << " name to enroll: ";
            getline(cin, studentname);
            cout << "Please enter student " << i + 1 << " roll number : ";
            cin >> rollnumber;
            cin.ignore();
            cout << "Please enter course title: ";
            getline(cin, coursetitle);

            outFile << studentname << endl << rollnumber << endl << coursetitle << endl;

            cout << "Student enrolled successfully." << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file!" << endl;
    }
    enrolmentmanagement();
    console_sleep();
}
///////////////////VIEW ENROLMENTS//////////////////////
void viewenrolment() {
    ifstream inFile("enrolment.txt");
    string studentname, coursetitle;
    int rollnumber;
    bool enrolmentfound = false;

    if (inFile.is_open()) {
        // read and display each student's details
        while (getline(inFile, studentname)) {
            if (inFile >> rollnumber) {
                inFile.ignore();  // ignore the newline after the roll number

                if (getline(inFile, coursetitle)) {
                    // display the details
                    cout << "Student Name: " << studentname << endl;
                    cout << "Roll Number: " << rollnumber << endl;
                    cout << "Course Title: " << coursetitle << endl;
                    cout << "--------------------------" << endl;

                    enrolmentfound = true;
                }
            }
            else {
                break;
            }
        }
        inFile.close();

        if (!enrolmentfound) {
            cout << "No enrolment found." << endl;
        }
    }
    else {
        cout << "Unable to open file." << endl;
    }

    enrolmentmanagement();
    console_sleep();
}
//////////////////////Loading screen///////////////////
void console_sleep() {
    char z = 219;
    system("cls");
    system("color 04");
    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\tloading";
    for (int i = 0; i <= 40; i++) {
        Sleep(40);
        cout << z;
    }
    system("color 7");
    system("cls");
}
///////////////// Main function/////////////////
int main() {
    management();
    return 0;
}
