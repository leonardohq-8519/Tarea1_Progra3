#include <iostream>
#include "Tensor.h"

using namespace std;

int main() {
    Tensor tensor1({2,2},{1,2,3,4});
    Tensor tensor2 = Tensor::zeros({3,3});
    Tensor tensor3 = Tensor::random({4,4},0.5,3.4);
    Tensor tensor4 = Tensor::arrange(0,6);

    Tensor tensor5 = tensor1;
    Tensor tensor6(tensor2);
    Tensor tensor7(move(tensor3));
}