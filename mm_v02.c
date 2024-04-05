/*****************************************
Para su debida ejuecucion:gcc mv_v01.c 
./a.out

* Fecha: 04-04-24
* Autor: Carlos Esteban Mejia Coy
* Materia: Sistemas Operativos
* Tema: Concurrencia
* Objetivo: Hacer una metodologia para la implementacion de la multiplicacion de matrices.
* La idea principal es construir paso a paso la 
* implementacion para hacer uso de la biblioteca PTHREAD se 
* implementa el *algoritmo clasico de multiplicacion de 
* matrices para matrices cuadradas es decir, la dimension de 
* filas es igual a al *dimension de columnas. Acontinucaion se decriben los pasos:
*     - Reserva de memoria
*     - Creacion de punteros para matrices de tipo doble
*     - Asignacion de memoria
*     - Ingreso de argumentos de netrada(Dimension matrriz, numero de hilos)
*     - Inicializar matrices
*     - Funcion para inicializar las matrices 
*     - Funcion para imprimir las matrices
*     - Funcion para multiplicar las matrices
*     - Se verifica el resultado

*****************************************/

// Incluimos las libreras estandar de C, pthread para el manejo de hilos y sys/time para medir el tiempo
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Definimos una constante RESERVA para reservar memoria para las matrices
#define RESERVA (1024*128*64*8)

// Reserva de memoria estatica para las matrices
static double MEM_CHUNK[RESERVA];

// Funcin para inicializar las matrices con valores aleatorios
void iniMatrices(int n, double *m1, double *m2, double *m3){
  for (int i = 0; i < n*n; i++){
    m1[i] = i*1.1; // Inicializamos la matriz 1
    m2[i] = i*2.2; // Inicializamos la matriz 2
    m3[i] = i;     // Inicializamos la matriz 3
  }
};

// Funcion para imprimir las matrices en pantalla
void impreMatrices(int n, double *m1){
  if(n < 9){
    for (int i = 0; i < n*n; i++){
      if(i%n == 0) printf("\n"); // Imprimimos un salto de linea cada n elementos
      printf(" %f", m1[i]); // Imprimimos el elemento actual
    }
    printf("\n###########################################\n ");
  }else{
    printf("\n###########################################\n ");
  }
};

// Estructura para almacenar los datos necesarios para cada hilo
struct datosMM{
  int N;
  int H;
  double *mA;
  double *mB;
  double *mC;
};

// Función para realizar la multiplicacion de matrices utilizando un bucle anidado
void *multMatrices(void *argMM){
  struct datosMM *datos = (struct datosMM *) argMM; // Convertimos el argumento en una estructura datosMM
  
  int n = datos->N; // Obtenemos la dimencionn de la matriz
  double *m1 = datos->mA; // Obtenemos el puntero a la matriz 1
  double *m2 = datos->mB; // Obtenemos el puntero a la matriz 2
  double *m3 = datos->mC; // Obtenemos el puntero a la matriz 3
  // Bucle anidado para realizar la multiplicacion de matrices
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      double sumaTemp, *pA, *pB; // Variables para almacenar los valores de las matrices
      sumaTemp = 0.0;
      pA = m1 + i*n ; // Calculamos la posicion del elemento actual en la matriz 1
      pB = m2 + j;   // Calculamos la posicion del elemento actual en la matriz 2
      for (int k = 0; k < n; k++, pA++, pB+=n){
        sumaTemp += *pA + *pB;  // Realizamos la suma de los elementos correspondientes
      }
      m3[i+j * n] = sumaTemp; // Almacenamos el resultado en la posision correspondiente en la matriz 3
    }
  }
  return 0;
};

// Funcion para realizar la multiplicación de matrices
void *MulMatrices(int n, double *m1, double *m2, double *m3){ 
  // Realizamos el algoritmo clásico de multiplicación de matrices
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      double sumaTemp, *pA, *pB; 
      sumaTemp = 0.0;
      pA = m1 + i*n ;
      pB = m2 + j;
      for (int k = 0; k < n; k++, pA++, pB+=n){
        sumaTemp +=*pA + *pB; 
      }
      m3[i+j * n] = sumaTemp;
    }
  }
  return 0;
};

int main(int argc, char *argv[]) {
  if(argc <= 2){ // Verificamos que se hayan ingresado los argumentos necesarios
    printf("Error: Ingrese la dimensión de la matriz y el número de hilos\n");
    printf("\n\t $ejecutable.exe DIM NumHilos\n");
    return -1;
  }

  // Convertimos los argumentos de la línea de comandos a enteros
  int N = (int) atof(argv[1]);
  int H = (int) atof(argv[2]);

  // Creamos un array de hilos
  pthread_t hilos [H];

  // Reservamos memoria para las matrices
  double *mA, *mB, *mC;
  mA = MEM_CHUNK;
  mB = mA + N*N;
  mC = mB + N*N;

  // Inicializamos las matrices
  iniMatrices(N, mA, mB, mC);

  // Imprimimos las matrices en pantalla
  impreMatrices(N, mA);
  impreMatrices(N, mB);
  impreMatrices(N, mC);

  printf("\n++++++++++++++++++++++++++++++++++++++\n");

  // Realizamos la multiplicación de matrices utilizando un solo hilo
  MulMatrices(N, mA, mB, mC);

  // Creamos los hilos y los iniciamos
  for(int h = 0; h < H; h++){
    struct datosMM datos;
    datos.N = N;
    datos.mA = mA; // Pasamos el puntero a la matriz 1
    datos.mB = mB;
    datos.mC = mC;
    pthread_create(&hilos[h], NULL, multMatrices, &datos); // Creamos un hilo y lo iniciamos con la función multMatrices
  }

  // Esperamos a que terminen los hilos
  for(int h = 0; h < H; h++){
    pthread_join(hilos[h], NULL); // Esperamos a que termine el hilo
  }

  printf("\n+Fin del programa...............!\n");

  return 0;
}