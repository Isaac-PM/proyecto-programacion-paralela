# Proyecto del curso Introducción a la Programación Paralela

- **Estudiantes:**
  - Emilio Chang Bustamante @ [emilio.chang.bustamante@est.una.ac.cr](mailto:emilio.chang.bustamante@est.una.ac.cr)
  - Isaac Fabián Palma Medina @ [isaac.palma.medina@est.una.ac.cr](mailto:isaac.palma.medina@est.una.ac.cr)
  - Karla Verónica Quirós Delgado @ [karla.quiros.delgado@est.una.ac.cr](mailto:karla.quiros.delgado@est.una.ac.cr)
- **Curso:** Introducción a la Programación Paralela, Escuela de Informática, Universidad Nacional
- **Docente:** Mag. Irene Hernández Ruiz

# Objetivo del proyecto

Convertir un programa secuencial a uno que utilice hilos, con la finalidad de estudiar las diferencias de rendimiento entre ambas metodologías.

# Programa a convertir

Contador de bytes escrito en C, con la finalidad de comparar el rendimiento entre contar de forma secuencial y de manera completamente paralela, esto para identificar si existe una correlación entre la cuenta de bytes de archivos maliciosos y archivos comunes. Pasos tentativos:

1. Conseguir un gran conjunto de archivos maliciosos y archivos comunes.
2. Contar los bytes de ambos conjuntos y documentar los resultados, escribiendo también el tiempo que duró el procesamiento de estos.
3. Convertir el programa a uno paralelo.
4. Procesar nuevamente los archivos.
5. Comparar si existe una correlación entre la secuencia de bytes de archivos maliciosos y aquellos que no, y si existe un beneficio al utilizar la versión paralela.