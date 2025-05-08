#include <iostream>
#include <vector>
using namespace std;

class Person {
protected:
    string name, contact;
    int age, ID;
public:
    Person(string n, int a, int id, string c) : name(n), age(a), ID(id), contact(c) {}
    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << ID << ", Contact: " << contact << endl;
    }
    virtual double calculatePayment() { return 0; }
};

class Student : public Person {
protected:
    string program;
public:
    Student(string n, int a, int id, string c, string prog) : Person(n, a, id, c), program(prog) {}
};

class UndergraduateStudent : public Student {
    string major, minor, graduationDate;
public:
    UndergraduateStudent(string n, int a, int id, string c, string prog, string mj, string mn, string grad)
        : Student(n, a, id, c, prog), major(mj), minor(mn), graduationDate(grad) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Undergrad - Program: " << program << ", Major: " << major << ", Minor: " << minor << ", Graduation: " << graduationDate << endl;
    }

    double calculatePayment() override { return 1200; }
};

class GraduateStudent : public Student {
    string researchTopic, advisor, thesisTitle;
public:
    GraduateStudent(string n, int a, int id, string c, string prog, string topic, string adv, string thesis)
        : Student(n, a, id, c, prog), researchTopic(topic), advisor(adv), thesisTitle(thesis) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Graduate - Program: " << program << ", Research: " << researchTopic << ", Advisor: " << advisor << ", Thesis: " << thesisTitle << endl;
    }

    double calculatePayment() override { return 1500; }
};

class Professor : public Person {
protected:
    string department;
public:
    Professor(string n, int a, int id, string c, string dept) : Person(n, a, id, c), department(dept) {}
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string n, int a, int id, string c, string dept)
        : Professor(n, a, id, c, dept) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Assistant Professor - Department: " << department << endl;
    }

    double calculatePayment() override { return 4000; }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string n, int a, int id, string c, string dept)
        : Professor(n, a, id, c, dept) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Associate Professor - Department: " << department << endl;
    }

    double calculatePayment() override { return 5000; }
};

class FullProfessor : public Professor {
public:
    FullProfessor(string n, int a, int id, string c, string dept)
        : Professor(n, a, id, c, dept) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Full Professor - Department: " << department << endl;
    }

    double calculatePayment() override { return 6000; }
};

class Course {
public:
    string title;
    Professor* instructor;
    Course(string t, Professor* prof) : title(t), instructor(prof) {}

    void showCourse() {
        cout << "Course: " << title << ", Instructor: " << instructor->name << endl;
    }
};

class Department {
public:
    string deptName;
    vector<Professor*> professors;
    Department(string name) : deptName(name) {}

    void addProfessor(Professor* p) {
        professors.push_back(p);
    }

    void showProfessors() {
        cout << "Department: " << deptName << endl;
        for (auto& p : professors) p->displayDetails();
    }
};

int main() {
    UndergraduateStudent u("Alice", 20, 1, "alice@mail.com", "CS", "CS", "Math", "2025");
    GraduateStudent g("Bob", 25, 2, "bob@mail.com", "CS", "AI", "Dr. Smith", "AI and Ethics");
    AssistantProfessor ap("Dr. Kim", 40, 3, "kim@uni.edu", "CS");
    AssociateProfessor asp("Dr. Jane", 50, 4, "jane@uni.edu", "Math");

    Department cs("Computer Science");
    cs.addProfessor(&ap);
    cs.addProfessor(&asp);

    Course c1("C++ Programming", &ap);

    u.displayDetails();
    g.displayDetails();
    ap.displayDetails();
    asp.displayDetails();

    c1.showCourse();
    cs.showProfessors();

    return 0;
}
