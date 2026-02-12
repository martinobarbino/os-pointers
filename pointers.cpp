// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    student.f_name = new char[128];
    student.l_name = new char[128];
    student.grades = new double[134217728];

    double average;

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);
    std::cout << "\n";

    for (int i = 0; i < student.n_assignments; i++) {
        student.grades[i] = promptDouble("Please enter grade for assignment " + std::to_string(i) + ": ",
                                            0.0, 1000.0);
    }
    
    // Call `CalculateStudentAverage(???, ???)`
    // Output `average`

    std::string studentInfo = "\nStudent: " + std::string(student.f_name) + " " + std::string(student.l_name) + " [" + std::to_string(student.id) + "]";
    std::cout << studentInfo;
    
    calculateStudentAverage(&student, &average);
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "\n  Average grade: " << average << std::endl;

    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    std::string inputStr;
    int userInput;
    while (true) {
        std::cout << message;
        if (std::cin >> inputStr) {
            bool isNumeric = true;
            size_t start = 0;
            if (inputStr.length() > 0 && inputStr[0] == '-') {
                start = 1;
                if (inputStr.length() == 1) isNumeric = false;
            }

            for (size_t i = start; i < inputStr.length(); i++) {
                if (!isdigit(inputStr[i])) {
                    isNumeric = false;
                    break;
                }
            }

            if (isNumeric) {
                try {
                    userInput = std::stoi(inputStr);
                    if (userInput >= min && userInput <= max) {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        return userInput;
                    }
                } catch (...) {}
            }
        } else {
            std::cin.clear();
        }

        std::cout << "Sorry, I cannot understand your answer\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    std::string inputStr;
    double userInput;
    while (true) {
        std::cout << message;
        if (std::cin >> inputStr) {
            bool isNumeric = true;
            bool hasDecimal = false;
            size_t start = 0;
            if (inputStr.length() > 0 && inputStr[0] == '-') {
                start = 1;
                if (inputStr.length() == 1) isNumeric = false;
            }

            for (size_t i = start; i < inputStr.length(); i++) {
                if (inputStr[i] == '.') {
                    if (hasDecimal) {
                        isNumeric = false;
                        break;
                    }
                    hasDecimal = true;
                } else if (!isdigit(inputStr[i])) {
                    isNumeric = false;
                    break;
                }
            }
            if (inputStr == "." || inputStr == "-.") isNumeric = false;

            if (isNumeric) {
                try {
                    userInput = std::stod(inputStr);
                    if (userInput >= min && userInput <= max) {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        return userInput;
                    }
                } catch (...) {}
            }
        } else {
            std::cin.clear();
        }

        std::cout << "Sorry, I cannot understand your answer\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    Student *student = (Student *) object;

    double total = 0.0;

    for (int i = 0; i < student->n_assignments; i++) {
        total += student->grades[i];
    }

    *avg = (total / student->n_assignments);
}
 