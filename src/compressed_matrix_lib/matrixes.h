//
// Created by Stephan on 04.09.2022.
//

#ifndef LAB1_SEM3_MATRIXES_H
#define LAB1_SEM3_MATRIXES_H
#include <iostream>
#include <cstring>

namespace MyMatrixes {
    typedef struct ListMatrix ListMatrix;
    typedef struct Item Item;

    typedef struct CSR_matrix {
        size_t width;
        size_t height;
        size_t n_items;
        int * items;
        size_t * cols_indexes;
        size_t * rows_indexes;
    } CSR_matrix;

    void * insert_item(void * array, size_t n, size_t size, size_t index, void * item);
    void * insert(void * array, size_t len, void * sub_array, size_t sub_len, size_t offset);
    CSR_matrix * init_CSR_matrix();
    CSR_matrix * init_CSR_matrix(Item * &items, size_t n, size_t width, size_t height);
    void insert_row_CSR_matrix(CSR_matrix * & M, const int * row, size_t index);
    ListMatrix * cut_CSR_matrix(CSR_matrix * &M);
    void print_CSR_matrix(const CSR_matrix * M);
    void destruct_CSR_matrix(CSR_matrix * &M);


    typedef struct DOC_matrix {
        size_t width;
        size_t height;
        size_t n_items;
        Item * items;
    } DOC_matrix;
    DOC_matrix * init_DOC_matrix(size_t width=0, size_t height=0);
    DOC_matrix * init_DOC_matrix(Item * &items, size_t n, size_t width, size_t height);
    ListMatrix * cut_DOC_matrix(CSR_matrix * &M);
    void print_DOC_matrix(const DOC_matrix * M);
    void print_DOC_matrix(const CSR_matrix * M);
    void destruct_DOC_matrix(DOC_matrix * &M);


    typedef struct ListEl {
        struct {
            size_t n;
            int data;
        };
        struct ListEl * next;
        struct ListEl * pr;
    } ListEl;

    typedef struct MatrixList {
        ListEl * head;
        ListEl * tail;
        size_t n;
        size_t size;
    } MatrixList;

    struct ListMatrix {
        size_t n;
        MatrixList * array;
    };

    ListEl * init_el(int data = 0);

    MatrixList * init_list();
    void push_back(MatrixList * list, int data);
    void destruct_list(MatrixList * list);

    ListMatrix * init_list_matrix();
    void push_line_list_matrix(ListMatrix * M, MatrixList * list);
    void print_list_matrix(const ListMatrix * LM);
    void destruct_list_matrix(ListMatrix * M);


    struct Item {
        size_t i;
        size_t j;
        int data;
    };
    int item_comp(const void *a, const void *b);

    template <typename T>
    void insert_t(T * &array, size_t n, T * sub_array, size_t sub_n, size_t ind) {
        T * tmp = new T[n+sub_n];
        std::memmove(tmp, array, ind);
        std::memmove(tmp + ind + sub_n, tmp + ind, (n-ind) * sizeof(T));
        std::memmove(tmp + ind, sub_array, sub_n);
        array = tmp;
    }
}

#endif //LAB1_SEM3_MATRIXES_H