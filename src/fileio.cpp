#include "fileio.h"
#include "utils.h"
#include <sstream>
#include <set>
#include <ctime>

namespace FileIO {

    std::string contentToCSV(const Production::Content& c) {
        std::stringstream ss;
        ss << c.id << "," << c.contenido << "," << c.tipo << "," << c.cliente << "," << c.fecha_entrega << "," << c.estado << "," << c.observaciones;
        return ss.str();
    }

    Production::Content parseContentFromCSV(const std::string& line) {
        Production::Content c;
        std::stringstream ss(line);
        std::string token;
        if (std::getline(ss, token, ',')) c.id = token.empty() ? 0 : atoi(token.c_str());
        if (std::getline(ss, c.contenido, ',')) {}
        if (std::getline(ss, c.tipo, ',')) {}
        if (std::getline(ss, c.cliente, ',')) {}
        if (std::getline(ss, c.fecha_entrega, ',')) {}
        if (std::getline(ss, c.estado, ',')) {}
        if (std::getline(ss, c.observaciones, ',')) {}
        return c;
    }

    void writeContentCSV(std::ofstream& ofs, const Production::Content& c) {
        ofs << contentToCSV(c) << "\n";
    }

    void saveToCSV(const std::string& filename) {
        std::ofstream ofs(filename.c_str());
        if (!ofs.is_open()) {
            Utils::printLine("[X] No se pudo abrir el archivo para guardar.");
            return;
        }
        for (size_t i = 0; i < Production::produccion.size(); ++i) {
            writeContentCSV(ofs, Production::produccion[i]);
        }
        ofs.close();
        Utils::printLine("[OK] Datos guardados en '" + filename + "'.");
    }

    void loadFromCSV(const std::string& filename) {
        std::ifstream ifs(filename.c_str());
        if (!ifs.is_open()) {
            Utils::printLine("[X] No se pudo abrir el archivo para cargar.");
            return;
        }
        Production::produccion.clear();
        std::string line;
        while (std::getline(ifs, line)) {
            if (!line.empty()) {
                Production::produccion.push_back(parseContentFromCSV(line));
            }
        }
        ifs.close();
        Utils::printLine("[OK] Datos cargados desde '" + filename + "'.");
    }

    Production::ResultadoComparacion mergeSortedFiles(const std::string& fileA, const std::string& fileB, const std::string& outFile) {
        Production::ResultadoComparacion r; r.comparaciones = 0; r.intercambios = 0; r.tiempo_ms = 0;
        clock_t t0 = clock();

        std::vector<Production::Content> A;
        std::vector<Production::Content> B;

        std::ifstream ifsA(fileA.c_str());
        std::string line;
        if (ifsA.is_open()) {
            while (std::getline(ifsA, line)) {
                if (!line.empty()) A.push_back(parseContentFromCSV(line));
            }
            ifsA.close();
        }

        std::ifstream ifsB(fileB.c_str());
        if (ifsB.is_open()) {
            while (std::getline(ifsB, line)) {
                if (!line.empty()) B.push_back(parseContentFromCSV(line));
            }
            ifsB.close();
        }

        std::ofstream ofs(outFile.c_str());
        if (!ofs.is_open()) {
            Utils::printLine("[X] No se pudo abrir el archivo de salida.");
            return r;
        }

        size_t i = 0, j = 0;
        std::set<int> seen;
        while (i < A.size() && j < B.size()) {
            r.comparaciones++;
            const Production::Content &ca = A[i];
            const Production::Content &cb = B[j];
            if (ca.id < cb.id) {
                if (!seen.count(ca.id)) { writeContentCSV(ofs, ca); seen.insert(ca.id); r.intercambios++; }
                ++i;
            } else if (cb.id < ca.id) {
                if (!seen.count(cb.id)) { writeContentCSV(ofs, cb); seen.insert(cb.id); r.intercambios++; }
                ++j;
            } else {
                if (!seen.count(ca.id)) { writeContentCSV(ofs, ca); seen.insert(ca.id); r.intercambios++; }
                ++i; ++j;
            }
        }
        while (i < A.size()) {
            r.comparaciones++;
            if (!seen.count(A[i].id)) { writeContentCSV(ofs, A[i]); seen.insert(A[i].id); r.intercambios++; }
            ++i;
        }
        while (j < B.size()) {
            r.comparaciones++;
            if (!seen.count(B[j].id)) { writeContentCSV(ofs, B[j]); seen.insert(B[j].id); r.intercambios++; }
            ++j;
        }

        ofs.close();
        clock_t t1 = clock();
        r.tiempo_ms = (long long)((t1 - t0) * 1000 / CLOCKS_PER_SEC);

        Utils::printLine("[OK] Intercalación completada en '" + outFile + "'.");
        return r;
    }

} // namespace FileIO
