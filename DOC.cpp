//
// Created by Stephan on 04.09.2022.
//
#include <iostream>
#include "matrixes.h"

CSR_matrix * init_CSR_matrix(int height, int width) {
    CSR_matrix * M = new CSR_matrix;

    M->height = height;
    M->width = width;
    M->items = nullptr;
    M->cols_indexes = nullptr;
    M->rows_indexes = nullptr;

    return M;
}

void insert_row_CSR_matrix(CSR_matrix & M, int * row, int index) {
    if (row == nullptr || M == nullptr) return;

    // увеличить на 1 height
    for (size_t i = 0; i < M.width; ++i) {
        // увеличить на 1 размер row
        // вставить в row индекс с которого начинается ненулевые элементы
        // вставить в cols индексы ненулевых элементов строки
        // вставить в items ненулевые элементы
    }
}