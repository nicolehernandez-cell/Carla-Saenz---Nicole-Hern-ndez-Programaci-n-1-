# Proyecto Final - Programación 1: Gestión de Contenido Multimedia

## Informe de Proyecto

**Programadores:** 
- Carla Saenz
- Nicole Hernandez

---

## 1. Descripción del Proyecto
Este proyecto es un sistema de gestión para producciones multimedia, desarrollado en C++. Permite a los usuarios registrar, visualizar, modificar, eliminar, buscar y ordenar contenidos. Además, incluye funcionalidades de persistencia de datos (lectura y escritura en archivos CSV), generación de reportes en HTML, y análisis de eficiencia algorítmica (comparando algoritmos de ordenamiento como Bubble Sort y Merge).

## 2. Análisis del Código Actual
El código actual está estructurado de manera modular, separando la lógica en distintos archivos (`main.cpp`, `src/` e `include/`), lo cual es una excelente práctica para mantener el proyecto organizado. Se identifican módulos clave como:
- `production.h/.cpp`: Lógica principal y definición de estructuras de datos.
- `fileio.h/.cpp`: Manejo de archivos y persistencia (CSV).
- `utils.h/.cpp`: Funciones utilitarias y algoritmos de ordenamiento/búsqueda.
- `report.h/.cpp`: Generación de reportes en HTML.

## 3. ¿Cómo hubiera implementado el código? (Propuestas de Mejora)
Si bien la implementación actual cumple con los requerimientos (especialmente los académicos, como implementar métodos de ordenamiento y manejo de archivos), a nivel profesional o escalable hubiera aplicado las siguientes prácticas:

### A. Arquitectura y Patrones de Diseño
- **Separación de Responsabilidades (MVC):** Hubiera implementado un patrón Modelo-Vista-Controlador más estricto. Actualmente, la interfaz de consola (`cout`/`cin`) puede estar mezclada con la lógica de negocio. Separaría por completo la "Vista" (menús y entradas de usuario) del "Controlador" (gestión de la producción).
- **Uso de Programación Orientada a Objetos Avanzada:** En lugar de structs planos, usaría clases con encapsulamiento, constructores robustos y polimorfismo si hay diferentes tipos de contenido multimedia (ej. `Video`, `Audio`, `Imagen` heredando de una clase base `Contenido`).

### B. Gestión de Datos y Persistencia
- **Uso de JSON o Bases de Datos:** En lugar de archivos CSV manuales, utilizaría una librería como `nlohmann/json` para C++ o una base de datos ligera como SQLite. Esto evita problemas de parseo (por ejemplo, si un título contiene comas).
- **Validación de Entradas:** Implementaría un sistema robusto de validación usando expresiones regulares (`std::regex`) para asegurar que fechas, correos o IDs tengan el formato correcto antes de procesarlos.

### C. Algoritmos y Rendimiento
- **Algoritmos Estándar:** Aunque el proyecto requiere implementar *Bubble Sort* y *Merge*, en un entorno real utilizaría exclusivamente la librería estándar `<algorithm>` (como `std::sort` y `std::lower_bound`), ya que están altamente optimizados.
- **Templates:** Hubiera programado los métodos de ordenamiento y búsqueda usando *Templates* (`template <typename T>`) para que sean genéricos y reutilizables con cualquier otra estructura de datos en el futuro, no solo limitados a `Production::Content`.

### D. Manejo de Errores
- **Excepciones (`try-catch`):** Reemplazaría los simples mensajes de error o retornos por defecto por un manejo de excepciones formal (`std::runtime_error`), especialmente en las operaciones de lectura/escritura de archivos (`fileio`) y asignaciones de memoria.

---

Este README sirve como evidencia del trabajo realizado y como base para futuras mejoras del sistema.