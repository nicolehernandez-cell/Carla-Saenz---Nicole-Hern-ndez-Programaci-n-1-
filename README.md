Proyecto Final - Programación 1: Gestión de Contenido Multimedia

Informe de Proyecto

Programadores:

Carla Antonella Saenz
Nicole Mariana Hernandez
Asignatura: Programación 1
Fecha de entrega: 19/06/2026

1. Introducción

El presente proyecto constituye la culminación práctica de los conceptos fundamentales de programación estructurada y orientada a objetos vistos a lo largo del curso. Se ha desarrollado un sistema de gestión de contenidos multimedia en C++ que permite administrar de forma eficiente un catálogo de producciones audiovisuales, aplicando técnicas de persistencia de datos, algoritmos de búsqueda y ordenamiento, así como generación de reportes en formato HTML.

El objetivo principal es ofrecer una herramienta funcional que simule un entorno real de gestión de información, donde el usuario pueda realizar operaciones CRUD (Crear, Leer, Actualizar, Eliminar) sobre un conjunto de registros, y además obtener análisis de rendimiento de los algoritmos implementados. Todo ello bajo un esquema modular que facilita el mantenimiento y la escalabilidad del código.

2. Descripción del Proyecto

El sistema está diseñado para gestionar producciones multimedia, tales como películas, series, documentales, videos musicales, entre otros. Cada producción se representa mediante una estructura de datos que contiene los siguientes campos:

ID: Identificador único numérico.
Título: Cadena de caracteres.
Director: Nombre del director.
Año de lanzamiento: Número entero.
Género: Categoría (p. ej., drama, comedia, acción).
Duración: En minutos (entero).
Calificación: Valor numérico (por ejemplo, de 1 a 10).
El sistema permite:

Registrar nuevas producciones.
Visualizar el listado completo de contenidos.
Modificar los datos de una producción existente.
Eliminar una producción mediante su ID.
Buscar producciones por título o por director (búsqueda secuencial).
Ordenar el catálogo por año, duración o calificación, utilizando dos algoritmos de ordenamiento distintos (Bubble Sort y Merge Sort) y comparando su eficiencia.
Persistencia de datos: lectura y escritura desde/hacia archivos CSV.
Generación de reportes en HTML con el listado completo y estadísticas básicas.
Análisis de tiempos de ejecución de los algoritmos de ordenamiento para diferentes tamaños de datos.
El proyecto se ha desarrollado en C++ utilizando el estándar C++11, y se ha estructurado en múltiples archivos fuente y cabeceras para mantener una clara separación de responsabilidades.

3. Estructura del Código y Módulos

El código fuente se organiza de la siguiente manera:

Archivo	Descripción
main.cpp	Contiene el bucle principal del programa, el menú interactivo y la lógica de control que orquesta las llamadas a los distintos módulos.
include/production.h / src/production.cpp	Define la estructura Production::Content (o similar) y las funciones para manejar el vector de producciones (alta, baja, modificación, etc.).
include/fileio.h / src/fileio.cpp	Implementa la lectura y escritura de archivos CSV, así como la carga inicial de datos y el guardado automático al salir.
include/utils.h / src/utils.cpp	Contiene las funciones de ordenamiento (Bubble Sort, Merge Sort) y búsqueda secuencial, junto con utilidades auxiliares (comparación, intercambio, etc.).
include/report.h / src/report.cpp	Genera un reporte en formato HTML a partir de los datos actuales, incluyendo una tabla con todas las producciones y un resumen estadístico.
Esta estructura modular permite que cada componente sea probado de forma independiente y facilita la colaboración entre los programadores, ya que cada uno puede trabajar en un módulo sin afectar a los demás.

4. Análisis del Código Actual

4.1. Fortalezas

Modularidad: La separación en archivos de cabecera e implementación es adecuada y sigue las buenas prácticas de C++.
Persistencia: El manejo de archivos CSV permite conservar los datos entre ejecuciones, lo cual es esencial para cualquier sistema real.
Algoritmos implementados: Se incluyen dos métodos de ordenamiento (Bubble Sort y Merge Sort) y búsqueda secuencial, cumpliendo con los requisitos académicos.
Generación de reportes: La capacidad de exportar a HTML añade valor práctico al proyecto.
Manejo de menús: La interfaz por consola es clara y guía al usuario paso a paso.
4.2. Áreas de Mejora Detectadas

A pesar de cumplir con los objetivos planteados, durante la revisión del código se han identificado ciertos aspectos que podrían optimizarse para lograr un sistema más robusto, profesional y escalable:

Mezcla de lógica de presentación y negocio: El menú y la entrada/salida de datos están integrados con las funciones de gestión, lo que dificulta posibles cambios de interfaz (por ejemplo, pasar a una interfaz gráfica).
Uso de estructuras planas (struct) sin encapsulamiento: No se aprovechan las ventajas de la programación orientada a objetos (constructores, métodos, herencia, polimorfismo). Si en el futuro se añaden distintos tipos de contenido (video, audio, imagen), la estructura actual requeriría modificaciones extensas.
Manejo de errores básico: Las validaciones son limitadas y, en caso de fallos (por ejemplo, archivo corrupto o entrada incorrecta), el programa podría comportarse de manera impredecible.
Dependencia del formato CSV: El uso de comas como separadores puede causar problemas si algún campo contiene comas internas (p. ej., títulos con comas). Además, no se manejan correctamente caracteres especiales o saltos de línea.
Falta de genéricos: Los algoritmos de ordenamiento y búsqueda están escritos específicamente para el tipo Production::Content, lo que impide su reutilización con otras estructuras de datos.
Ausencia de pruebas automáticas: No se han implementado pruebas unitarias que verifiquen el correcto funcionamiento de cada módulo.
5. Propuestas de Mejora (Implementación Ideal)

Con base en el análisis anterior, se proponen las siguientes mejoras, que representan cómo se abordaría el proyecto desde una perspectiva profesional y con miras a la evolución del sistema.

5.1. Arquitectura y Patrones de Diseño

Separación de Responsabilidades (MVC)
Se implementaría un patrón Modelo-Vista-Controlador para desacoplar completamente la interfaz de usuario de la lógica de negocio y el acceso a datos.

Modelo: Representaría los datos y las reglas de negocio (clases Contenido, Catalogo, etc.).
Vista: Encapsularía toda la interacción con el usuario (menús, mensajes, entrada/salida por consola). Si en el futuro se desea migrar a una GUI, solo se reemplazaría esta capa.
Controlador: Orquestaría las peticiones del usuario, actuando como intermediario entre la Vista y el Modelo.
Programación Orientada a Objetos Avanzada
Se definiría una clase base abstracta Contenido con atributos comunes (ID, título, director, año) y métodos virtuales puros (por ejemplo, mostrarDetalles()). A partir de ella se derivarían clases como Pelicula, Serie, Documental, cada una con sus atributos específicos (número de episodios, temporadas, etc.). Esto permite polimorfismo y facilita la extensión sin modificar el código existente.

5.2. Gestión de Datos y Persistencia

Uso de JSON o Base de Datos SQLite
En lugar de CSV, se emplearía un formato más estructurado como JSON (con la librería nlohmann/json) o una base de datos ligera SQLite. Estas opciones evitan problemas de parseo, permiten anidar estructuras y son ampliamente soportadas en entornos de producción.

Validación de Entradas Robusta
Se implementarían validaciones con expresiones regulares (std::regex) para verificar formatos de correo electrónico, fechas, números de teléfono, etc., según los campos que se manejen. Además, se usarían bucles de repetición hasta que el usuario ingrese un valor válido, con mensajes de error claros.

5.3. Algoritmos y Rendimiento

Uso de la STL
Aunque el proyecto exige implementar Bubble Sort y Merge Sort con fines didácticos, en un entorno real se utilizarían los algoritmos de la biblioteca estándar (std::sort, std::stable_sort, std::lower_bound) que están altamente optimizados y probados. Se podría mantener la implementación propia para fines de comparación, pero delegar en la STL para las operaciones habituales.

Algoritmos Genéricos con Templates
Se reescribirían las funciones de ordenamiento y búsqueda usando plantillas (template <typename T>). De este modo, el mismo código serviría para ordenar vectores de cualquier tipo (enteros, cadenas, objetos Contenido), siempre que se defina un operador de comparación adecuado.

5.4. Manejo de Errores y Excepciones

Se implementaría un manejo de excepciones estructurado con try-catch para capturar errores de archivo (archivo no encontrado, permisos, formato incorrecto), errores de memoria y entradas inválidas. Cada módulo lanzaría excepciones específicas (derivadas de std::runtime_error) que serían manejadas en el nivel superior, mostrando mensajes adecuados al usuario y manteniendo la integridad del programa.

5.5. Pruebas y Calidad de Código

Pruebas Unitarias
Se incorporaría un marco de pruebas como Google Test o Catch2 para escribir pruebas automatizadas de cada función. Esto asegura que los cambios futuros no rompan la funcionalidad existente y facilita la detección temprana de errores.

Documentación del Código
Se añadirían comentarios estilo Doxygen para generar documentación automática, explicando el propósito de cada clase, método y parámetro.

Control de Versiones
Se utilizaría Git con un flujo de trabajo basado en ramas (feature branches) y revisiones de código (pull requests) para garantizar la calidad colaborativa.

6. Consideraciones sobre Pruebas y Calidad

Para garantizar el correcto funcionamiento del sistema, se plantean los siguientes escenarios de prueba:

ID	Prueba	Resultado Esperado
P1	Registrar una producción con datos válidos	La producción se añade al vector y se guarda en el archivo.
P2	Intentar registrar una producción con año negativo	El sistema rechaza la entrada y solicita un año válido.
P3	Buscar por título existente	Se muestra la producción encontrada.
P4	Buscar por título inexistente	Se informa que no se encontró ninguna producción.
P5	Ordenar por año usando Bubble Sort	El vector queda ordenado de menor a mayor año.
P6	Ordenar por duración usando Merge Sort	El vector queda ordenado de menor a mayor duración.
P7	Generar reporte HTML	Se crea un archivo .html con la tabla y estadísticas.
P8	Cargar datos desde un CSV corrupto	El programa maneja la excepción y carga un conjunto vacío, notificando al usuario.
P9	Medir tiempos de ordenamiento	Se muestran los tiempos para diferentes tamaños de datos (100, 1000, 5000).
Además, se realizarían pruebas de rendimiento para comparar la eficiencia de Bubble Sort vs. Merge Sort, y se documentarían los resultados en el informe.

7. Conclusiones

El proyecto "Gestión de Contenido Multimedia" ha sido una excelente oportunidad para aplicar los conceptos fundamentales de programación en C++. La implementación actual cumple con todos los requisitos funcionales establecidos, demostrando competencia en:

Manejo de estructuras de datos dinámicas (vectores).
Operaciones CRUD.
Algoritmos de ordenamiento y búsqueda.
Persistencia mediante archivos CSV.
Generación de reportes en HTML.
Las propuestas de mejora presentadas reflejan una visión más amplia del desarrollo de software, enfocada en la mantenibilidad, escalabilidad y robustez. Adoptar estas prácticas no solo enriquecería el proyecto académico, sino que también prepararía a los programadores para enfrentar desafíos en entornos profesionales reales.

En definitiva, el equipo ha logrado construir una base sólida que puede ser extendida y mejorada progresivamente, aplicando los conocimientos adquiridos a lo largo del curso.

8. Anexos

Código fuente completo: disponible en el repositorio del proyecto.
Ejemplos de archivos CSV y HTML generados.
Capturas de pantalla de la ejecución.
Tablas comparativas de tiempos de ordenamiento.
