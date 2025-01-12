#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <sstream> 

using namespace std;

// Student Class
class Student {
private:
    int rollNumber;
    string name;
    string className;
    float feesPaid;
    int attendance;
    map<string, float> grades; // Subject and grade

public:
    void addStudent();
    void displayStudent() const;
    void displayPerformance() const;
    void markAttendance();
    void addGrade(const string& subject, float grade);
    int getRollNumber() const;
    const string& getName() const; 
    void saveToFile() const;
    static void loadFromFile(vector<Student>& students);
};

// Teacher Class
class Teacher {
private:
    int teacherID;
    string name;
    string schedule;

public:
    void addTeacher();
    void displayTeacher() const;
    void assignClassSchedule(const string& schedule);
    int getTeacherID() const;
    const string& getName() const
    void saveToFile() const;
    static void loadFromFile(vector<Teacher>& teachers);
};

// Report Class
class Report {
public:
    static void generateAdminReport(const vector<Student>& students, const vector<Teacher>& teachers);
    static void generateStudentReport(const vector<Student>& students, int rollNo);
};

// Input validation for menu choice
int getValidatedChoice() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 19) {
            cout << "Invalid choice. Please enter a number between 1 and 19: ";
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            break;
        }
    }
    return choice;
}

// Student Class Implementation
void Student::addStudent() {
    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Class Name: ";
    getline(cin, className);
    cout << "Enter Fees Paid: ";
    cin >> feesPaid;
    attendance = 0;
}

void Student::displayStudent() const {
    cout << "Roll Number: " << rollNumber << "\n"
         << "Name: " << name << "\n"
         << "Class: " << className << "\n"
         << "Fees Paid: " << feesPaid << "\n"
         << "Attendance: " << attendance << "%\n";
}

void Student::displayPerformance() const {
    cout << "Performance Report for Roll Number: " << rollNumber << "\n";
    for (map<string, float>::const_iterator it = grades.begin(); it != grades.end(); ++it) {
        cout << "Subject: " << it->first << " - Grade: " << it->second << "\n";
    }
}

void Student::markAttendance() {
    cout << "Enter attendance percentage: ";
    cin >> attendance;
}

void Student::addGrade(const string& subject, float grade) {
    grades[subject] = grade;
}

int Student::getRollNumber() const {
    return rollNumber;
}

const string& Student::getName() const {
    return name;
}

void Student::saveToFile() const {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << rollNumber << "\n"
             << name << "\n"
             << className << "\n"
             << feesPaid << "\n"
             << attendance << "\n";
        for (map<string, float>::const_iterator it = grades.begin(); it != grades.end(); ++it) {
            file << it->first << ":" << it->second << "\n";
        }
        file << "END_GRADES\n";
        file.close();
    } else {
        cout << "\n";
    }
}

void Student::loadFromFile(vector<Student>& students) {
    ifstream file("students.txt");
    if (file.is_open()) {
        while (true) {
            Student temp;
            file >> temp.rollNumber;
            file.ignore();
            getline(file, temp.name);
            getline(file, temp.className);
            file >> temp.feesPaid >> temp.attendance;
            file.ignore();
            string line;
            while (getline(file, line) && line != "END_GRADES") {
                size_t pos = line.find(':');
                if (pos != string::npos) {
                    string subject = line.substr(0, pos);
                    string gradeStr = line.substr(pos + 1);
                    stringstream ss(gradeStr);
                    float grade;
                    ss >> grade;
                    temp.grades[subject] = grade;
                }
            }
            if (file) students.push_back(temp);
            if (file.eof()) break;
        }
        file.close();
    } else {
        cout << "\n";
    }
}

// Teacher Class Implementation
void Teacher::addTeacher() {
    cout << "Enter Teacher ID: ";
    cin >> teacherID;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    schedule = "Not Assigned";
}

void Teacher::displayTeacher() const {
    cout << "Teacher ID: " << teacherID << "\n"
         << "Name: " << name << "\n"
         << "Schedule: " << schedule << "\n";
}

void Teacher::assignClassSchedule(const string& schedule) {
    this->schedule = schedule;
}

int Teacher::getTeacherID() const {
    return teacherID;
}

const string& Teacher::getName() const {
    return name;
}

void Teacher::saveToFile() const {
    ofstream file("teachers.txt", ios::app);
    if (file.is_open()) {
        file << teacherID << "\n"
             << name << "\n"
             << schedule << "\n";
        file.close();
    } else {
        cout << "\n";
    }
}

void Teacher::loadFromFile(vector<Teacher>& teachers) {
    ifstream file("teachers.txt");
    if (file.is_open()) {
        while (true) {
            Teacher temp;
            file >> temp.teacherID;
            file.ignore();
            getline(file, temp.name);
            getline(file, temp.schedule);
            if (file) teachers.push_back(temp);
            if (file.eof()) break;
        }
        file.close();
    } else {
        cout << \n";
    }
}

// Report Class Implementation
void Report::generateAdminReport(const vector<Student>& students, const vector<Teacher>& teachers) {
    cout << "\n--- Admin Report ---\n";
    cout << "Total Students: " << students.size() << "\n";
    cout << "Total Teachers: " << teachers.size() << "\n";
}

void Report::generateStudentReport(const vector<Student>& students, int rollNo) {
    cout << "<--- Student Report --->\n";
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getRollNumber() == rollNo) {
            students[i].displayPerformance();
            return;
        }
    }
    cout << "No student found with Roll Number " << rollNo << ".\n";
}

// Search Functions
void searchStudentByName(const vector<Student>& students) {
    string name;
    cout << "Enter the name of the student to search: ";
    cin.ignore();
    getline(cin, name);
    bool found = false;
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].getName() == name) {
            students[i].displayStudent();
            found = true;
        }
    }
    if (!found) {
        cout << "No student found with the name " << name << ".\n";
    }
}

void searchTeacherByName(const vector<Teacher>& teachers) {
    string name;
    cout << "Enter the name of the teacher to search: ";
    cin.ignore();
    getline(cin, name);
    bool found = false;
    for (size_t i = 0; i < teachers.size(); ++i) {
        if (teachers[i].getName() == name) {
            teachers[i].displayTeacher();
            found = true;
        }
    }
    if (!found) {
        cout << "No teacher found with the name " << name << ".\n";
    }
}

// Main Function
int main() {
    vector<Student> students;
    vector<Teacher> teachers;

    Student::loadFromFile(students);
    Teacher::loadFromFile(teachers);

    int choice;
    do {
    	cout << "<:----------------------------------------:>\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Mark Student Attendance\n";
        cout << "4. Add Grade to Student\n";
        cout << "5. Add Teacher\n";
        cout << "6. View All Teachers\n";
        cout << "7. Assign Class Schedule to Teacher\n";
        cout << "8. Generate Admin Report\n";
        cout << "9. Generate Student Report\n";
        cout << "10. Search Student by Name\n";
        cout << "11. Search Teacher by Name\n";
        cout << "12. Exit\n";
        cout << "<:----------------------------------------:>\n";
        cout << "\n";
        cout << "Enter your choice: ";
        choice = getValidatedChoice();

        if (choice == 1) {
            Student s;
            s.addStudent();
            students.push_back(s);
            s.saveToFile();
        } else if (choice == 2) {
            for (size_t i = 0; i < students.size(); ++i) {
                students[i].displayStudent();
            }
        } else if (choice == 3) {
            int rollNo;
            cout << "Enter Roll Number: ";
            cin >> rollNo;
            for (size_t i = 0; i < students.size(); ++i) {
                if (students[i].getRollNumber() == rollNo) {
                    students[i].markAttendance();
                }
            }
        } else if (choice == 4) {
            int rollNo;
            string subject;
            float grade;
            cout << "Enter Roll Number: ";
            cin >> rollNo;
            cout << "Enter Subject: ";
            cin.ignore();
            getline(cin, subject);
            cout << "Enter Grade: ";
            cin >> grade;
            for (size_t i = 0; i < students.size(); ++i) {
                if (students[i].getRollNumber() == rollNo) {
                    students[i].addGrade(subject, grade);
                }
            }
        } else if (choice == 5) {
            Teacher t;
            t.addTeacher();
            teachers.push_back(t);
            t.saveToFile();
        } else if (choice == 6) {
            for (size_t i = 0; i < teachers.size(); ++i) {
                teachers[i].displayTeacher();
            }
        } else if (choice == 7) {
            int teacherID;
            string schedule;
            cout << "Enter Teacher ID: ";
            cin >> teacherID;
            cout << "Enter Schedule: ";
            cin.ignore();
            getline(cin, schedule);
            for (size_t i = 0; i < teachers.size(); ++i) {
                if (teachers[i].getTeacherID() == teacherID) {
                    teachers[i].assignClassSchedule(schedule);
                }
            }
        } else if (choice == 8) {
            Report::generateAdminReport(students, teachers);
        } else if (choice == 9) {
            int rollNo;
            cout << "Enter Roll Number: ";
            cin >> rollNo;
            Report::generateStudentReport(students, rollNo);
        } else if (choice == 10) {
            searchStudentByName(students);
        } else if (choice == 11) {
            searchTeacherByName(teachers);
        }
    } while (choice != 12);

    return 0;
}
