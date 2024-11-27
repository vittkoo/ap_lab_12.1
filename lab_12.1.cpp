#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <Windows.h>

using namespace std;

void CreateBIN(const char* fname) {
    ofstream fout(fname, ios::binary);
    char ch;
    double value;
    do {
        cout << "Введіть дійсне число: ";
        cin >> value;
        fout.write((char*)&value, sizeof(value));
        cout << "Продовжити? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fout.close();
}

void PrintBIN(const char* fname) {
    ifstream fin(fname, ios::binary);
    double value;
    cout << "Вміст файлу: ";
    while (fin.read((char*)&value, sizeof(value))) {
        cout << value << " ";
    }
    cout << endl;
    fin.close();
}


bool IsExpValue(double value) {
    if (value <= 0) return false;
    return abs(log(value) - round(log(value))) < 1e-6; // перевірка, чи x ∈ N
}

// переписування значень, які можуть бути значеннями exp x
void ProcessBIN(const char* fname, const char* gname) {
    ifstream fin(fname, ios::binary);
    ofstream fout(gname, ios::binary);
    double value;
    while (fin.read((char*)&value, sizeof(value))) {
        if (IsExpValue(value)) {
            fout.write((char*)&value, sizeof(value));
        }
    }
    fin.close();
    fout.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[100], gname[100];

    cout << "Введіть ім'я початкового файлу: ";
    cin >> fname;
    CreateBIN(fname);

    PrintBIN(fname);

    cout << "Введіть ім'я файлу із результатом: ";
    cin >> gname;
    ProcessBIN(fname, gname);

    PrintBIN(gname);

    return 0;
}
