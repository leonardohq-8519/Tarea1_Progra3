//
// Created by leona on 30/03/2026.
//

#ifndef TAREA1_P3_TENSORTRANSFORM_H
#define TAREA1_P3_TENSORTRANSFORM_H
#include "Tensor.h"

using namespace std;

class Tensor;

class TensorTransform {
    public:
        virtual Tensor apply(const Tensor& t) const = 0;
        virtual ~TensorTransform() = default;
};

class relu : public TensorTransform {
    public:
    Tensor apply(const Tensor& t) const override;
};

class sigmoid : public TensorTransform {
    public:
    Tensor apply(const Tensor& t) const override;
};


#endif //TAREA1_P3_TENSORTRANSFORM_H