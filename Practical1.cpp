#include<iostream>
using namespace std;

int main() {
    string str;
    cout << "Input String: ";
    cin >> str;

    int i = 0;  
    int n = str.length();


    while (i < n && str[i] == 'a') {
        i++;
    }

    
    for (int j = 0; j < 2; j++) {
        if (i < n && str[i] == 'b') {
            i++;
        } else {
            cout << "Invalid String" << endl;
            return 0; 
        }
    }
    if (i == n) {
        cout << "Valid String" << endl;
    } else {
        cout << "Invalid String" << endl;
    }

    return 0;
}