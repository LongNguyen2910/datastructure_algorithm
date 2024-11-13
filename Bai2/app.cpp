#include <iostream>
#include "management.h"
#include "bst.h"
#include "linkedlist.h"
using namespace std;

class app {
    private:
        Management november;
    public:

        void enterTask() {
            int m_day;
            cout << "Enter day: ";
            do {
                cin >> m_day;
                if (!checkValid(m_day))
                    cout << "Invalid day input\n";
            } while (!checkValid(m_day));
            Data task;
            cin >> task;
            november.addTask(m_day, task);
        }

        void viewTaskDay() {
            int x;
            char choice;
            cout << "Enter day: ";
            cin >> x;
            november.viewTaskDay(x);
            do {
                cout << "Come back? (y/n)";
                cin >> choice;
            } while (choice != 'y');
        }

        void viewTaskPrior() {
            int choice;
            cout << "1. Not necessary\n"
                 << "2. Necessary\n"
                 << "3. Important\n"
                 << "4. Very Important\n";
            cout << "Enter your choice: \n";
            cin >> choice;
            november.preOder(november.getDay().getRoot(), choice, printPriority);
            char y;
            do {
                cout << "Come back? (y/n)";
                cin >> y;
            } while (y != 'y');
        }

        void viewTaskStatus() {
            int choice;
            cout << "1. In Progress\n"
                 << "2. Completed\n";
            cout << "Enter your choice: \n";
            cin >> choice;
            november.preOder(november.getDay().getRoot(), choice, printStatus);
            char y;
            do {
                cout << "Come back? (y/n)";
                cin >> y;
            } while (y != 'y');
        }

        void viewAToB() {
            int a, b;
            cout << "enter a and b (a < b): ";
            cin >> a >> b;
            auto it = november.getDay().search(a, november.getDay().getRoot(), 1);
            november.inOder(it, b, printAToB);
            char y;
            do {
                cout << "Come back? (y/n)";
                cin >> y;
            } while (y != 'y');
        }

        void deleteTask() {
            int hour, day;
            cout << "Enter day and hour: ";
            cin >> day >> hour;
            november.deleteTask(day, hour);
        }

        void editTask() {
            int curDay, curHour;
            cout << "Enter current day and current hour: ";
            cin >> curDay >> curHour;
            november.editTask(curDay, curHour);
        }

        void display() {
            int choice;
            do {
                cout << "--------------\n";
                
                november.getDay().preOder(november.getDay().getRoot(), print);

                cout << "--------------\n";
                cout << "1. Add task\n";
                cout << "2. View task (Day)\n";
                cout << "3. View task (Priority)\n";
                cout << "4. View task (Status)\n";
                cout << "5. View task (day a to day b)\n";
                cout << "6. delete task\n";
                cout << "7. Edit task\n";
                cout << "8. Exit\n";
                cout << "--------------\n";
                cin >> choice;
                switch(choice) {
                    case 1:
                        enterTask();
                        break;
                    case 2:
                        viewTaskDay();
                        break;
                    case 3: 
                        viewTaskPrior();
                        break;
                    case 4:
                        viewTaskStatus();
                        break;
                    case 5:
                        viewAToB();
                        break;
                    case 6:
                        deleteTask();
                        break;
                    case 7:
                        editTask();
                        break;
                    case 8:
                        break;
                    default:
                        cout << "Invalid input!\n";
                        break;
                }
            } while (choice != 8);
        }
};

int main() {
    app x;
    x.display();
    return 0;
}