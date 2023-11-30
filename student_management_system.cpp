#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// Define the structure for user information
struct User {
    string username;
    string password;
};

// Function to register a new user
void registerUser() {
    ofstream file("users.txt", ios::app);
    User newUser;

    cout << "\nEnter Username: ";
    cin >> newUser.username;
    cout << "Enter Password: ";
    cin >> newUser.password;

    // Write the new user information to the file
    file << newUser.username << " " << newUser.password << endl;

    file.close();
    cout << "\nRegistration Successful!\n";
}

// Function to authenticate a user
int authenticateUser(string username, string password) {
    ifstream file("users.txt");
    User user;

    while (file >> user.username >> user.password) {
        if (username == user.username && password == user.password) {
            file.close();
            return 1; // Authentication successful
        }
    }

    file.close();
    return 0; // Authentication failed
}

class student {
    class semester {
        class subject {
            char sub_name[20];
            char grade;
            float q1, q2, ses1, ses2, asn, atd, final, total, internal;
            int credits;
            int g;

        public:
            int getinfo() {
                cout << "Subject name: ";
                cin >> sub_name;
                cout << "Quiz 1: ";
                cin >> q1;
                q1 = q1 / 2;
                cout << "Quiz 2: ";
                cin >> q2;
                q2 = q2 / 2;
                cout << "Sessional 1: ";
                cin >> ses1;
                ses1 = ses1 * 0.3;
                cout << "Sessional 2: ";
                cin >> ses2;
                ses2 = ses2 * 0.3;
                cout << "Attendance percentage: ";
                cin >> atd;
                if (atd >= 95)
                    atd = 5;
                else if (atd < 95 && atd >= 90)
                    atd = 4;
                else if (atd < 90 && atd >= 85)
                    atd = 3;
                else if (atd < 85 && atd >= 80)
                    atd = 2;
                else if (atd < 80 && atd >= 75)
                    atd = 1;
                else
                    atd = 0;
                cout << "Assignment: ";
                cin >> asn;
                cout << "Finals' marks: ";
                cin >> final;
                final = final / 2;
                internal = q1 + q2 + ses1 + ses2 + atd + asn;
                total = internal + final;
                if (total >= 90) {
                    grade = 'S';
                    g = 10;
                } else if (total < 90 && total >= 80) {
                    grade = 'A';
                    g = 9;
                } else if (total < 80 && total >= 70) {
                    grade = 'B';
                    g = 8;
                } else if (total < 70 && total >= 60) {
                    grade = 'C';
                    g = 7;
                } else if (total < 60 && total >= 50) {
                    grade = 'D';
                    g = 6;
                } else if (total < 50 && total >= 35) {
                    grade = 'E';
                    g = 5;
                } else {
                    grade = 'F';
                    g = 0;
                }
                credits = g * 3;
                return credits;
            }

            void display() {
                cout << sub_name << "\t" << q1 << "\t" << q2 << "\t" << ses1 << "\t" << ses2 << "\t" << asn << "\t" << atd << "\t" << internal << "\t\t" << final << "\t\t" << total << "\t" << grade << "\n";
            }
        };

        int n;
        subject* x;
        int tcredits;

        float gpa, score;

    public:
        semester() {
            cout << "Enter the number of subjects for this semester: ";
            cin >> n;
            x = new subject[n];
            tcredits = n * 3;
            score = 0;
        }

        ~semester() {
            delete[] x;
        }

        float sem_gpa() {
            for (int i = 0; i < n; i++)
                score += x[i].getinfo();
            gpa = score / tcredits;
            return gpa;
        }

        void display() {
            cout << "Name\tquiz1\tquiz2\tses1\tses2\tasn\tatd\tinternal\texternal\ttotal\tgrade\n";
            for (int i = 0; i < n; i++)
                x[i].display();
            cout << "GPA = " << gpa << endl;
        }
    };

    int m;
    semester* sem;
    float cgpa;
    int tot_credits;

    float score;

public:
    student() {
        int m;
        cout << "Enter the number of semester: ";
        cin >> m;
        semester sem[m];
        float cgpa;
        tot_credits = m * sem[0].getTcredits();
        float score = 0;
    }

    ~student() {
        delete[] sem;
    }

    float student_gpa() {
        for (int i = 0; i < m; i++) {
            cout << "For semester " << i + 1 << endl;
            score += sem[i].sem_gpa() * 15;
        }
        cgpa = score / tot_credits;
        return cgpa;
    }

    void display() {
        for (int i = 0; i < m; i++) {
            cout << "\t\t\t\t\tSemester" << i + 1 << "\n";
            sem[i].display();
        }
    }
};


int main() {
    int option;
    string username, password;

    cout << "Press '1' to Register\nPress '2' to Login\n";
    cin >> option;

    if (option == 1) {
        registerUser();
        cout << "\nLogin with the registered credentials.\n";
    } else if (option == 2) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (authenticateUser(username, password)) {
            cout << "\nLogin Successful!\n";

            student s;
            float cg = s.student_gpa();

            cout << "\n\n";
            cout << "\t\t\t\t\tStudent\n";
            s.display();
            cout << "CGPA = " << cg << "\n\n";
        } else {
            cout << "\nIncorrect Login Details\n";
        }
    }

    return 0;
}
