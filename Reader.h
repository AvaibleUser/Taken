#ifndef TAKEN_READER_H
#define TAKEN_READER_H


#include <string>
#include <vector>
#include <fstream>


class Reader {
private:
    std::vector<size_t> vectorData;

    void fillVector(const std::string& str);

public:
    Reader(std::string &str, bool readFile);

    void copyDataToVector(std::vector<size_t> *vector);

    size_t *getVectorData();

    size_t getVectorSize();
};


#endif //TAKEN_READER_H
