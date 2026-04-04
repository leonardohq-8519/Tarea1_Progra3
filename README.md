# Desarrollo de una librería de tensores en C++
### Autores ✒️
Leonardo Julian Huanay Quiroz

Emily Alessandra Chacón Ttito

## Descripción de la tarea 🎯
En esta tarea se debía diseñar e implementar una librería llamada **Tensor** en C++, la cual estaría inspirada en otros bibliotecas como NumPy y PyTorch.
El objetivo es crear una clase Tensor capaz de manejar tensores de hasta 3 dimensiones, realizar operaciones matemáticas con ellos y que sean utilizados en aplicaciones realistas de procesamiento de datos.

## Descarga de los archivos localmente💻
Primero se debe clonar el contenido del repositorio en la máquina local. Entramos a nuestra aplicación de terminal y clonamos el repositorio. Utilizamos ___cd___ para poder acceder al mismo.

```
git clone https://github.com/leonardohq-8519/Tarea1_Progra3.git
cd Tarea1_Progra3
```
Al realizar ___ls___, se deberían observar los siguientes archivos:
- main.cpp
- Tensor.cpp
- Tensor.h
- TensorTransform.cpp
- TensorTransform.h
- README.md
- CMakeLists.txt

## Compilación 🛠️
Considerando que el proyecto no se realizó en un solo archivo (ej. solamente main.cpp), se deben compilar todos los archivos juntos. Esto se puede realizar dependiendo del sistema operativo:
- __MacOs/Linux__
```
g++ -std=c++17 -o main main.cpp Tensor.cpp TensorTransform.cpp
```
o su versión alterna
```
clang++ -std=c++17 -o main main.cpp Tensor.cpp TensorTransform.cpp
```
- __Windows__
```
g++ -std=c++17 -o main.exe main.cpp Tensor.cpp TensorTransform.cpp
```
__⚠️Nota importante__ : En ambos casos se está creando un archivo ejecutable llamado main/main.exe para facilitar la ejecución del programa.

## Ejecución ⚙️
Una vez compilado el programa, se pueden ejecutar fácilmente con tan solo una línea en la terminal:

- __MacOs/Linux__
```
./main
```

- __Windows__
```
main.exe
```

## Resultado esperado 📤
Al ejecutar el programa, debería haber un output del tamaño final del tensor usado:

> Tamaño final: 1000,10

Si se presenta este resultado en la terminal, significa que la red neuronal simulada se ejecutó correctamente.
