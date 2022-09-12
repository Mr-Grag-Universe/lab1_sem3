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

ListMatrix * MyMatrixes::cut_DOC_matrix(DOC_matrix * &M) {
    if (!M)
        return nullptr;

    size_t * max_col = nullptr;
    try {
        max_col = new size_t[M->height];
    } catch (std::bad_alloc & ba) {
        std:: cout << ba.what() << std::endl;
        return nullptr;
    }

    // выборка максимумов
    size_t count = 0;
    for (size_t i = 0; i < M->height; ++i) {
        int max_item = M->items[count].data;
        max_col[i] = 0;
        while (M->items[count].i == i) {
            if (max_item < M->items[count].data) {
                max_item = M->items[count].data;
                max_col[i] = M->items[count].j;
            }
            count++;
        }
    }

//    std::cout << "max_col: ";
//    for (size_t i = 0; i < M->height; ++i)
//        std::cout << max_col[i] << " ";
//    std::cout << std::endl;

    ListMatrix * LM = init_list_matrix();
    count = 0;
    for (size_t i = 0; i < M->height; ++i) {
        MatrixList * list = init_list();

        // пушим в лист
        size_t ind = 0;
        while (ind <= max_col[i]) {
            if (ind == M->items[count].j) {
                push_back(list, M->items[count].data);
                ++count;
            }
            else {
                push_back(list, 0);
            }
            ++ind;
        }

        push_line_list_matrix(LM, list);
        delete list;
    }

    delete[] max_col;

    return LM;
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