#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
private:
    string name;
    int age;
    double averageScore;

public:
    
    Student() : name(""), age(0), averageScore(0.0) {}

    
    void writeToFile(const string& fileName) {
        ofstream outFile(fileName, ios::binary);
        if (!outFile) {
            cerr << "Error" << endl;
            return;
        }

        
        size_t nameLength = name.size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(name.c_str(), nameLength);
        outFile.write(reinterpret_cast<const char*>(&age), sizeof(age));
        outFile.write(reinterpret_cast<const char*>(&averageScore), sizeof(averageScore));

        outFile.close();
        cout << "Done" << endl;
    }

    
    void readFromFile(const string& fileName) {
        ifstream inFile(fileName, ios::binary);
        if (!inFile) {
            cerr << "Error" << endl;
            return;
        }

       
        size_t nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        name.resize(nameLength);
        inFile.read(&name[0], nameLength);
        inFile.read(reinterpret_cast<char*>(&age), sizeof(age));
        inFile.read(reinterpret_cast<char*>(&averageScore), sizeof(averageScore));

        inFile.close();

        
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Average: " << averageScore << endl;
    }

    
    void inputStudentInfo() {
        cout << "Name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;
        cout << "Average: ";
        cin >> averageScore;
    }
};

int main() {
    Student student;

    student.inputStudentInfo();

    
    string fileName = "student.bin";
    student.writeToFile(fileName);

    
    cout << "\nRead:" << endl;
    student.readFromFile(fileName);

    return 0;
}
