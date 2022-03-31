#include <string>
#include <iostream>
#include <limits>


using namespace std;

size_t getInteger(const string &msg, const size_t &min, const size_t &max) {
    size_t value;

    cout << msg;
    cin >> value;

    while (value < min || max < value) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ingrese un numero valido.\n" << msg;
        cin >> value;
    }

    return value;
}
