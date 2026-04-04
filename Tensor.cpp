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

Tensor Tensor::concat(vector<Tensor> tensors, size_t axis) {
    if (tensors.empty()) {
        throw invalid_argument("Empty tensors");
    }
    const Tensor& first = tensors[0];
    size_t dims = first.c_size;

    if (axis >= dims) {
        throw invalid_argument("Invalid axis");
    }

    vector<size_t> new_shape(first.coords, first.coords + dims);

    for (size_t i = 1; i < tensors.size(); i++) {
        const Tensor& tensor = tensors[i];
        if (tensor.c_size != dims) {
            throw invalid_argument("Invalid size");
        }
        for (size_t d = 0; d < dims; d++) {
            if (d == axis) {
                new_shape[d] += tensor.coords[d];
            }
            else if (tensor.coords[d] != new_shape[d]) {
                throw invalid_argument("Invalid axis");
            }
        }
    }
    size_t outer_size = 1;
    for (size_t d = 0; d < axis; d++) {
        outer_size *= new_shape[d];
    }

    size_t inner_size = 1;
    for (size_t d = axis + 1; d < dims; d++) {
        inner_size *= new_shape[d];
    }

    vector<double> new_values;
    new_values.reserve(accumulate(new_shape.begin(),new_shape.end(),1,multiplies<size_t>()));
    vector<const double*> read_ptrs;
    for (const Tensor& tensor : tensors) {
        read_ptrs.push_back(tensor.tensor);
    }
    for (size_t o = 0; o < outer_size; o++) {
        for (size_t i = 0; i < tensors.size(); i++) {
            size_t chunk_size = tensors[i].coords[axis]*inner_size;
            new_values.insert(new_values.end(), read_ptrs[i], read_ptrs[i] + chunk_size);
            read_ptrs[i] += chunk_size;
        }
    }
    return Tensor(new_shape,new_values);
}

Tensor dot ( const Tensor & a , const Tensor & b ) {
    if (a.coords != b.coords)
        throw invalid_argument("Las dimensiones no son compatibles.");
}

Tensor matmul ( const Tensor & a , const Tensor & b ) {
    if (a.coords != b.coords)
        throw invalid_argument("Las dimensiones no son compatibles.");

}

void Tensor::print() const {
    if (c_size == 0 || size == 0) {
        cout << "[]" << endl;
    }

    if (c_size == 1) {
        cout << "[";
        for (size_t i = 0; i < coords[0]; i++) {
            cout << tensor[i] << (i < coords[0] - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }
    else if (c_size == 2) {
        cout << "[" << endl;
        for (size_t i = 0; i < coords[0]; i++) {
            cout << "  [";
            for (size_t j = 0; j < coords[1]; j++) {
                size_t index = i*coords[1] + j;
                cout << tensor[index] << (j < coords[1] - 1 ? ", " : "");
            }
            cout << "]" << (i < coords[0] - 1 ? ",\n" : "\n");
        }
        cout << "]" << endl;
    }
    else if (c_size == 3) {
        cout << "[" << endl;
        for (size_t i = 0; i < coords[0]; i++) {
            cout << "  [" << endl;
            for (size_t j = 0; j < coords[1]; j++) {
                cout << "    [" << endl;
                for (size_t k = 0; k < coords[2]; k++) {
                    size_t index = i * (coords[1] * coords[2]) + j * coords[2] + k;
                    cout << tensor[index] << (k < coords[2] - 1 ? ", " : "");
                }
                cout << "]" << (j < coords[1] - 1 ? ",\n" : "\n");
            }
            cout << "  ]" << (i < coords[0] - 1 ? ",\n\n" : "\n");
        }
        cout << "]" << endl;
    }
    else {
        throw invalid_argument("Invalid size");
    }
}