#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    float marks;
    static int count;          // static member: counts students

public:
    // parameterized constructor
    Student(int r, string n, float m) {
        rollNo = r;
        name = n;
        marks = m;
        count++;
    }

    // overloaded functions
    void display() {
        cout << "Roll No: " << rollNo << ", Name: " << name
             << ", Marks: " << marks << endl;
    }
    void display(string title) {
        cout << title << endl;
        display();
    }

    // static function
    static int getCount() {
        return count;
    }

    // overloaded > operator
    bool operator>(Student s) {
        return marks > s.marks;
    }

    // friend function
    friend void showMarks(Student s);
};

int Student::count = 0;

void showMarks(Student s) {
    cout << s.name << " scored " << s.marks << " marks (friend function)" << endl;
}

int main() {
    Student s1(101, "Sravya", 88.5);
    Student s2(102, "Ananya", 76);
    Student s3(103, "Rohit", 92);

    s1.display();
    s2.display("Student 2 details:");

    cout << "Total students = " << Student::getCount() << endl;

    showMarks(s3);

    if (s1 > s2)
        cout << "Sravya has more marks than Ananya" << endl;
    else
        cout << "Ananya has more marks than Sravya" << endl;

    if (s3 > s1)
        cout << "Rohit has more marks than Sravya" << endl;
    else
        cout << "Sravya has more marks than Rohit" << endl;

    return 0;
}
