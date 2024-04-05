Aplicación de Multiplicación de Matrices
Esta aplicación implementa la multiplicación de matrices cuadradas utilizando hilos en C. La idea principal es construir paso a paso la implementación para hacer uso de la biblioteca PTHREAD.

Requisitos
GCC para la compilación
Biblioteca PTHREAD para el manejo de hilos
Ejecución
Para ejecutar el programa, primero debe compilarlo con GCC:

Luego, puede ejecutar el programa con:

Implementación
La implementación sigue los siguientes pasos:

Reserva de memoria: Se reserva memoria para las matrices utilizando la constante RESERVA.

Creación de punteros para matrices de tipo doble: Se crean punteros para las matrices que se van a multiplicar.

Asignación de memoria: Se asigna la memoria reservada a los punteros de las matrices.

Ingreso de argumentos de entrada: Se ingresan los argumentos de entrada, que son la dimensión de la matriz y el número de hilos.

Inicialización de matrices: Se inicializan las matrices con los valores deseados.

Función para inicializar las matrices: Se utiliza una función para inicializar las matrices.

Función para imprimir las matrices: Se utiliza una función para imprimir las matrices.

Función para multiplicar las matrices: Se utiliza una función para multiplicar las matrices.

Verificación del resultado: Se verifica que el resultado de la multiplicación sea correcto.

La implementación utiliza la biblioteca PTHREAD para el manejo de hilos, lo que permite realizar la multiplicación de matrices de manera concurrente, mejorando el rendimiento del programa.

Código
El código incluye las bibliotecas estándar de C, pthread para el manejo de hilos y sys/time para medir el tiempo. Se define una constante RESERVA para reservar memoria para las matrices.
