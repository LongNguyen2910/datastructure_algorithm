#include <bits/stdc++.h>
#include "stu_management.h"
#include "student.h"
using namespace std;

class application {
    private:
        StudentManagement s2024;
    public:
        void menu() {
            cout << "\n" << setw(45) << " " << "MENU\n"
                 << "1. Read data from file\n"
                 << "2. Write data to file\n"
                 << "3. Add Student\n"
                 << "4. Delete Student\n"
                 << "5. Search Student\n"
                 << "6. Sort (GPA)\n"
                 << "7. Top Highest GPA\n"
                 << "8. Top Lowest GPA\n"
                 << "9. Exit\n\n";
        }

        void printSort() {
            StudentManagement tmp {s2024};
            char choice {};
            do {
                tmp.sortStudent();
                cout << "\n" << setw(32) << " " << "Sorted list\n";
                cout << left << setw(15) << "ID" << setw(30) << "Name"
                     << setw(10) << "Gender" << setw(16) << "Date of Birth"
                     << setw(6) << "GPA" << "Letter Grade" << endl;
                for (int i = 0; i < 89; ++i)
                    cout << '-';
                cout << "\n";
                for (auto i : tmp.getStudent()) {
                    cout << i;
                }
                cout << "Do u want to come back (y/n)\n";
                cin >> choice;
            } while (choice != 'y');
            cout << "\n";
        }

        void searchStudent() {
            char choice {};
            do {
                string ID {};
                cout << "Enter ID: ";
                while (ID.length() != 10) {
                    cin >> ID;
                    if (ID.length() != 10)
                        cout << "Invalid ID input, try again!\n";
                }
                auto i = s2024.searchID(ID);
                if (i != s2024.getStudent().end())
                    cout << *i;
                else
                    cout << "Not found!\n";
                cout << "Do you want to come back (y/n)\n";
                cin >> choice;
            } while (choice != 'y');
        }

        void deleteStudent() {
            string ID {};
            cout << "Enter ID: ";
            while (ID.length() != 10) {
                cin >> ID;
                if (ID.length() != 10)
                    cout << "Invalid ID input, try again!\n";
            }
            s2024.deleteStudent(ID);
        }

        void printFilterA() {
            StudentManagement tmp {s2024};
            tmp.sortStudent();
            char choice {};
            do {
                tmp.filterScholarship();
                cout << "Do you want to comeback (y/n)\n";
                cin >> choice;
            } while (choice != 'y');
        }

        void printFail() {
            StudentManagement tmp {s2024};
            tmp.sortStudent();
            char choice {};
            do {
                tmp.filterFail();
                cout << "Do you want to comeback (y/n)\n";
                cin >> choice;
            } while (choice != 'y');
        }

        void display() {
            int choice = -1;
            do {  
                system("cls");
                s2024.printList();

                for (int i = 0; i < 89; ++i)
                    cout << '-';
                cout << "\n";

                menu();
                cout << "Enter your choice: ";
                cin >> choice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1, '\n');
                    cout << "Invalid choice input\n";
                    continue;
                }
                switch (choice) {
                    case 1:
                        s2024.readFile();
                        break;
                    case 2:
                        s2024.writeFile();
                        break;
                    case 3: 
                        s2024.addStudent();
                        break;
                    case 4:
                        deleteStudent();
                        break;
                    case 5:
                        searchStudent();
                        break;
                    case 6:
                        printSort();
                        break;
                    case 7:
                        printFilterA();
                        break;
                    case 8:
                        printFail();
                        break;
                    case 9:
                        break;
                    default:
                        cout << "Invalid choice input, try again!\n";
                        break;
                    
                }
            } while(choice != 9);
        }
};

int main() {
    application x;
    x.display();
    return 0;
}