#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Reader.h"

using namespace std;

void Reader::fillVector(const string &str) {
    stringstream stream(str);
    size_t number;

    while (stream >> number) {
        vectorData.push_back(number);
        stream.ignore(1);
    }
    vectorData.erase(unique(vectorData.begin(), vectorData.end()), vectorData.end());
}

Reader::Reader(string &str, bool readFile) {
    if (readFile) {
        ifstream stream(str);

        if (!stream) {
            std::cerr << "No se encontro el archivo o hubo un problema al abrirlo\n";
            return;
        }
        stringstream buffer;
        buffer << stream.rdbuf();

        string file = buffer.str();

        replace(file.begin(), file.end(), '\n', ',');
        replace(file.begin(), file.end(), ' ', '0');
        replace(file.begin(), file.end(), 'x', '0');
        fillVector(file);
    } else {
        replace(str.begin(), str.end(), ' ', '0');
        replace(str.begin(), str.end(), 'x', '0');
        fillVector(str);
    }
}

size_t *Reader::getVectorData() {
    return vectorData.data();
}

void Reader::copyDataToVector(vector<size_t> *vector) {
    for (unsigned long long &i: vectorData) {
        vector->push_back(i);
    }
}

size_t Reader::getVectorSize() {
    return vectorData.size();
}
