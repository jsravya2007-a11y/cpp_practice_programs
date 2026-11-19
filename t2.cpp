#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Base class
class Student {
protected:
    int rollNo;
    string name;
public:
    Student(int r, string n) {
        rollNo = r;
        name = n;
    }
    virtual void display() {
        cout << "Roll No: " << rollNo << ", Name: " << name << endl;
    }
    virtual int getTotal() {
        return 0;
    }
    virtual void save(ofstream &out) {
        out << rollNo << " " << name << endl;
    }
    virtual ~Student() {}
};

// Derived class
class Result : public Student {
private:
    int m1, m2, m3;
public:
    Result(int r, string n, int a, int b, int c) : Student(r, n) {
        // exception handling for invalid marks
        if (a < 0 || a > 100 || b < 0 || b > 100 || c < 0 || c > 100)
            throw string("Invalid marks entered for " + n);
        m1 = a;
        m2 = b;
        m3 = c;
    }
    int getTotal() {
        return m1 + m2 + m3;
    }
    string getResult() {
        if (m1 >= 40 && m2 >= 40 && m3 >= 40)
            return "PASS";
        return "FAIL";
    }
    void display() {
        Student::display();
        cout << "Marks: " << m1 << " " << m2 << " " << m3
             << " | Total: " << getTotal()
             << " | Result: " << getResult() << endl;
    }
    void save(ofstream &out) {
        out << rollNo << " " << name << " " << m1 << " " << m2 << " " << m3 << endl;
    }
};

// adds a student to the vector, catches invalid marks
void addStudent(vector<Student*> &list, int r, string n, int a, int b, int c) {
    try {
        list.push_back(new Result(r, n, a, b, c));
    }
    catch (string msg) {
        cout << "Error: " << msg << endl;
    }
}

int main() {
    vector<Student*> students;

    addStudent(students, 101, "Sravya", 88, 92, 79);
    addStudent(students, 102, "Ananya", 70, 35, 80);
    addStudent(students, 103, "Rohit", 95, 105, 90);   // invalid marks
    addStudent(students, 104, "Meena", 91, 94, 97);

    cout << "\n--- All Students ---" << endl;
    for (Student *s : students)
        s->display();                  // runtime polymorphism

    // save records to file
    ofstream out("students.txt");
    for (Student *s : students)
        s->save(out);
    out.close();
    cout << "\nRecords saved to students.txt" << endl;

    // read records back from file
    ifstream in("students.txt");
    vector<Student*> loaded;
    int r, a, b, c;
    string n;
    while (in >> r >> n >> a >> b >> c)
        loaded.push_back(new Result(r, n, a, b, c));
    in.close();
    cout << loaded.size() << " records loaded from file" << endl;

    // lambda + STL algorithm to find students above a mark
    int limit = 240;
    cout << "\n--- Students with total above " << limit << " ---" << endl;
    auto above = [limit](Student *s) { return s->getTotal() > limit; };
    for (Student *s : loaded)
        if (above(s))
            s->display();
    cout << "Count = " << count_if(loaded.begin(), loaded.end(), above) << endl;

    // free memory
    for (Student *s : students) delete s;
    for (Student *s : loaded) delete s;

    return 0;
}
