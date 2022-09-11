//
// Created by Stephan on 10.09.2022.
//
#include <iostream>
#include <string>
#include <cstring>

#include "matrixes.h"

using namespace MyMatrixes;

DOC_matrix * MyMatrixes::init_DOC_matrix(size_t width, size_t height) {
    auto * M = new DOC_matrix;
    M->width = width;
    M->height = height;
    M->items = nullptr;
    M->n_items = 0;

    return M;
}

DOC_matrix * MyMatrixes::init_DOC_matrix(Item * &items, size_t n, size_t width, size_t height) {
    DOC_matrix * M = init_DOC_matrix(width, height);
    std::qsort(items, n, sizeof(Item), item_comp);
    M->items = items;
    M->n_items = n;

    return M;
}

ListMatrix * MyMatrixes::cut_DOC_matrix(CSR_matrix * &M) {
    return nullptr;
}

void MyMatrixes::print_DOC_matrix(const DOC_matrix * M) {
    size_t count = 0;
    for (size_t i = 0; i < M->height; ++i) {
        size_t ind = 0;
        while (M->items[count].i == i) {
            while (M->items[count].j > ind) {
                std::cout << "0 ";
                ++ind;
            }
            ++count;
            std::cout << M->items[count].data << " ";
        }
        std::cout << std::endl;
    }
}

void MyMatrixes::destruct_DOC_matrix(DOC_matrix * &M) {
    delete[] M->items;
    delete M;
}