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

Contador de bytes escrito en C, para de comparar el rendimiento entre contar de forma secuencial y de manera completamente paralela, esto para identificar si existe una correlación entre la cuenta de bytes de archivos maliciosos y archivos comunes.

# Documentación (Borrar, pasar a un cuaderno de R o Python)

1. Próposito del programa.
   1. Explicar que quizás existe una correlación entre la ocurrencia de bytes en un determinado archivo y si este es malicioso o no.
2. Explicación del programa (versión secuencial).
3. Explicación del programa (versión paralela).
4. Comparación de las cuentas de bytes.
   1. Explicar el procedimiento de conteo de bytes: 50 archivos maliciosos y 50 archivos comunes, aproximadamente del mismo tamaño.
   2. Indicar el origen de los archivos.
   3. Comparar los resultados obtenidos:
      1. Gráfico de barras verticales de dos variables, eje X serían los bytes y el eje Y la cantidad de veces que se repite, ejemplo: https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.lifeder.com%2Fwp-content%2Fuploads%2F2020%2F03%2Fgr%25C3%25A1fico-de-barras-2.jpg&f=1&nofb=1&ipt=9e6e9d3de1435ee45cc1e0d8a54b61581733fbdf4b2334062da9765a71652b96&ipo=images
      2. Indicar si existe una correlación entre los bytes y si el archivo es malicioso o no.
5. Comparación de rendimiento.
   1. Analizar el rendimiento de la versión secuencial y paralela.
      1. Cada archivo se procesó 3 veces y se sacó un promedio de tiempo de procesamiento.
      2. Gráfico de líneas, eje X sería la cantidad de hilos y el eje Y el tiempo de procesamiento, ejemplo: https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimages.edrawmax.com%2Fimages%2Fknowledge%2Fline-graph-5-example-2.jpg&f=1&nofb=1&ipt=8fe0ff9364049afd21eb607c264bdc6c69bc7f523261386db17e8daed695809c&ipo=images
6. Cierre.