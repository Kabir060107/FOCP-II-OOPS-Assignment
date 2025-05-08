#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Person {
private:
    string name, contactInfo;
    int age;
    int ID;
public:
    Person() : name(""), contactInfo(""), age(0), ID(0) {}
    Person(string n, int a, int id, string contact) {
        setName(n);
        setAge(a);
        ID = id;
        contactInfo = contact;
    }
    void setName(string n) { if (!n.empty()) name = n; }
    void setAge(int a) { if (a > 0 && a < 120) age = a; }
    string getName() { return name; }
    int getAge() { return age; }
    int getID() { return ID; }
    string getContactInfo() { return contactInfo; }

    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << ID << ", Contact: " << contactInfo << endl;
    }

    virtual double calculatePayment() {
        return 0.0;
    }
};

class Student : public Person {
private:
    string enrollmentDate, program;
    float GPA;
public:
    Student(string n, int a, int id, string contact, string enroll, string prog, float g)
        : Person(n, a, id, contact), enrollmentDate(enroll), program(prog), GPA(0.0f) {
        setGPA(g);
    }

    void setGPA(float g) { if (g >= 0.0 && g <= 4.0) GPA = g; }
    float getGPA() { return GPA; }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Program: " << program << ", Enrollment Date: " << enrollmentDate << ", GPA: " << GPA << endl;
    }

    double calculatePayment() override {
        return 1000 * GPA;
    }
};

class Professor : public Person {
private:
    string department, specialization, hireDate;
public:
    Professor(string n, int a, int id, string contact, string dept, string spec, string hire)
        : Person(n, a, id, contact), department(dept), specialization(spec), hireDate(hire) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Department: " << department << ", Specialization: " << specialization << ", Hire Date: " << hireDate << endl;
    }

    double calculatePayment() override {
        return 5000.0;
    }
};

class Course {
private:
    string code, title, description;
    int credits;
public:
    Course(string c, string t, string d, int cr) : code(c), title(t), description(d), credits(0) {
        setCredits(cr);
    }

    void setCredits(int c) { if (c > 0) credits = c; }

    void display() {
        cout << "Course Code: " << code << ", Title: " << title << ", Credits: " << credits << ", Description: " << description << endl;
    }
};

class Department {
private:
    string name, location;
    double budget;
public:
    Department(string n, string loc, double b) : name(n), location(loc), budget(b) {}

    void display() {
        cout << "Department: " << name << ", Location: " << location << ", Budget: $" << budget << endl;
    }
};

class GradeBook {
private:
    map<int, float> grades;
public:
    void addGrade(int studentID, float grade) {
        grades[studentID] = grade;
    }

    float calculateAverageGrade() {
        float sum = 0;
        for (auto& g : grades) sum += g.second;
        return grades.empty() ? 0 : sum / grades.size();
    }

    float getHighestGrade() {
        float max = 0;
        for (auto& g : grades) if (g.second > max) max = g.second;
        return max;
    }

    vector<int> getFailingStudents() {
        vector<int> fail;
        for (auto& g : grades) if (g.second < 50) fail.push_back(g.first);
        return fail;
    }
};

class EnrollmentManager {
private:
    map<int, vector<string>> enrollments;
public:
    void enrollStudent(int studentID, string courseCode) {
        enrollments[studentID].push_back(courseCode);
    }

    void dropStudent(int studentID, string courseCode) {
        auto& courses = enrollments[studentID];
        courses.erase(remove(courses.begin(), courses.end(), courseCode), courses.end());
    }

    int getEnrollmentCount(string courseCode) {
        int count = 0;
        for (auto& e : enrollments)
            for (auto& course : e.second)
                if (course == courseCode) count++;
        return count;
    }
};

int main() {
    Student s1("Alice", 20, 101, "alice@mail.com", "2023-08-15", "BSc CS", 3.6);
    Student s2("Bob", 21, 102, "bob@mail.com", "2023-08-15", "BSc CS", 3.2);
    Professor p1("Dr. Smith", 45, 201, "smith@uni.edu", "CS", "AI", "2010-07-01");
    Professor p2("Dr. Jane", 50, 202, "jane@uni.edu", "Math", "Algebra", "2005-01-01");

    Course c1("CS101", "Intro to Programming", "Basics of C++", 3);
    Department d1("Computer Science", "Building A", 500000);

    s1.displayDetails();
    s2.displayDetails();
    p1.displayDetails();
    p2.displayDetails();

    c1.display();
    d1.display();

    GradeBook gb;
    gb.addGrade(101, 85.0);
    gb.addGrade(102, 45.0);

    cout << "Average Grade: " << gb.calculateAverageGrade() << endl;
    cout << "Highest Grade: " << gb.getHighestGrade() << endl;

    vector<int> failing = gb.getFailingStudents();
    for (int id : failing) cout << "Failing student ID: " << id << endl;

    EnrollmentManager em;
    em.enrollStudent(101, "CS101");
    em.enrollStudent(102, "CS101");
    cout << "Enrollment in CS101: " << em.getEnrollmentCount("CS101") << endl;

    vector<Person*> people;
    people.push_back(&s1);
    people.push_back(&s2);
    people.push_back(&p1);
    people.push_back(&p2);

    for (Person* p : people) {
        p->displayDetails();
        cout << "Payment: $" << p->calculatePayment() << endl;
    }

    return 0;
}
