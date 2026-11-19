#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Node structure for each student
struct Student {
    int rollNo;
    string name;
    string course;
    float marks;
    Student* next;

    Student(int r, string n, string c, float m) {
        rollNo = r;
        name = n;
        course = c;
        marks = m;
        next = nullptr;
    }
};

// Student Record Management System
class StudentList {
private:
    Student* head;

public:
    StudentList() {
        head = nullptr;
    }

    // Destructor
    ~StudentList() {
        Student* current = head;

        while (current != nullptr) {
            Student* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Add a new student
    void addStudent() {
        int rollNo;
        string name, course;
        float marks;

        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        // Check duplicate roll number
        Student* current = head;

        while (current != nullptr) {
            if (current->rollNo == rollNo) {
                cout << "Student with this roll number already exists.\n";
                return;
            }
            current = current->next;
        }

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks (0-100): ";
        cin >> marks;

        if (marks < 0 || marks > 100) {
            cout << "Invalid marks.\n";
            return;
        }

        Student* newStudent =
            new Student(rollNo, name, course, marks);

        if (head == nullptr) {
            head = newStudent;
        } else {
            current = head;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newStudent;
        }

        cout << "Student record added successfully!\n";
    }

    // Display all students
    void displayStudents() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        Student* current = head;

        cout << "\n";
        cout << left
             << setw(12) << "Roll No"
             << setw(25) << "Name"
             << setw(20) << "Course"
             << setw(10) << "Marks"
             << "\n";

        cout << string(67, '-') << "\n";

        while (current != nullptr) {
            cout << left
                 << setw(12) << current->rollNo
                 << setw(25) << current->name
                 << setw(20) << current->course
                 << setw(10) << fixed << setprecision(2)
                 << current->marks
                 << "\n";

            current = current->next;
        }
    }

    // Search student by roll number
    void searchStudent() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        int rollNo;

        cout << "\nEnter Roll Number to search: ";
        cin >> rollNo;

        Student* current = head;

        while (current != nullptr) {
            if (current->rollNo == rollNo) {
                cout << "\nStudent Found!\n";
                cout << "--------------------------\n";
                cout << "Roll Number : " << current->rollNo << "\n";
                cout << "Name        : " << current->name << "\n";
                cout << "Course      : " << current->course << "\n";
                cout << "Marks       : " << current->marks << "\n";
                return;
            }

            current = current->next;
        }

        cout << "Student not found.\n";
    }

    // Update student record
    void updateStudent() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        int rollNo;

        cout << "\nEnter Roll Number to update: ";
        cin >> rollNo;

        Student* current = head;

        while (current != nullptr) {
            if (current->rollNo == rollNo) {

                cin.ignore();

                cout << "Enter New Name: ";
                getline(cin, current->name);

                cout << "Enter New Course: ";
                getline(cin, current->course);

                cout << "Enter New Marks (0-100): ";
                cin >> current->marks;

                if (current->marks < 0 || current->marks > 100) {
                    cout << "Invalid marks.\n";
                    return;
                }

                cout << "Student record updated successfully!\n";
                return;
            }

            current = current->next;
        }

        cout << "Student not found.\n";
    }

    // Delete student
    void deleteStudent() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        int rollNo;

        cout << "\nEnter Roll Number to delete: ";
        cin >> rollNo;

        // If first node has the roll number
        if (head->rollNo == rollNo) {
            Student* temp = head;
            head = head->next;

            delete temp;

            cout << "Student record deleted successfully!\n";
            return;
        }

        Student* current = head;

        while (current->next != nullptr) {

            if (current->next->rollNo == rollNo) {
                Student* temp = current->next;

                current->next = temp->next;

                delete temp;

                cout << "Student record deleted successfully!\n";
                return;
            }

            current = current->next;
        }

        cout << "Student not found.\n";
    }

    // Selection sort by marks
    void sortByMarks() {
        if (head == nullptr || head->next == nullptr) {
            cout << "\nNot enough records to sort.\n";
            return;
        }

        Student* current = head;

        while (current != nullptr) {

            Student* maximum = current;
            Student* temp = current->next;

            while (temp != nullptr) {

                if (temp->marks > maximum->marks) {
                    maximum = temp;
                }

                temp = temp->next;
            }

            // Swap data instead of nodes
            if (maximum != current) {

                swap(current->rollNo, maximum->rollNo);
                swap(current->name, maximum->name);
                swap(current->course, maximum->course);
                swap(current->marks, maximum->marks);
            }

            current = current->next;
        }

        cout << "\nStudents sorted by marks successfully!\n";
    }

    // Find topper
    void findTopper() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        Student* topper = head;
        Student* current = head->next;

        while (current != nullptr) {

            if (current->marks > topper->marks) {
                topper = current;
            }

            current = current->next;
        }

        cout << "\n========== TOPPER ==========\n";
        cout << "Roll Number : " << topper->rollNo << "\n";
        cout << "Name        : " << topper->name << "\n";
        cout << "Course      : " << topper->course << "\n";
        cout << "Marks       : "
             << fixed << setprecision(2)
             << topper->marks << "\n";
        cout << "============================\n";
    }

    // Display statistics
    void showStatistics() {
        if (head == nullptr) {
            cout << "\nNo student records available.\n";
            return;
        }

        int count = 0;
        float totalMarks = 0;

        Student* current = head;

        while (current != nullptr) {
            count++;
            totalMarks += current->marks;
            current = current->next;
        }

        float average = totalMarks / count;

        cout << "\n========== STATISTICS ==========\n";
        cout << "Total Students : " << count << "\n";
        cout << "Average Marks  : "
             << fixed << setprecision(2)
             << average << "\n";
        cout << "================================\n";
    }
};

// Main function
int main() {

    StudentList students;

    int choice;

    do {
        cout << "\n";
        cout << "========================================\n";
        cout << "     STUDENT RECORD MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort by Marks\n";
        cout << "7. Find Topper\n";
        cout << "8. Student Statistics\n";
        cout << "9. Exit\n";
        cout << "========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                students.addStudent();
                break;

            case 2:
                students.displayStudents();
                break;

            case 3:
                students.searchStudent();
                break;

            case 4:
                students.updateStudent();
                break;

            case 5:
                students.deleteStudent();
                break;

            case 6:
                students.sortByMarks();
                break;

            case 7:
                students.findTopper();
                break;

            case 8:
                students.showStatistics();
                break;

            case 9:
                cout << "\nThank you for using the Student Record "
                        "Management System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}