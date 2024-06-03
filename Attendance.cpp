# Attendance-
#Attendance Management System Using C++

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sys/time.h>

using namespace std;

class Student {
public:
    string name;
    int roll_number;
    map<struct timeval, bool> attendance_record;

    void mark_present(struct timeval date) {
        attendance_record[date] = true;
    }

    double calculate_attendance_percentage();
};

double Student::calculate_attendance_percentage() {
    int total_classes = attendance_record.size();
    int attended_classes = 0;
  double Student::calculate_attendance_percentage() {
    int total_classes = attendance_record.size();
    int attended_classes = 0;
    for (auto& entry : attendance_record) {
        if (entry.second) {
            attended_classes++;
        }
    }
    return (attended_classes / (double)total_classes) * 100;
} // <--- This closing brace was missing

class AttendanceManagementSystem {
public:
    map<string, Student> students;
    string filename;

    void add_student(string name, int roll_number) {
        students[name] = Student{name, roll_number};
    };

    bool search_student(string name) {
        return students.find(name) != students.end();
    }

    void mark_present(string name, struct timeval date) {
        if (search_student(name)) {
            students[name].mark_present(date);
        } else {
            cout << "Student not found. Please add the student first." << endl;
        }
    }

    void store_attendance_record() {
        ofstream file(filename.c_str());
        for (auto& student : students) {
            file << "Name: " << student.second.name << ", Roll Number: " << student.second.roll_number << ", Attendance Record: ";
            for (auto& entry : student.second.attendance_record) {
                file << entry.first.tv_sec << ":" << (entry.second ? "PRESENT" : "ABSENT") << " ";
            }
            file << endl;
        }
    };

    void generate_report(struct timeval date) {
        cout << "Attendance Report for " << date.tv_sec << ":" << endl;
        for (auto& student : students) {
            bool attended = student.second.attendance_record.count(date) && student.second.attendance_record[date];
            cout << "Name: " << student.second.name << ", Roll Number: " << student.second.roll_number << ", Availability: " << (attended ? "PRESENT" : "ABSENT") << endl;
        }
    };

    void calculate_attendance_percentage(string name) {
        if (search_student(name)) {
            double percentage = students[name].calculate_attendance_percentage();
            cout << "Attendance Percentage for " << name << ": " << percentage << "%" << endl;
        } else {
            cout << "Student not found. Please add the student first." << endl;
        }
    };
};

int main() {
    AttendanceManagementSystem AMS;
    AMS.filename = "attendance_record.txt";

    while (true) {
        cout << "1. Add Student" << endl;
        cout << "2. Mark Present" << endl;
        cout << "3. Generate Report" << endl;
        cout << "4. Calculate Attendance Percentage" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            string name;
            int roll_number;
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter roll number: ";
            cin >> roll_number;
            AMS.add_student(name, roll_number);
        } else if (choice == 2) {
            string name;
            struct timeval date;
            gettimeofday(&date, NULL);
            cout << "Enter student name: ";
            cin >> name;
            AMS.mark_present(name, date);
        } else if (choice == 3) {
            struct timeval date;
            gettimeofday(&date, NULL);
            AMS.generate_report(date);
        } else if (choice == 4) {
            string name;
            cout << "Enter student name: ";
            cin >> name;
            AMS.calculate_attendance_percentage(name);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
