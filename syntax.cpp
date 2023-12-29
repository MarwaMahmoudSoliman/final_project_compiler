#include <iostream>
#include <conio.h>
using namespace std;

int j = 0;
char m[10];

void B();
void S();
void A();
void error();

int main() {
    cout << "the grammar is " << endl;
    cout << "S -> aBb/ccA" << endl;
    cout << "A -> b/c" << endl;
    cout << "B -> a/b" << endl;
    cout << "Enter the string" << endl;
    cin >> m;

    S();
    
    if (m[j] == '\0')
        cout << "this is String is valid" << endl;
    else
        cout << "this is String is invalid" << endl;
    
    getch();
    return 0;
}

void S() {
    if (m[j] == 'a') {
        j++;
        B();
        if (m[j] == 'b')
            j++;
        else
            error();
    }
    else if (m[j] == 'c') {
        j++;
        if (m[j] == 'c') {
            j++;
            A();
        }
        else
            error();
    }
}

void A() {
    if (m[j] == 'b' || m[j] == 'c')
        j++;
    else
        error();
}

void B() {
    if (m[j] == 'a' || m[j] == 'b')
        j++;
    else
        error();
}

void error() {
    cout << "String is invalid" << endl;
    getch();
}
