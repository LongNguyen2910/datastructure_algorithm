#include <iostream>
#include <string>
#include "bst.h"
#include "linkedlist.h"
using namespace std;

#ifndef  __MANAGEMENT__CPP__
#define  __MANAGEMENT__CPP__


class Data {
    private:
        int hour;
        string name, description;
        int priority, status;
    public:
        Data() = default;
        Data(int m_hour, string m_name, string m_des, int m_prior, int m_status) {
            hour = m_hour;
            name = m_name;
            description = m_des;
            priority = m_prior;
            status = m_status;
        }
        int getHour() { return hour; }
        string getName() { return name; }
        string getDes() { return description; }
        int getPrior() { return priority; }
        int getStatus() { return status; }

        void setHour(int m_hour) { hour = m_hour; }
        void setName(string m_name) { name = m_name; }
        void setDes(string m_des) { description = m_des; }
        void setPrior(int m_prior) { priority = m_prior; }

        friend ostream& operator<< (ostream& out, const Data& data);
};

ostream& operator<< (ostream& out, const Data& data) {
    out << data.hour << " | " << data.name << " | "
        << data.description << " | ";
    if (data.priority == 1)
        out << "Not necessary | ";
    else if (data.priority == 2)
        out << "Necessary | ";
    else if (data.priority == 3)
        out << "Important | ";
    else if (data.priority == 4)
        out << "Very Important | ";
    if (data.status == 1)
        out << "In progress";
    else out << "Completed";
    out << "\n";
    return out;
}

istream& operator>> (istream& in, Data& data) {
    int hour;
    string name, des;
    int prior, status; 
    cout << "Enter time begin: "; 
    do {
        in >> hour;
        if (hour >= 24 && hour < 0)
            cout << "Invalid hour input. Try Again!\n";
    } while (hour >= 24 && hour < 0);


    cout << "Enter name of task: ";
    in.ignore(1);
    getline(in, name);
    cout << "Enter task's description: ";
    getline(in, des);
    cout << "Enter priority\n";
    cout << "1. Not necessary\n"
         << "2. Necessary\n"
         << "3. Important\n"
         << "4. Very Important\n";
    do {
        in >> prior;
        if (prior > 4 || prior < 1)
            cout << "Invalid priority input. Try Again!\n";
    } while(prior > 4 || prior < 1);

    cout << "Enter status\n";
    cout << "1. In progress\n"
         << "2. Completed\n";
    do {
        in >> status;
        if (status != 1 && status != 2)
            cout << "Invalid status input\n";
    } while (status != 1 && status != 2);
    data = Data(hour, name, des, prior, status);
    return in;
}

class Management {
    private:
        BinaryTree<int, DoublyList<Data>> day;
    public:
        Management() = default;

        BinaryTree<int, DoublyList<Data>> getDay() { return day; }

        void addTask(int m_day, Data task) {     
            if (!day.isEmpty() && day.search(m_day, day.getRoot()) != nullptr) {
                auto it = day.search(m_day, day.getRoot());
                DoublyList<Data> tmp = it->getElem();
                for (Iterator<Data> i = tmp.front(); i != nullptr; i++) {
                    if ((*i).getHour() > task.getHour()) {
                        if (i != tmp.front()) {
                            tmp.insert(task, i.getCur()->getPrev());
                        } else 
                            tmp.push_front(task);
                        it->setElem(tmp);
                        return;
                    }
                }
                tmp.push_back(task);
                it->setElem(tmp);
            } else {
                DoublyList<Data> tmp;
                tmp.push_back(task);
                day.addNode(m_day, tmp);
            }
        }

        void deleteTask(int m_day, int m_hour) {
            if (day.search(m_day, day.getRoot()) != nullptr) {
                auto i = day.search(m_day, day.getRoot());
                DoublyList<Data> tmp = i->getElem();
                for (Iterator<Data> it = tmp.front(); it != nullptr; ++it) {
                    if ((*it).getHour() == m_hour) {
                        tmp.erase(it.getCur());
                        if (tmp.getSize() == 0)
                            day.remove(i->getKey());
                        else 
                            i->setElem(tmp);
                        break;
                    } 
                }
            } else {
                cout << "Not found!\n";
            }
        }

        void editTask(int m_day, int m_hour) {
            int newDay, newHour;
            Data newTask;
            cout << "Enter new day and new hour: ";
            cin >> newDay >> newHour;
            if (day.search(m_day, day.getRoot()) != nullptr) {
                auto it = day.search(m_day, day.getRoot());
                DoublyList<Data> tmp = it->getElem();
                for (Iterator<Data> i = tmp.front(); i != nullptr; ++i) {
                    if ((*i).getHour() == m_hour) {
                        newTask = Data(newHour, (*i).getName(), (*i).getDes() ,(*i).getPrior(), (*i).getStatus());
                        tmp.erase(i.getCur());
                        if (tmp.getSize() == 0)
                            day.remove(it->getKey());
                        else 
                            it->setElem(tmp);
                        addTask(newDay, newTask);
                        break;
                    } else {
                        cout << "Not found!\n";
                    }
                }
            } else {
                cout << "Not found!\n";
            }
        }

        void viewTaskDay(int m_day) {
            if (day.search(m_day, day.getRoot()) != nullptr) {
                auto i = day.search(m_day, day.getRoot());
                for (Iterator<Data> it = i->getElem().front(); it != nullptr; ++it) {
                    cout << *it;
                }
            } else {
                cout << "Not found!\n";
            }
        }

        void inOder(Node<int, DoublyList<Data>>* tmp, int end, void (*visit)(Node<int, DoublyList<Data>>* m_node, int end)) {
            if (tmp) {
                inOder(tmp->getLeft(), end, visit);
                visit(tmp, end);
                inOder(tmp->getRight(), end, visit);
            }
        }
        
        void preOder(Node<int, DoublyList<Data>>* tmp, int choice, void (*visit)(Node<int, DoublyList<Data>>* m_node, int m_choice)) {
            if (tmp) {
                visit(tmp, choice);
                preOder(tmp->getLeft(), choice, visit);
                preOder(tmp->getRight(), choice, visit);
            }
        }

            
};


void printPriority(Node<int, DoublyList<Data>>* m_node, int choice) {
    bool flag = 1;
    cout << "Day" << m_node->getKey() << "\n";
    for (Iterator<Data> i = m_node->getElem().front(); i != nullptr; ++i) {
        if ((*i).getPrior() == choice)
        {
            cout << *i;
            flag = 0;
        }
    }
    if (flag)
        cout << "empty\n";
}

void printStatus(Node<int, DoublyList<Data>>* m_node, int choice) {
    bool flag = 1;
    cout << "Day" << m_node->getKey() << "\n";
    for (Iterator<Data> i = m_node->getElem().front(); i != nullptr; ++i) {
        if ((*i).getStatus() == choice)
        {
            cout << *i;
            flag = 0;
        }
    }
    if (flag)
        cout << "empty\n";
}

void printAToB(Node<int, DoublyList<Data>>* tmp, int end) {
    cout << "Day" << tmp->getKey() << "\n";
    for (Iterator<Data> i = tmp->getElem().front(); i != nullptr; ++i) {
        cout << *i;
    }
    if (tmp->getKey() == end)
        return;
}

bool checkValid(int day) {
    if (day > 31 || day <= 0)
        return false;
    return true;
}

void print(Node<int, DoublyList<Data>>* tmp) {
    cout << "Day " << tmp->getKey() << "\n";
    for (Iterator<Data> i = tmp->getElem().front(); i != nullptr; ++i) {
        if (i != nullptr)
            cout << *i;
    }
}

#endif