#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Course {
public:
    string name;
    int creditHours;
    double gradePoint;

    Course(string n, int ch, double gp)
        : name(n), creditHours(ch), gradePoint(gp) {}
};

class CGPACalculator {
private:
    vector<Course> courses;

public:
    void addCourse(const string& name, int creditHours, double gradePoint) {
        courses.emplace_back(name, creditHours, gradePoint);
    }

    double calculateCGPA() {
        double totalPoints = 0;
        int totalCredits = 0;
        for (const auto& c : courses) {
            totalPoints += c.creditHours * c.gradePoint;
            totalCredits += c.creditHours;
        }
        return (totalCredits == 0) ? 0 : totalPoints / totalCredits;
    }

    void displayCourses() {
        cout << "\nCourses Entered:\n";
        cout << left << setw(15) << "Course"
             << setw(15) << "Credits"
             << setw(15) << "Grade Point" << endl;
        cout << string(45, '-') << endl;
        for (const auto& c : courses) {
            cout << left << setw(15) << c.name
                 << setw(15) << c.creditHours
                 << setw(15) << c.gradePoint << endl;
        }
    }
};

// Windows Entry Point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AllocConsole(); // Create a console window
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout); // Redirect stdout to console
    freopen_s(&stream, "CONIN$", "r", stdin);   // Redirect stdin to console

    CGPACalculator calc;
    int numCourses;
    cout << "Enter number of courses: ";
    cin >> numCourses;

    for (int i = 0; i < numCourses; i++) {
        string name;
        int credits;
        double grade;
        cout << "Enter course name: ";
        cin >> name;
        cout << "Enter credit hours: ";
        cin >> credits;
        cout << "Enter grade point (0-4): ";
        cin >> grade;
        calc.addCourse(name, credits, grade);
    }

    calc.displayCourses();
    cout << "\nYour CGPA is: " << fixed << setprecision(2) << calc.calculateCGPA() << endl;

    system("pause"); // Hold console open
    FreeConsole();   // Close console when done
    return 0;
}
