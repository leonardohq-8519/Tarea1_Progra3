cmake_minimum_required(VERSION 4.0)
project(Tarea1_P3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tarea1_P3 main.cpp
        Tensor.cpp
        Tensor.h
        TensorTransform.cpp
        TensorTransform.h)
