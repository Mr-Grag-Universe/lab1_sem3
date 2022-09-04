//
// Created by Stephan on 04.09.2022.
//

#ifndef LAB1_SEM3_MATRIXES_H
#define LAB1_SEM3_MATRIXES_H
#include <iostream>

struct CSR_matrix {
    size_t width;
    size_t height;
    int * items;
    size_t * cols_indexes;
    size_t * rows_indexes;
};
#endif //LAB1_SEM3_MATRIXES_H
