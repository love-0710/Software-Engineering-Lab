#include <iostream>
#include <vector>
#include <string>

class Student {
private:
    std::string name;
    int age;
    std::string gender;
    int room_number;
    std::string username;
    std::string password;

public:
    Student(std::string name, int age, std::string gender, int room_number, std::string username, std::string password)
        : name(name), age(age), gender(gender), room_number(room_number), username(username), password(password) {}

    void display_info() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Gender: " << gender << std::endl;
        std::cout << "Room Number: " << room_number << std::endl;
    }

    void update_profile(std::string name, int age, std::string gender, int room_number) {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->room_number = room_number;
    }

    void change_password(std::string new_password) {
        password = new_password;
    }

    std::string get_username() const {
        return username;
    }

    std::string get_password() const {
        return password;
    }
};

Student* login(const std::vector<Student>& students) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (auto& student : students) {
        if (student.get_username() == username && student.get_password() == password) {
            return new Student(student);
        }
    }

    std::cout << "Invalid username or password. Please try again." << std::endl;
    return nullptr;
}

int main() {
    std::cout << "Hostel Management System" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::vector<Student> students;

    while (true) {
        std::cout << "\n1. Add Student" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name, gender, username, password;
            int age, room_number;

            std::cout << "Enter student name: ";
            std::cin >> name;
            std::cout << "Enter student age: ";
            std::cin >> age;
            std::cout << "Enter student gender: ";
            std::cin >> gender;
            std::cout << "Enter room number: ";
            std::cin >> room_number;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            students.emplace_back(name, age, gender, room_number, username, password);
            std::cout << "\nStudent added successfully." << std::endl;
        } else if (choice == 2) {
            Student* logged_in_student = login(students);
            if (logged_in_student != nullptr) {
                while (true) {
                    std::cout << "\n1. Display Profile" << std::endl;
                    std::cout << "2. Update Profile" << std::endl;
                    std::cout << "3. Change Password" << std::endl;
                    std::cout << "4. Logout" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;

                    if (choice == 1) {
                        logged_in_student->display_info();
                    } else if (choice == 2) {
                        std::string name, gender;
                        int age, room_number;

                        std::cout << "Enter new name: ";
                        std::cin >> name;
                        std::cout << "Enter new age: ";
                        std::cin >> age;
                        std::cout << "Enter new gender: ";
                        std::cin >> gender;
                        std::cout << "Enter new room number: ";
                        std::cin >> room_number;

                        logged_in_student->update_profile(name, age, gender, room_number);
                        std::cout << "\nProfile updated successfully." << std::endl;
                    } else if (choice == 3) {
                        std::string new_password;
                        std::cout << "Enter new password: ";
                        std::cin >> new_password;

                        logged_in_student->change_password(new_password);
                        std::cout << "\nPassword changed successfully." << std::endl;
                    } else if (choice == 4) {
                        delete logged_in_student;
                        break;
                    } else {
                        std::cout << "Invalid choice. Please try again." << std::endl;
                    }
                }
            } else {
                std::cout << "Login failed." << std::endl;
            }
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
