//
// Created by Stephan on 04.09.2022.
//
#include <iostream>
#include <string>
#include <cstring>

#include "matrixes.h"
#include "input.h"

using namespace MyMatrixes;


CSR_matrix * MyMatrixes::init_CSR_matrix() {
    auto * M = new CSR_matrix;

    M->height = 0;
    M->width = 0;
    M->n_items = 0;
    M->items = nullptr;
    M->cols_indexes = nullptr;
    M->rows_indexes = new size_t[1];
    M->rows_indexes[0] = 0;

    return M;
}

CSR_matrix * MyMatrixes::init_CSR_matrix(Item * &items, size_t n, size_t width, size_t height) {
    CSR_matrix * M = nullptr;
    try {
        M = new CSR_matrix; //init_CSR_matrix();
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        exit(MEMORY_ERROR);
    }
    M->width = width;
    M->height = height;
    M->n_items = 0;
    M->rows_indexes = nullptr;
    M->cols_indexes = nullptr;
    M->items = nullptr;

    // исправление если мало элементов (добавляем нули - как элементы нулевых строк)
    size_t new_n = n;
    for (size_t i = 0; i < height; ++i) {
        bool found = false;
        for (size_t j = 0; j < new_n; ++j) {
            if (items[j].i == i) {
                found = true;
                break;
            }
        }
        if (!found) {
            Item item = {i, 0, 0};
            // void * tmp = insert(items, new_n * sizeof(Item), &item, sizeof(Item), sizeof(Item)*new_n);
            Item * tmp = nullptr;
            try {
                tmp = new Item[new_n+1];
            } catch (std::bad_alloc & ba) {
                std::cerr << ba.what() << std::endl;
                exit(MEMORY_ERROR);
            }
            std::memmove(tmp+1, items, sizeof(Item) * new_n);
            tmp[0] = item;

            delete[] items;
            items = (Item*) tmp;
            ++new_n;
        }
    }

    std::qsort(items, new_n, sizeof(Item), item_comp);
    int * item = nullptr;
    size_t * cols = nullptr;
    size_t * rows = nullptr;
    try {
        item = new int[new_n];
        cols = new size_t[new_n];
        rows = new size_t[height+1];
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        exit(MEMORY_ERROR);
    }
    rows[0] = 0;

    size_t ind = 0;
    for (size_t i = 0; i < new_n; ++i) {
        item[i] = items[i].data;
        cols[i] = items[i].j;
        if (items[i].i != ind) {
            ++ind;
            rows[ind] = i;
        }
    }
    rows[height] = new_n;

    std::cout << "items: ";
    for (size_t i = 0; i < new_n; ++i)
        std::cout << item[i];
    std::cout << "\n";
    std::cout << "cols: ";
    for (size_t i = 0; i < new_n; ++i)
        std::cout << cols[i];
    std::cout << "\n";
    std::cout << "rows: ";
    for (size_t i = 0; i < height+1; ++i)
        std::cout << rows[i];
    std::cout << "\n";


    M->items = item;
    M->cols_indexes = cols;
    M->rows_indexes = rows;
    M->n_items = new_n;

    return M;
}

void MyMatrixes::insert_row_CSR_matrix(CSR_matrix * &M, const int * row, size_t index) {
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

ListMatrix * MyMatrixes::cut_CSR_matrix(CSR_matrix * &M) {
    if (!M)
        return nullptr;

    size_t * max_col = nullptr;
    try {
        max_col = new size_t[M->height];
    } catch (std::bad_alloc & ba) {
        std:: cout << ba.what() << std::endl;
        return nullptr;
    }

    // выбираем номера столбцов с максимуми
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
    // пушим в новую матрицу
    size_t count = 0;
    for (size_t i = 1; i < M->height+1; ++i) {
        size_t ind = 0;
        MatrixList * list = init_list();
        for (size_t j = 0; j <= max_col[i-1]; ++j) {
            if (count < M->n_items && ind < M->n_items && count < M->rows_indexes[i] && j == M->cols_indexes[M->rows_indexes[i-1]+ind]) {
                push_back(list, M->items[M->rows_indexes[i-1]+ind]);
                ++ind;
                ++count;
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

void MyMatrixes::print_CSR_matrix(const CSR_matrix * M) {
    size_t count = 0;
    for (size_t i = 1; i < M->height+1; ++i) {
        size_t ind = 0;
        for (size_t j = 0; j < M->width; ++j) {
            // getchar();
            if (ind < M->n_items && count < M->rows_indexes[i] && j == M->cols_indexes[M->rows_indexes[i-1]+ind]) {
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

void MyMatrixes::destruct_CSR_matrix(CSR_matrix * &M) {
    delete[] M->items;
    delete[] M->cols_indexes;
    delete[] M->rows_indexes;
    delete M;
}