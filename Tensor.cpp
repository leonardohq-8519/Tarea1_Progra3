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
   delete[] coords;
}


Tensor::Tensor(const vector<size_t> &shape, const vector<double> &values) {
   //MAX 3D
   size = values.size();
   c_size = shape.size();
   tensor = new double[size];
   coords = new size_t[c_size];


   if (c_size > 3 || c_size < 1) {
       throw invalid_argument("Invalid shape");
   }


   for (int i = 0; i < size; i++) {
       tensor[i] = values[i];
   }


   for (int i = 0; i < c_size; i++) {
       coords[i] = shape[i];
   }
}


Tensor Tensor::zeros(const vector<size_t> &shape) {
   int size = 1;
   for (int i = 0; i < shape.size(); i++) {
       size *= shape[i];
   }
   vector<double> values(size, 0);
   return Tensor(shape, values);
}


Tensor Tensor::ones(const vector<size_t> &shape) {
   int size = 1;
   for (int i = 0; i < shape.size(); i++) {
       size *= shape[i];
   }
   vector<double> values(size, 1.0);
   return Tensor(shape, values);
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
   return Tensor(shape, values);
}


Tensor Tensor::arrange(int start, int end) {
   size_t size = end - start;
   vector<double> values(size);
   for (int i = 0; i < size; i++) {
       values[i] = start + i;
   }
   return Tensor({size}, values);
}


Tensor::Tensor(const Tensor &other) {
   tensor = new double[other.size];
   coords = new size_t[other.c_size];


   //Deep Copy
   for (int i = 0; i < other.c_size; i++) {
       coords[i] = other.coords[i];
   }
   for (int i = 0; i < other.size; i++) {
       tensor[i] = other.tensor[i];
   }
   size = other.size;
   c_size = other.c_size;
}


Tensor &Tensor::operator=(const Tensor &other) {
   if (this != &other) {
       delete[] tensor;
       delete[] coords;
       tensor = new double[other.size];
       coords = new size_t[other.c_size];
       for (int i = 0; i < other.c_size; i++) {
           coords[i] = other.coords[i];
       }
       for (int i = 0; i < other.size; i++) {
           tensor[i] = other.tensor[i];
       }
       size = other.size;
       c_size = other.c_size;
   }
   return *this;
}


Tensor::Tensor(Tensor &&other) noexcept : tensor(other.tensor), coords(other.coords), size(other.size),
                                         c_size(other.c_size) {
   other.tensor = nullptr;
   other.coords = nullptr;
   other.size = 0;
   other.c_size = 0;
}


Tensor &Tensor::operator=(Tensor &&other) noexcept {
   if (this != &other) {
       delete[] tensor;
       delete[] coords;
       tensor = other.tensor;
       coords = other.coords;
       size = other.size;
       c_size = other.c_size;


       other.coords = nullptr;
       other.tensor = nullptr;
       other.size = 0;
       other.c_size = 0;
   }
   return *this;
}


Tensor Tensor::apply(const TensorTransform &transform) const {
   return transform.apply(*this);
}




Tensor operator+(const Tensor &a, const Tensor &b) {
   if (a.coords != b.coords)
       throw invalid_argument("Las dimensiones no son compatibles.");
   vector<size_t> vec;
   for (int i = 0; i < a.c_size; i++)
       vec.push_back(a.coords[i]);
   vector<double> r;
   for (int j = 0; j < b.size; j++)
       r[j] = a.tensor[j] + b.tensor[j];
   Tensor resultado(vec, r);
   return resultado;
}




Tensor operator-(const Tensor &a, const Tensor &b) {
   if (a.coords != b.coords)
       throw invalid_argument("Las dimensiones no son compatibles.");


   vector<size_t> vec;
   for (int i = 0; i < a.c_size; i++)
       vec.push_back(a.coords[i]);
   vector<double> r;
   for (int j = 0; j < b.size; j++)
       r[j] = a.tensor[j] - b.tensor[j];
   Tensor resultado(vec, r);
   return resultado;
}


Tensor operator*(const Tensor &a, const Tensor &b) {
   if (a.coords != b.coords)
       throw invalid_argument("Las dimensiones no son compatibles.");


   vector<size_t> vec;
   for (int i = 0; i < a.c_size; i++)
       vec.push_back(a.coords[i]);
   vector<double> r;
   for (int j = 0; j < b.size; j++)
       r[j] = a.tensor[j] * b.tensor[j];
   Tensor resultado(vec, r);
   return resultado;
}


Tensor operator*(const Tensor &a, double b) {
   vector<size_t> vec;
   for (int i = 0; i < a.c_size; i++)
       vec.push_back(a.coords[i]);
   vector<double> r;
   for (int j = 0; j < a.size; j++)
       r[j] = a.tensor[j] * b;
   Tensor resultado(vec, r);
   return resultado;
}
