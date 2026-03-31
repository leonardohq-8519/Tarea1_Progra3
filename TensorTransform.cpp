//
// Created by leona on 30/03/2026.
//

#include "TensorTransform.h"
#include <cmath>

Tensor relu::apply(const Tensor &t) const {
    vector<double> values(t.size);
    for (size_t i = 0; i < t.size; i++) {
        values[i] = max(0.0,t.tensor[i]);
    }
    return Tensor(vector<size_t>(t.coords,t.coords+t.c_size), values);
}

Tensor sigmoid::apply(const Tensor &t) const {
    vector<double> values(t.size);
    for (size_t i = 0; i < t.size; i++) {
        double val = t.tensor[i];
        values[i] = 1.0 / (1.0 + exp(-val));
    }

    return Tensor(vector<size_t>(t.coords,t.coords+t.c_size), values);
}
