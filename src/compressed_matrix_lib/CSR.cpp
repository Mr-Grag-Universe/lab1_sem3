//
// Created by Stephan on 04.09.2022.
//
#include <iostream>
#include <string>
#include <cstring>

#include "matrixes.h"

void * insert(void * array, size_t len, void * sub_array, size_t sub_len, size_t offset) {
    char * tmp = new char[len+sub_len];
    std::memcpy(tmp, array, offset);
    std::memcpy(tmp + offset + sub_len, tmp + offset, len-offset);
    std::memcpy(tmp + offset, sub_array, sub_len);
    return (void *) tmp;
}

CSR_matrix * init_CSR_matrix() {
    CSR_matrix * M = new CSR_matrix;

    M->height = 0;
    M->width = 0;
    M->n_items = 0;
    M->items = nullptr;
    M->cols_indexes = nullptr;
    M->rows_indexes = new size_t[1];
    M->rows_indexes[0] = 0;

    return M;
}

void insert_row_CSR_matrix(CSR_matrix * &M, const int * row, size_t index) {
    if (row == nullptr || M == nullptr) return;

    int * items = new int[M->width];
    auto * cols = new size_t[M->width];
    size_t n = 0;
    for (size_t i = 0; i < M->width; ++i) items[i] = 0;

    for (size_t i = 0; i < M->width; ++i) {
        if (row[i]) {
            items[n] = row[i];
            cols[n] = i;
            ++n;
        }
    }

    if (n == 0) {
        cols[0] = 0;
        n = 1;
        items[0] = 0;
    }

    // вставить в items ненулевые элементы
    if (M->height == 0) {
        M->items = new int[n];
        std::memmove(M->items, items, n*sizeof(int));

        M->cols_indexes = new size_t[n];
        std::memmove(M->cols_indexes, cols, n*sizeof(size_t));

        delete[] M->rows_indexes;
        M->rows_indexes = new size_t[2];
        M->rows_indexes[0] = 0;
        M->rows_indexes[1] = n;
    }
    else {
        void * tmp = insert((void*) M->items, (M->n_items)*sizeof(int), (void*) items, sizeof(int)*n, M->rows_indexes[index]*sizeof(int));
        delete[] M->items;
        M->items = (int*) tmp;

        // вставить в cols индексы ненулевых элементов строки
        tmp = insert((void*) M->cols_indexes, (M->n_items)*sizeof(size_t), (void*) cols, sizeof(size_t)*n, M->rows_indexes[index]*sizeof(size_t));
        delete[] M->cols_indexes;
        M->cols_indexes = (size_t*) tmp;

        tmp = insert((void*) M->rows_indexes, (M->height+1)*sizeof(size_t), (void*) (M->rows_indexes+index), sizeof(size_t), (index+1)*sizeof(size_t));
        delete[] M->rows_indexes;
        M->rows_indexes = (size_t*) tmp;
        for (size_t i = index+1; i < M->height+2; ++i)
            M->rows_indexes[i] += n;
    }

    // правим индексы в row_indexes
    M->n_items += n;
    // увеличить на 1 height
    M->height += 1;
    delete[] cols;
    delete[] items;
}

ListMatrix * cut_CSR_matrix(CSR_matrix * &M) {
    auto * max_col = new size_t[M->height];
    for (size_t i = 0; i < M->height; ++i) {
        max_col[i] = M->cols_indexes[M->rows_indexes[i]];
        int max = M->items[M->rows_indexes[i]];
        for (size_t j = M->rows_indexes[i]; j < M->rows_indexes[i+1]; ++j){
            if (max < M->items[j]) {
                max = M->items[j];
                max_col[i] = M->cols_indexes[j];
            }
        }
    }
//    std::cout << "max_col: ";
//    for (size_t i = 0; i < M->height; ++i)
//        std::cout << max_col[i] << " ";
//    std::cout << std::endl;

    ListMatrix * LM = init_list_matrix();
    for (size_t i = 1; i < M->height+1; ++i) {
        size_t ind = 0;
        MatrixList * list = init_list();
        for (size_t j = 0; j <= max_col[i-1]; ++j) {
            if (ind < M->n_items && j == M->cols_indexes[M->rows_indexes[i-1]+ind]) {
                push_back(list, M->items[M->rows_indexes[i-1]+ind]);
                ++ind;
            }
            else {
                push_back(list, 0);
            }
        }
        push_line_list_matrix(LM, list);
        delete list;
    }

    delete[] max_col;

    return LM;
}

void print_CSR_matrix(const CSR_matrix * M) {
    size_t count = 0;
    for (size_t i = 1; i < M->height+1; ++i) {
        size_t ind = 0;
        for (size_t j = 0; j < M->width; ++j) {
            // getchar();
            if (count < M->n_items && ind < M->n_items && j == M->cols_indexes[M->rows_indexes[i-1]+ind]) {
                std::cout << M->items[M->rows_indexes[i-1]+ind] << " ";
                ++ind;
                ++count;
            }
            else {
                std::cout << 0 << " ";
            }
        }
        std::cout << std::endl;
    }
}

void destruct_CSR_matrix(CSR_matrix * &M) {
    delete[] M->items;
    delete[] M->cols_indexes;
    delete[] M->rows_indexes;
    delete M;
}