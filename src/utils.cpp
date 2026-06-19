#include "utils.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

namespace Utils {

    void printLine(const std::string& s) {
        std::cout << s << std::endl;
    }

    void pause() {
        std::cout << "\nPresione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void printTableHeader() {
        std::cout << "---------------------------------------------------------------------------------------------\n";
        std::cout << "| ID | Contenido                     | Tipo      | Cliente         | Fecha       | Estado            |\n";
        std::cout << "---------------------------------------------------------------------------------------------\n";
    }

    void printContentRow(const Production::Content& c) {
        // pad helper
        std::string pad;
        std::string cont = c.contenido;
        if (cont.size() > 27) cont = cont.substr(0, 27);
        pad = cont;
        while (pad.size() < 28) pad += ' ';

        std::string tipo = c.tipo;
        if (tipo.size() > 8) tipo = tipo.substr(0,8);
        while (tipo.size() < 9) tipo += ' ';

        std::string cliente = c.cliente;
        if (cliente.size() > 14) cliente = cliente.substr(0,14);
        while (cliente.size() < 15) cliente += ' ';

        std::string fecha = c.fecha_entrega;
        if (fecha.size() > 10) fecha = fecha.substr(0,10);
        while (fecha.size() < 11) fecha += ' ';

        std::string estado = c.estado;
        if (estado.size() > 16) estado = estado.substr(0,16);
        while (estado.size() < 17) estado += ' ';

        std::stringstream ss;
        ss << "| " << setw(2) << c.id << " | " << pad << " | " << tipo << " | " << cliente << " | " << fecha << " | " << estado << " |";
        std::cout << ss.str() << std::endl;
    }

    std::string toUpper(const std::string& s) {
        std::string out = s;
        for (size_t i = 0; i < out.size(); ++i) out[i] = (char)toupper((unsigned char)out[i]);
        return out;
    }

    bool validateDateFormat(const std::string& s) {
        if (s.size() != 10) return false;
        if (s[4] != '-' || s[7] != '-') return false;
        for (size_t i = 0; i < s.size(); ++i) {
            if (i == 4 || i == 7) continue;
            if (!isdigit((unsigned char)s[i])) return false;
        }
        int year = atoi(s.substr(0,4).c_str());
        int month = atoi(s.substr(5,2).c_str());
        int day = atoi(s.substr(8,2).c_str());
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        if (month == 2) {
            bool leap = (year%4==0 && year%100!=0) || (year%400==0);
            if (day > (leap ? 29 : 28)) return false;
        }
        if ((month==4||month==6||month==9||month==11) && day>30) return false;
        return true;
    }

    std::string intToString(int v) {
        std::stringstream ss; ss << v; return ss.str();
    }

    std::string longLongToString(long long v) {
        std::stringstream ss; ss << v; return ss.str();
    }

} // namespace Utils
