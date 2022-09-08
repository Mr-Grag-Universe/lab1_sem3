//
// Created by Stephan on 06.09.2022.
//

#include <iostream>
#include <string>

#include "matrixes.h"


ListEl * init_el(int data) {
    auto * el = new ListEl;
    el->next = nullptr;
    el->pr = nullptr;
    el->n = 1;
    el->data = data;
    return el;
}

void destruct_el(ListEl * el) {
    delete el;
}

MatrixList * init_list() {
    auto * list = new MatrixList;
    list->n = 0;
    list->size = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void clear_list(MatrixList * list) {
    ListEl * el = list->head;
    while (el != nullptr) {
        ListEl * tmp = el;
        el = el->next;
        destruct_el(tmp);
    }
    list->tail = nullptr;
    list->head = nullptr;
    list->size = 0;
    list->n = 0;
}

void destruct_list(MatrixList * list) {
    ListEl * el = list->head;
    while (el != nullptr) {
        ListEl * tmp = el;
        el = el->next;
        destruct_el(tmp);
    }
    delete list;
}

void push_back(MatrixList * list, int data) {
    if (list == nullptr)
        throw "pushing to nullptr array";

    if (list->tail) {
        if (list->tail->data == data) {
            list->tail->n++;
        } else {
            list->tail->next = init_el(data);
            list->tail->next->pr = list->tail;
            list->tail = list->tail->next;
            list->size++;
        }
    } else {
        list->head = init_el(data);
        list->tail = list->head;
        list->size++;
    }
    list->n++;
}

void print_list(const MatrixList * list) {
    if (list == nullptr) {
        std::cout << "empty list" << std::endl;
        return;
    }

    ListEl * el = list->head;
    while (el != nullptr) {
        for (size_t i = 0; i < el->n; ++i)
            std::cout << "->" << el->data;
        el = el->next;
    }
    std::cout << std::endl;
}

ListMatrix * init_list_matrix() {
    auto * M = new ListMatrix;
    M->array = nullptr;
    M->n = 0;

    return M;
}

void push_line_list_matrix(ListMatrix * M, MatrixList * list) {
    if (M->array == nullptr) {
        M->array = new MatrixList[1];
        M->array[0] = *list;
    } else {
        void * tmp = insert(M->array, sizeof(MatrixList)*M->n, list, sizeof(MatrixList), sizeof(MatrixList)*M->n);
        delete[] M->array;
        M->array = (MatrixList *) tmp;
    }
    M->n++;
}

ListMatrix * init_list_matrix(CSR_matrix * M) {
    ListMatrix * LM = init_list_matrix();

    MatrixList * list = nullptr;
    for (size_t i = 1; i < M->height+1; ++i) {
        size_t ind = 0;
        list = init_list();
        for (size_t j = 0; j <= M->width; ++j) {
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

    return LM;
}

void print_list_matrix(const ListMatrix * LM) {
    for (size_t i = 0; i < LM->n; ++i) {
        // печатаем листик
        print_list(LM->array+i);
    }
}

void destruct_list_matrix(ListMatrix * M) {
    for (size_t i = 0; i < M->n; ++i)
        clear_list(M->array + i);
    delete[] M->array;
    delete M;
}