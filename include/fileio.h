#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include <fstream>
#include "production.h"

namespace FileIO {
    void saveToCSV(const std::string& filename);
    void loadFromCSV(const std::string& filename);

    Production::ResultadoComparacion mergeSortedFiles(const std::string& fileA, const std::string& fileB, const std::string& outFile);

    std::string contentToCSV(const Production::Content& c);
    Production::Content parseContentFromCSV(const std::string& line);
    void writeContentCSV(std::ofstream& ofs, const Production::Content& c);
}

#endif // FILEIO_H
