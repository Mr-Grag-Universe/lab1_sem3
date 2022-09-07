//
// Created by Stephan on 06.09.2022.
//

#include <iostream>
#include <string>

#include "matrixes.h"


int * read_int_array(size_t n) {
    // std::string input;
    // std::cin >> input;

    // std::cout << input;

    // int * array = new int[n];
    // size_t pos = 0;
    // for (size_t i = 0; i < n; ++i) {
    //     array[i] = std::stoi(input, &pos, 10);
    //     input = input.substr(pos);
    // }

    int * array = new int[n];
    for (size_t i = 0; i < n; ++i)
        std::cin >> array[i];

    return array;
}

CSR_matrix * read_matrix() {
    size_t height{}, width{};
    std::cin >> height;
    std::cin >> width;

    CSR_matrix * M = init_CSR_matrix();
    M->width = width;
    for (size_t i = 0; i < height; ++i) {
        int * array = read_int_array(width);
        insert_row_CSR_matrix(M, array, i);
        delete[] array;
    }

    return M;
}