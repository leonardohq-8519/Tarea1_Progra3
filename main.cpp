#include <iostream>
#include "Tensor.h"
#include "TensorTransform.h"

using namespace std;

int main() {
   Tensor tensor1({2, 2}, {1, 2, 3, 4});

   // Ejemplo 3
   Tensor tensor2 = Tensor::zeros({2, 3});
   Tensor tensor3 = Tensor::ones({3, 3});
   Tensor tensor4 = Tensor::random({2, 2},0.0,1.0);
   Tensor tensor5 = Tensor::arrange(0, 6);

   // Ejemplo 5
   Tensor tensor6 = Tensor::arrange(-5, 5).view({2, 5});
   relu ReLU;
   Tensor tensor7 = tensor6.apply(ReLU);

   // Ejemplo 6
   Tensor tensor8 = tensor6 + tensor7;
   Tensor tensor9 = tensor6 - tensor7;
   Tensor tensor10 = tensor6 * tensor7;
   Tensor tensor11 = tensor6 * 2.0;

   // Ejemplo 7
   Tensor tensor12 = Tensor::arrange(0, 12);
   Tensor tensor13 = tensor12.view({3, 4});

   Tensor tensor14 = Tensor::arrange(0, 3);
   Tensor tensor15 = tensor14.unsqueeze(0); // shape {1, 3}
   Tensor tensor16 = tensor14.unsqueeze(1); // shape {3, 1}

   // Ejemplo 8
   Tensor tensor17 = Tensor::ones({2, 3});
   Tensor tensor18 = Tensor::zeros({2, 3});
   Tensor tensor19 = Tensor::concat({tensor17, tensor18}, 0);



   // Ejecución de la parte 10
   // 1. Crear un tensor de entrada de dimensiones 1000 × 20 × 20.
   Tensor A = Tensor::zeros({1000, 20, 20});

   // 2. Transformarlo a 1000 × 400 usando view.
   Tensor A_view = A.view({1000, 400});

   // 3. Multiplicarlo por una matriz 400 × 100.
   Tensor B = Tensor::zeros({400, 100});
   Tensor mult_w1 = matmul(A_view, B);

   // 4. Sumar una matriz 1 × 100.
   Tensor C = Tensor::zeros({1, 100});
   Tensor D = mult_w1 + C;

   // 5. Aplicar la funci´on ReLU.
   relu ReLU2;
   Tensor E = D.apply(ReLU2);

   // 6. Multiplicar por una matriz 100 × 10.
   Tensor F = Tensor::zeros({100, 10});
   Tensor mult_w2 = matmul(E, F);

   // 7. Sumar una matriz 1 × 10.
   Tensor G = Tensor::zeros({1, 10});
   Tensor H = mult_w2 + G;

   // 8. Aplicar la funci´on Sigmoid.
   sigmoid Sigmoid;
   Tensor I = H.apply(Sigmoid);

   // Para corroborar el tamaño final
   auto shape = I.getShape();

   cout << "Tamaño final: ";
   cout << *shape <<","<<*(shape+1)<< endl;
   return 0;
}
