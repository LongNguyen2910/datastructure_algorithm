#include <bits/stdc++.h>
using namespace std;

#ifndef STUDENT_DATA_STRUCTURE
#define STUDENT_DATA_STRUCTURE

struct dateOfBirth {
    int day, month, year;
    dateOfBirth(int x, int y,int z): day {x}, month {y}, year {z} {};
    dateOfBirth() = default;
};

class Student {
    private:
        string id, name;
        bool gender;
        dateOfBirth dOB; 
        float gpa;
        int major;
        char letterGrade[2];
    public:
        //Constructor
        Student() {
            id = "";
            name = "";
            dOB = dateOfBirth(0,0,0);
            gpa = 0;
            letterGrade[0] = letterGrade[1] = '\0';
        }
        Student(string m_name, bool m_gender, dateOfBirth m_dOB, int m_major, float m_gpa) {
            name = m_name;
            gender = m_gender;
            dOB = m_dOB;
            gpa = m_gpa;
            major = m_major;
        }

        //Get element
        string_view getId() { return id; }
        string_view getName() { return name; }
        bool getGender() { return gender; }
        dateOfBirth getDOB() { return dOB; }
        int getMajor() { return major; }
        float getGPA() { return gpa; }
        char* getLetterGrade() { return letterGrade; }

        //Set element
        void setId(string_view m_id) { id = m_id; }
        void setName(string_view m_name) { name = m_name; }

        //Output
        friend ostream& operator<< (ostream& out, const Student& student);

        bool operator<(Student s1) {
            return gpa < s1.getGPA();
        }
};

// Check input
bool checkValid(string_view m_name) {
    size_t tmp = m_name.length();
    if (tmp == 0) return 0;
    while (tmp--) {
        if (m_name[tmp] == ' ')
            continue;
        if ((m_name[tmp] <= 96 && m_name[tmp] >= 91)
           ||m_name[tmp] < 65 || m_name[tmp] > 122)
            return 0;
    }
    return 1;
}

bool checkValid(dateOfBirth m_dOB) {
    if (m_dOB.day <= 31 && m_dOB.day > 0)
        if (m_dOB.month <= 12 && m_dOB.month > 0)
            if (m_dOB.year >= 2000)
                return 1;
    return 0;
}

bool checkValid(float m_gpa) {
    if (m_gpa >= 0 && m_gpa <= 4)
        return 1;
    return 0;
}

bool checkValid(int m_major) {
    if (m_major > 4 || m_major <= 0) 
        return 0;
    return 1;
}

//Input, Output
istream& operator>> (istream& in, Student& student) {
    string m_name;
    bool m_gender;
    dateOfBirth m_dOB;
    int m_major;
    float m_gpa;

    cout << "Enter name: ";
    do {
        cin.ignore(1);
        getline(in, m_name);
        if (!checkValid(m_name))
            cout << "Invalid Name input, enter again\n";
    } while (!checkValid(m_name));

    cout << "Enter gender (1-Male, 0-Female): ";
    while (true) {
        in >> m_gender;
        if (in.fail()) {
            in.clear(); 
            in.ignore(1, '\n');
            cout << "Invalid gender input\n";
            continue; 
        }
        break;
    }


    cout << "Enter Date Of Birth\n";
    do {
        cout << "Enter Day: ";
        in >> m_dOB.day;
        cout << "Enter Month: ";
        in >> m_dOB.month;
        cout << "Enter Year: ";
        in >> m_dOB.year;
        if (!checkValid(m_dOB))
            cout << "Invalid Date of Birth input\n";
    } while (!checkValid(m_dOB));


    cout << "Enter major (a digit)\n";
    cout << "1. Information Technology\n";
    cout << "2. Finance\n";
    cout << "3. Electrical Engineering\n";
    cout << "4. Mechanical Engineering\n";
    do {
        cin >> m_major;
        if (!checkValid(m_major)) 
            cout << "Invalid major input\n";
    } while (!checkValid(m_major));
    

    cout << "Enter GPA: ";
    do {
        in >> m_gpa;
        if (!checkValid(m_gpa))
            cout << "Invalid GPA input\n";
    } while (!checkValid(m_gpa));

    student = Student(m_name, m_gender, m_dOB, m_major, m_gpa);

    return in;
}

ostream& operator<< (ostream& out, const Student& student) {
    out << left << setw(15) << student.id << setw(30) << student.name
        << setw(10) << (student.gender == 1 ? "Male" : "Female")
        << (student.dOB.day < 10 ? '0' : '\0') << student.dOB.day << "/" 
        << (student.dOB.month < 10 ? '0' : '\0') << student.dOB.month << "/" 
        << setw(10) << student.dOB.year << setw(6) << fixed << setprecision(2) << student.gpa 
        << student.letterGrade[0] << student.letterGrade[1] << endl;
    return out;
}

#endif