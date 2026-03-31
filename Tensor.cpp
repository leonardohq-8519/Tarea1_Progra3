//
// Created by leona on 30/03/2026.
//

#include "Tensor.h"
#include <random>
#include <stdexcept>

double rand_num(double min, double max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

Tensor::~Tensor() {
    delete[] tensor;
}

Tensor::Tensor(const vector<size_t> &shape, const vector<double> &values) {
    //MAX 3D
    size_t size = values.size();
    tensor = new double[size];
    coords = new int[shape.size()];

    if (shape.size() > 3 || shape.size() < 1) {
        throw invalid_argument("Invalid shape");
    }

    for (int i = 0; i < size; i++) {
        tensor[i] = values[i];
    }

    for (int i = 0; i < shape.size(); i++) {
        coords[i] = shape[i];
    }
}

Tensor Tensor::zeros(const vector<size_t> &shape) {
    int size = 1;
    for (int i = 0; i < shape.size(); i++) {
        size *= shape[i];
    }
    vector<double> values(size);
    for (int i = 0; i < size; i++) {
        values[i] = 0;
    }
    return Tensor(shape,values);
}

Tensor Tensor::ones(const vector<size_t> &shape) {
    int size = 1;
    for (int i = 0; i < shape.size(); i++) {
        size *= shape[i];
    }
    vector<double> values(size);
    for (int i = 0; i < size; i++) {
        values[i] = 1;
    }
    return Tensor(shape,values);
}

Tensor Tensor::random(const vector<size_t> &shape, double min, double max) {
    int size = 1;
    for (int i = 0; i < shape.size(); i++) {
        size *= shape[i];
    }
    vector<double> values(size);
    for (int i = 0; i < size; i++) {
        values[i] = rand_num(min, max);
    }
    return Tensor(shape,values);
}

Tensor Tensor::arrange(int start, int end) {

}