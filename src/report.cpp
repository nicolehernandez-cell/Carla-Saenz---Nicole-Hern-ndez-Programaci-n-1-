#include "report.h"
#include "production.h"
#include "utils.h"
#include <fstream>
#include <sstream>

using namespace std;

namespace Report {

bool generateHtmlReport(const std::string& filename) {
    if (Production::produccion.empty()) {
        Utils::printLine("[!] No hay datos para generar el reporte.");
        return false;
    }

    std::ofstream ofs(filename.c_str());
    if (!ofs.is_open()) {
        Utils::printLine("[X] No se pudo crear el archivo de reporte.");
        return false;
    }

    ofs << "<!doctype html>\n<html lang=\"es\">\n<head>\n<meta charset=\"utf-8\">\n";
    ofs << "<title>Reporte de Produccion Multimedia</title>\n";
    ofs << "<style>\n";
    ofs << "body{font-family: Arial, sans-serif; margin:20px;}\n";
    ofs << "table{border-collapse: collapse; width:100%;}\n";
    ofs << "th, td{border:1px solid #444; padding:6px; font-size:12px;}\n";
    ofs << "th{background:#eee;}\n";
    ofs << "</style>\n</head>\n<body>\n";
    ofs << "<h2>Reporte de Produccion Multimedia</h2>\n";
    ofs << "<p>Registros: " << Production::produccion.size() << "</p>\n";
    ofs << "<table>\n";
    ofs << "<tr><th>ID</th><th>Contenido</th><th>Tipo</th><th>Cliente</th><th>Fecha entrega</th><th>Estado</th><th>Observaciones</th></tr>\n";

    for (size_t i = 0; i < Production::produccion.size(); ++i) {
        Production::Content c = Production::produccion[i];
        // escape minimal
        std::string escContenido;
        for (size_t k = 0; k < c.contenido.size(); ++k) {
            char ch = c.contenido[k];
            if (ch == '&') escContenido += "&amp;";
            else if (ch == '<') escContenido += "&lt;";
            else if (ch == '>') escContenido += "&gt;";
            else if (ch == '"') escContenido += "&quot;";
            else escContenido += ch;
        }
        ofs << "<tr>";
        ofs << "<td>" << c.id << "</td>";
        ofs << "<td>" << escContenido << "</td>";
        ofs << "<td>" << c.tipo << "</td>";
        ofs << "<td>" << c.cliente << "</td>";
        ofs << "<td>" << c.fecha_entrega << "</td>";
        ofs << "<td>" << c.estado << "</td>";
        ofs << "<td>" << c.observaciones << "</td>";
        ofs << "</tr>\n";
    }

    ofs << "</table>\n";
    ofs << "<p>Generado por el sistema.</p>\n";
    ofs << "</body>\n</html>\n";
    ofs.close();

    Utils::printLine("[OK] Reporte HTML generado: " + filename);
    Utils::printLine("[TIP] Abra el HTML en un navegador y use 'Imprimir -> Guardar como PDF' para obtener PDF.");
    return true;
}

} // namespace Report
