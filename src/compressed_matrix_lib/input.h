//
// Created by Stephan on 06.09.2022.
//

#ifndef LAB1_SEM3_INPUT_H
#define LAB1_SEM3_INPUT_H
#include "matrixes.h"

namespace MyMatrixes {
    typedef enum InputErrors {
        END_OF_STREAM,
        CONVERSION_FAILED,
        MEMORY_ERROR,
    } InputErrors;

    int * read_matrix_line(size_t n);
    Item * read_items(size_t height, size_t width);
    CSR_matrix * read_compressed_matrix();
    CSR_matrix * read_matrix();
}
#endif //LAB1_SEM3_INPUT_H
