//
// Created by leona on 30/03/2026.
//

#ifndef TAREA1_P3_TENSOR_H
#define TAREA1_P3_TENSOR_H
#include <vector>
#include "TensorTransform.h"
using namespace std;

class TensorTransform;

class Tensor {
    double* tensor;
    size_t* coords;
    size_t size;
    size_t c_size;
public:
    friend class TensorTransform;
    friend class relu;
    friend class sigmoid;
    Tensor(const vector<size_t>& shape, const vector<double>& values);
    Tensor(const Tensor& other);
    Tensor(Tensor&& other) noexcept;
    Tensor& operator=(const Tensor& other);
    Tensor& operator=(Tensor&& other) noexcept;
    ~Tensor();
    static Tensor zeros(const vector<size_t>& shape);
    static Tensor ones(const vector<size_t>& shape);
    static Tensor random(const vector<size_t>& shape, double min, double max);
    static Tensor arrange(int start, int end);

    Tensor apply(const TensorTransform& transform) const;
};


#endif //TAREA1_P3_TENSOR_H