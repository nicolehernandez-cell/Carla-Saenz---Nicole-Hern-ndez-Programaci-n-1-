#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "production.h"

namespace Utils {
    void printLine(const std::string& s);
    void pause();
    void printTableHeader();
    void printContentRow(const Production::Content& c);
    std::string toUpper(const std::string& s);
    bool validateDateFormat(const std::string& s); // YYYY-MM-DD
    std::string intToString(int v);
    std::string longLongToString(long long v);
}

#endif // UTILS_H
