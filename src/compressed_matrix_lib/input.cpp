//
// Created by Stephan on 06.09.2022.
//

#include <iostream>
#include <string>

#include "matrixes.h"
#include "input.h"


using namespace MyMatrixes;

int * read_int_array(size_t n) {
    int * array = new int[n];
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        try {
            array[i] = std::stoi(s);
        } catch (const std::invalid_argument & e) {
            std::cout << e.what() << std::endl;
            delete[] array;
            return nullptr;
        } catch (const std::out_of_range & e) {
            std::cout << e.what() << "\n";
            delete[] array;
            return nullptr;
        }

    }
    std::cin.clear();

    return array;
}

CSR_matrix * MyMatrixes::read_matrix() {
    size_t height{}, width{};
    std::cout << "введите высоту и ширину вашей матрицы: " << std::endl;
    std::string height_s;
    std::string width_s;
    std::cin >> height_s;
    std::cin >> width_s;
    try {
        height = std::stoi(height_s);
        width = std::stoi(width_s);
    } catch (const std::invalid_argument & e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    } catch (const std::out_of_range & e) {
        std::cout << e.what() << "\n";
        return nullptr;
    }

    CSR_matrix * M = init_CSR_matrix();
    M->width = width;
    for (size_t i = 0; i < height; ++i) {
        int * array = nullptr;
        while (array == nullptr)
            array = read_int_array(width);
        insert_row_CSR_matrix(M, array, i);
        delete[] array;
    }

    return M;
}