#include <iostream>
#include <exception>
#include <vector>
#include <map>
using namespace std;

class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(string msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(string msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(string msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class Person {
public:
    int ID;
    string name;
    Person(int id, string n) : ID(id), name(n) {}
};

class Course {
public:
    string code;
    int capacity;
    vector<int> enrolledIDs;

    Course(string c, int cap) : code(c), capacity(cap) {}

    void enroll(int studentID) {
        if (enrolledIDs.size() >= capacity)
            throw EnrollmentException("Course is full.");
        enrolledIDs.push_back(studentID);
    }
};

class GradeBook {
    map<int, float> grades;
public:
    void addGrade(int studentID, float grade) {
        if (grade < 0 || grade > 100)
            throw GradeException("Invalid grade.");
        grades[studentID] = grade;
    }
};

class UniversitySystem {
    map<string, Course> courses;
public:
    void addCourse(string code, int capacity) {
        courses[code] = Course(code, capacity);
    }

    void enrollStudent(string courseCode, int studentID) {
        if (courses.find(courseCode) == courses.end())
            throw EnrollmentException("Course not found.");
        courses[courseCode].enroll(studentID);
    }

    void simulate() {
        try {
            addCourse("CS101", 1);
            enrollStudent("CS101", 1);
            enrollStudent("CS101", 2);
        } catch (UniversitySystemException& ex) {
            cout << "Caught Exception: " << ex.what() << endl;
        }
    }
};

int main() {
    UniversitySystem sys;
    sys.simulate();
    return 0;
}
