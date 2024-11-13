#include <bits/stdc++.h>
#include "student.h"
using namespace std;

#ifndef STUDENT_STUDENT_MANAGEMENT
#define STUDENT_STUDENT_MANAGEMENT

class StudentManagement {
    private:
        vector<Student> student;
        int curID;
    public:
        //Constructor
        StudentManagement(): student {}, curID {1} {}

        //Get element
        vector<Student> getStudent() { return student; }
        int getCurID() { return curID; }
        
        //Set element
        void setCurID(int x) { curID = x; }

        //Member function
        
        //Modify
        void modify(Student& student) {
            string m_ID{"S2024"};
            stringstream number;
            string toString;
            student.getLetterGrade()[0] = student.getLetterGrade()[1] = '\0';

            // modify letter grade
            float gpa = student.getGPA();
            if (gpa <= 4.0 && gpa >= 3.3) {
                student.getLetterGrade()[0] = 'A';
                if (gpa <= 3.69)
                    student.getLetterGrade()[1] = '-';
            }
            else if (gpa <= 3.29 && gpa >= 2.3) {
                student.getLetterGrade()[0] = 'B';
                if (gpa >= 3)
                    student.getLetterGrade()[1] = '+';
                if (gpa <= 2.69)
                    student.getLetterGrade()[1] = '-';
            }
            else if (gpa <= 2.29 && gpa >= 1.3) {
                student.getLetterGrade()[0] = 'C';
                if (gpa >= 2)
                    student.getLetterGrade()[1] = '+';
                if (gpa <= 1.69)
                    student.getLetterGrade()[1] = '-';
            }
            else if (gpa <= 1.20 && gpa >= 0.99) {
                student.getLetterGrade()[0] = 'D';
                if (gpa >= 1)
                    student.getLetterGrade()[1] = '+';
            }
            else {
                student.getLetterGrade()[0] = 'F';
            }

            fflush(stdin);
            // modify ID (S2024IT001)
            if (student.getMajor() == 1)
                m_ID += "IT";
            if (student.getMajor() == 2)
                m_ID += "FN";
            if (student.getMajor() == 3)
                m_ID += "EE";
            if (student.getMajor() == 4)
                m_ID += "ME";
            number << curID;
            number >> toString;
            if (curID >= 100)
                m_ID += toString;
            else if (curID >= 10)
                m_ID += ('0' + toString);
            else if (curID > 0)
                m_ID += ("00" + toString);
            student.setId(m_ID);
            curID++;
            number.clear();
            toString = "";
        }

        void addStudent() {
            Student m_student;
            cin >> m_student;
            modify(m_student);
            student.push_back(m_student);  
        }

        void readFile() {
            string m_name, file;
            bool m_gender;
            dateOfBirth m_dOB;
            int m_major;
            float m_gpa;
            Student m_student;
            cout << "Enter input file name: ";
            cin >> file;
            ifstream inf(file);
            if (!inf) {
                cerr << "File not found\n";
                return;
            }
            while (getline(inf, m_name)) {
                inf >> m_gender >> m_dOB.day >> m_dOB.month >> m_dOB.year >> m_major >> m_gpa;
                m_student = Student(m_name, m_gender, m_dOB, m_major, m_gpa);
                modify(m_student);
                student.push_back(m_student);  
                inf.ignore(1);
            }
            inf.close();
        }

        void printList() {
            cout << left << setw(15) << "ID" << setw(30) << "Name"
                 << setw(10) << "Gender" << setw(16) << "Date of Birth"
                 << setw(6) << "GPA" << "Letter Grade" << endl;
            for (int i = 0; i < 89; ++i)
                cout << '-';
            cout << endl;
            for (auto i : student) {
                cout << i;
            }
        }

        void writeFile() {
            string file;
            cout << "Enter output file name: ";
            cin >> file;
            ofstream outf(file);
            for (auto i : student) {
                outf << i.getId() << "  " << i.getName() << "  " << i.getGender()
                     << "  " << i.getDOB().day << "/" << i.getDOB().month << "/" << i.getDOB().year << "  ";
                switch (i.getMajor()) {
                case 1:
                    outf << "Information Technology";
                    break;
                case 2:
                    outf << "Finance";
                    break;
                case 3: 
                    outf << "Electrical Engineering";
                    break;
                default:
                    outf << "Mechanical Engineering";
                    break;
                }
                outf << "  " << fixed << setprecision(2) << i.getGPA() << "  " << i.getLetterGrade()[0] << i.getLetterGrade()[1] << endl;
            }
            outf.close();
        }

        void sortStudent() {
            auto cmp = [] (Student a, Student b) {
                return b < a;
            };
            sort(student.begin(), student.end(), cmp);
        }

        void filterScholarship() {
            bool flag {false};
            auto it {student.begin()};
            while ((*it).getLetterGrade()[0] == 'A' && (*it).getLetterGrade()[1] == '\0') {
                cout << *it;
                it++;
                flag = true;
            }
            if (flag == false)
                cout << "No student got an A\n";
        }

        void filterFail() {
            bool flag {false};
            auto it {student.rbegin()};
            while ((*it).getGPA() < 1) {
                cout << *it;
                it++;
                flag = true;
            }
            if (flag == false)
                cout << "No student fail\n";
        }
         
        auto searchID(string_view m_id) {
            for (auto i = student.begin(); i != student.end(); ++i) {
                if ((*i).getId() == m_id) {
                    return i;
                }
            }
            cerr << "Not found!\n";
            return student.end();
        }

        void deleteStudent(string_view ID) {
            if (searchID(ID) != student.end()) {
                student.erase(searchID(ID));
                cerr << "Delete successful!\n";
            }
        }
};


void swap(Student& x, Student& y) {
    Student tmp {x};
    x = y;
    y = tmp;
}

#endif