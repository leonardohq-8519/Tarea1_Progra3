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
  
   return 0;
}
