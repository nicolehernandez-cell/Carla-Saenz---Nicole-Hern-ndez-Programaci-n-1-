#include "production.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

namespace Production {

    std::vector<Content> produccion;

    void loadSampleData() {
        if (!produccion.empty()) return;
        Content c;
        c.id = 1; c.contenido = "VIDEO INSTITUCIONAL"; c.tipo = "VIDEO"; c.cliente = "UNIVALLE"; c.fecha_entrega = "2026-03-10"; c.estado = "EN PROCESO"; c.observaciones = "AJUSTE DE COLOR PENDIENTE"; produccion.push_back(c);
        c.id = 2; c.contenido = "ANIMACION PRODUCTO X"; c.tipo = "ANIMACION"; c.cliente = "KADILA PHARMA"; c.fecha_entrega = "2026-03-15"; c.estado = "PENDIENTE DE REVISION"; c.observaciones = "ERROR TECNICO EN AUDIO"; produccion.push_back(c);
        c.id = 3; c.contenido = "DISEÑO BANNER"; c.tipo = "IMAGEN"; c.cliente = "LABOMAC"; c.fecha_entrega = "2026-03-01"; c.estado = "ENTREGADO"; c.observaciones = "SIN INCONVENIENTES"; produccion.push_back(c);
        c.id = 4; c.contenido = "SPOT PROMOCIONAL"; c.tipo = "VIDEO"; c.cliente = "ACME CORP"; c.fecha_entrega = "2026-04-01"; c.estado = "EN PROCESO"; c.observaciones = "NO SE ESCUCHA"; produccion.push_back(c);
        c.id = 5; c.contenido = "GIF REDES"; c.tipo = "IMAGEN"; c.cliente = "STARTUP Y"; c.fecha_entrega = "2026-03-20"; c.estado = "ENTREGADO"; c.observaciones = "CALIDAD BAJA EN COMPRESION"; produccion.push_back(c);
        c.id = 6; c.contenido = "TUTORIAL PRODUCTO"; c.tipo = "VIDEO"; c.cliente = "UNIVALLE"; c.fecha_entrega = "2026-03-22"; c.estado = "PENDIENTE DE REVISION"; c.observaciones = "SIN INCONVENIENTES"; produccion.push_back(c);
        c.id = 7; c.contenido = "ANIMACION LOGO"; c.tipo = "ANIMACION"; c.cliente = "LABOMAC"; c.fecha_entrega = "2026-04-05"; c.estado = "EN PROCESO"; c.observaciones = "ERROR TECNICO EN AUDIO"; produccion.push_back(c);
        c.id = 8; c.contenido = "POSTER CAMPAÑA"; c.tipo = "IMAGEN"; c.cliente = "ACME CORP"; c.fecha_entrega = "2026-03-30"; c.estado = "ENTREGADO"; c.observaciones = "SIN INCONVENIENTES"; produccion.push_back(c);
        c.id = 9; c.contenido = "VIDEO TESTIMONIAL"; c.tipo = "VIDEO"; c.cliente = "CLIENTE Z"; c.fecha_entrega = "2026-04-10"; c.estado = "PENDIENTE DE REVISION"; c.observaciones = "NO SE ESCUCHA"; produccion.push_back(c);
        c.id = 10; c.contenido = "ANIMACION EXPLICATIVA"; c.tipo = "ANIMACION"; c.cliente = "CLIENTE A"; c.fecha_entrega = "2026-04-15"; c.estado = "EN PROCESO"; c.observaciones = "AJUSTE DE COLOR PENDIENTE"; produccion.push_back(c);
    }

    int nextId() {
        if (produccion.empty()) return 1;
        int maxId = 0;
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].id > maxId) maxId = produccion[i].id;
        }
        return maxId + 1;
    }

    void addContent(const Content& c) {
        produccion.push_back(c);
        Utils::printLine("[OK] Contenido agregado.");
    }

    bool modifyContent(int id) {
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].id == id) {
                Utils::printLine("Deje vacío para mantener valor actual.");
                string s;
                cout << "Nombre [" << produccion[i].contenido << "]: ";
                getline(cin, s); if (!s.empty()) produccion[i].contenido = Utils::toUpper(s);

                cout << "Tipo (VIDEO/ANIMACION/IMAGEN) [" << produccion[i].tipo << "]: ";
                getline(cin, s);
                if (!s.empty()) {
                    string upper = Utils::toUpper(s);
                    if (upper == "VIDEO" || upper == "ANIMACION" || upper == "IMAGEN") produccion[i].tipo = upper;
                    else Utils::printLine("[!] Tipo invalido, se mantiene el anterior.");
                }

                cout << "Cliente [" << produccion[i].cliente << "]: ";
                getline(cin, s); if (!s.empty()) produccion[i].cliente = Utils::toUpper(s);

                cout << "Fecha entrega (YYYY-MM-DD) [" << produccion[i].fecha_entrega << "]: ";
                getline(cin, s);
                if (!s.empty()) {
                    if (Utils::validateDateFormat(s)) produccion[i].fecha_entrega = s;
                    else Utils::printLine("[!] Formato de fecha invalido, se mantiene el anterior.");
                }

                cout << "Estado (EN PROCESO/ENTREGADO/PENDIENTE DE REVISION) [" << produccion[i].estado << "]: ";
                getline(cin, s);
                if (!s.empty()) {
                    string upper = Utils::toUpper(s);
                    if (upper == "EN PROCESO" || upper == "ENTREGADO" || upper == "PENDIENTE DE REVISION") produccion[i].estado = upper;
                    else Utils::printLine("[!] Estado invalido, se mantiene el anterior.");
                }

                cout << "Observaciones [" << produccion[i].observaciones << "]: ";
                getline(cin, s); if (!s.empty()) produccion[i].observaciones = Utils::toUpper(s);

                Utils::printLine("[OK] Contenido modificado.");
                return true;
            }
        }
        return false;
    }

    bool deleteContent(int id) {
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].id == id) {
                produccion.erase(produccion.begin() + i);
                Utils::printLine("[OK] Contenido eliminado.");
                return true;
            }
        }
        return false;
    }

    void showAll() {
        if (produccion.empty()) {
            Utils::printLine("[!] No hay contenidos registrados.");
            return;
        }
        // Ordenar copia por fecha de entrega (ascendente), desempate por id
        std::vector<Content> ordenado = produccion;
        for (size_t i = 0; i + 1 < ordenado.size(); ++i) {
            for (size_t j = i + 1; j < ordenado.size(); ++j) {
                if (ordenado[j].fecha_entrega < ordenado[i].fecha_entrega ||
                    (ordenado[j].fecha_entrega == ordenado[i].fecha_entrega && ordenado[j].id < ordenado[i].id)) {
                    Content tmp = ordenado[i]; ordenado[i] = ordenado[j]; ordenado[j] = tmp;
                }
            }
        }
        Utils::printTableHeader();
        for (size_t i = 0; i < ordenado.size(); ++i) {
            Utils::printContentRow(ordenado[i]);
        }
        stringstream ss; ss << "Total de contenidos: " << ordenado.size();
        Utils::printLine(ss.str());
    }

    std::vector<Content> filterByTipo(const string& tipo) {
        std::vector<Content> res;
        string t = Utils::toUpper(tipo);
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].tipo.find(t) != string::npos) res.push_back(produccion[i]);
        }
        return res;
    }

    std::vector<Content> filterByCliente(const string& cliente) {
        std::vector<Content> res;
        string t = Utils::toUpper(cliente);
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].cliente.find(t) != string::npos) res.push_back(produccion[i]);
        }
        return res;
    }

    std::vector<Content> filterByEstado(const string& estado) {
        std::vector<Content> res;
        string t = Utils::toUpper(estado);
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].estado.find(t) != string::npos) res.push_back(produccion[i]);
        }
        return res;
    }

    std::vector<Content> filterByFecha(const string& fecha) {
        std::vector<Content> res;
        for (size_t i = 0; i < produccion.size(); ++i) {
            if (produccion[i].fecha_entrega.find(fecha) != string::npos) res.push_back(produccion[i]);
        }
        return res;
    }

    ResultadoComparacion bubbleSortByIdOptimized() {
        ResultadoComparacion r; r.comparaciones = 0; r.intercambios = 0; r.tiempo_ms = 0;
        clock_t t0 = clock();

        bool swapped;
        size_t n = produccion.size();
        for (size_t i = 0; i < n; ++i) {
            swapped = false;
            for (size_t j = 0; j + 1 < n - i; ++j) {
                r.comparaciones++;
                if (produccion[j].id > produccion[j+1].id) {
                    Content tmp = produccion[j];
                    produccion[j] = produccion[j+1];
                    produccion[j+1] = tmp;
                    r.intercambios++;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }

        clock_t t1 = clock();
        r.tiempo_ms = (long long)((t1 - t0) * 1000 / CLOCKS_PER_SEC);
        Utils::printLine(" [OK] Ordenamiento por ID completado (Bubble Sort optimizado).");
        return r;
    }

    void sortByFechaEntrega(int &comparaciones) {
        comparaciones = 0;
        // simple sort usando comparator que incrementa comparaciones
        for (size_t i = 0; i + 1 < produccion.size(); ++i) {
            for (size_t j = i + 1; j < produccion.size(); ++j) {
                comparaciones++;
                if (produccion[j].fecha_entrega < produccion[i].fecha_entrega) {
                    Content tmp = produccion[i];
                    produccion[i] = produccion[j];
                    produccion[j] = tmp;
                }
            }
        }
        Utils::printLine(" [OK] Ordenamiento por fecha de entrega completado.");
    }

    void sortByFechaEntrega() {
        int dummy = 0;
        sortByFechaEntrega(dummy);
    }

    bool isSortedById() {
        for (size_t i = 1; i < produccion.size(); ++i) {
            if (produccion[i-1].id > produccion[i].id) return false;
        }
        return true;
    }

    ResultadoBusqueda sequentialSearchById(int id) {
        ResultadoBusqueda r; r.indice = -1; r.comparaciones = 0;
        for (size_t i = 0; i < produccion.size(); ++i) {
            r.comparaciones++;
            if (produccion[i].id == id) { r.indice = (int)i; break; }
        }
        return r;
    }

    ResultadoBusqueda binarySearchById(int id) {
        ResultadoBusqueda r; r.indice = -1; r.comparaciones = 0;
        if (!isSortedById()) {
            Utils::printLine("[!] El arreglo no está ordenado por ID. Ejecutando ordenamiento automático.");
            bubbleSortByIdOptimized();
        }
        int left = 0;
        int right = (int)produccion.size() - 1;
        while (left <= right) {
            r.comparaciones++;
            int mid = left + (right - left) / 2;
            if (produccion[mid].id == id) { r.indice = mid; break; }
            if (produccion[mid].id < id) left = mid + 1;
            else right = mid - 1;
        }
        return r;
    }

    std::vector<std::pair<Content, std::vector<std::string> > > detectAlerts() {
        std::vector<std::pair<Content, std::vector<std::string> > > alertas;
        std::vector<std::string> palabras;
        palabras.push_back("ERROR TECNICO");
        palabras.push_back("NO SE ESCUCHA");
        palabras.push_back("CALIDAD BAJA");
        palabras.push_back("PENDIENTE DE REVISION");
        for (size_t i = 0; i < produccion.size(); ++i) {
            std::vector<std::string> motivos;
            Content c = produccion[i];
            if (c.estado.find("PENDIENTE") != string::npos || c.estado.find("REVISION") != string::npos)
                motivos.push_back("Estado: PENDIENTE DE REVISION");
            for (size_t p = 0; p < palabras.size(); ++p) {
                if (c.observaciones.find(palabras[p]) != string::npos) motivos.push_back("Observacion contiene: " + palabras[p]);
            }
            if (!motivos.empty()) alertas.push_back(std::make_pair(c, motivos));
        }
        return alertas;
    }

    Content makeContentFromInput() {
        Content c;
        c.id = nextId();
        string s;
        cout << "Nombre del contenido: "; getline(cin, s); c.contenido = Utils::toUpper(s);

        while (1) {
            cout << "Tipo (VIDEO/ANIMACION/IMAGEN): "; getline(cin, s);
            string upper = Utils::toUpper(s);
            if (upper == "VIDEO" || upper == "ANIMACION" || upper == "IMAGEN") { c.tipo = upper; break; }
            Utils::printLine("[X] Tipo invalido. Opciones: VIDEO, ANIMACION, IMAGEN.");
        }

        cout << "Cliente o proyecto: "; getline(cin, s); c.cliente = Utils::toUpper(s);

        while (1) {
            cout << "Fecha de entrega (YYYY-MM-DD): "; getline(cin, s);
            if (Utils::validateDateFormat(s)) { c.fecha_entrega = s; break; }
            Utils::printLine("[X] Formato invalido. Use YYYY-MM-DD (ej: 2025-04-15).");
        }

        while (1) {
            cout << "Estado (EN PROCESO/ENTREGADO/PENDIENTE DE REVISION): "; getline(cin, s);
            string upper = Utils::toUpper(s);
            if (upper == "EN PROCESO" || upper == "ENTREGADO" || upper == "PENDIENTE DE REVISION") { c.estado = upper; break; }
            Utils::printLine("[X] Estado invalido. Opciones: EN PROCESO, ENTREGADO, PENDIENTE DE REVISION.");
        }

        cout << "Observaciones: "; getline(cin, s); c.observaciones = Utils::toUpper(s);
        return c;
    }

} // namespace Production
