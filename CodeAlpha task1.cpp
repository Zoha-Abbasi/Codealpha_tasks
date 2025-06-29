#include <iostream>
using namespace std;

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    double totalGradePoints = 0;
    int totalCreditHours = 0;

    cout << "\nCourse\tGrade\tCredit Hours\tGrade Points\n";

    for (int i = 1; i <= numCourses; i++) {
        double grade;
        int creditHours;

        cout << "\nEnter grade for course " << i << " (on 4.0 scale): ";
        cin >> grade;

        cout << "Enter credit hours for course " << i << ": ";
        cin >> creditHours;

        double gradePoints = grade * creditHours;

        totalGradePoints += gradePoints;
        totalCreditHours += creditHours;        cout << "Course " << i << "\t" << grade << "\t" << creditHours << "\t\t" << gradePoints << endl;
    }

    double cgpa = totalGradePoints / totalCreditHours;

    cout << "\n====================================\n";
    cout << "Total Credit Hours: " << totalCreditHours << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Final CGPA: " << cgpa << endl;
    cout << "====================================\n";

    return 0;
}
