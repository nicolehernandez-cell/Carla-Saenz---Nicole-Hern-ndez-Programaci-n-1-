#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>
#include <vector>

namespace Production {

    struct Content {
        int id;
        std::string contenido;
        std::string tipo;
        std::string cliente;
        std::string fecha_entrega;
        std::string estado;
        std::string observaciones;
    };


    extern std::vector<Content> produccion;

    struct ResultadoBusqueda {
        int indice;
        int comparaciones;
    };

    struct ResultadoComparacion {
        int comparaciones;
        int intercambios;
        long long tiempo_ms;
    };

    void loadSampleData();
    int nextId();
    void addContent(const Content& c);
    bool modifyContent(int id);
    bool deleteContent(int id);
    void showAll();

    std::vector<Content> filterByTipo(const std::string& tipo);
    std::vector<Content> filterByCliente(const std::string& cliente);
    std::vector<Content> filterByEstado(const std::string& estado);
    std::vector<Content> filterByFecha(const std::string& fecha);

    ResultadoComparacion bubbleSortByIdOptimized();
    void sortByFechaEntrega(int &comparaciones);
    void sortByFechaEntrega();

    bool isSortedById();

    ResultadoBusqueda sequentialSearchById(int id);
    ResultadoBusqueda binarySearchById(int id);

    std::vector<std::pair<Content, std::vector<std::string> > > detectAlerts();
    Content makeContentFromInput();
}

#endif // PRODUCTION_H
