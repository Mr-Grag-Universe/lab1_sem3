//
// Created by Stephan on 06.09.2022.
//

#include <iostream>
#include <string>
#include <cstring>

#include "matrixes.h"
#include "input.h"


using namespace MyMatrixes;

int read_int() {
    std::string s;
    if (!(std::cin >> s)) {
        std::cout << "end of this stream" << std::endl;
        throw std::runtime_error("");
    }
    int n;
    try {
        n = std::stoi(s);
    } catch (const std::invalid_argument & e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("wrong input");
    } catch (const std::out_of_range & e) {
        std::cout << e.what() << std::endl;
        throw std::invalid_argument("wrong input");
    }
    return n;
}
size_t read_size_t() {
    std::string s;
    if (!(std::cin >> s)) {
        std::cout << "end of this stream" << std::endl;
        throw std::runtime_error("");
    }
    size_t n;
    try {
        n = std::stoll(s);
    } catch (const std::invalid_argument & e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("wrong input");
    } catch (const std::out_of_range & e) {
        std::cout << e.what() << std::endl;
        throw std::invalid_argument("wrong input");
    }
    return n;
}

int * read_int_array(size_t n) {
    int * array = nullptr;
    try {
        array = new int[n];
    } catch (std::bad_alloc &ba) {
        std::cerr << ba.what() << std::endl;
        return nullptr;
    }
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
    try {
        height = read_int();
        width = read_int();
    } catch (std::runtime_error & e) {
        // конец ввода
        return nullptr;
    } catch (std::invalid_argument & e) {
        // неверный ввод
        throw std::invalid_argument("wrong input in read_matrix()");
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

CSR_matrix * MyMatrixes::read_compressed_matrix() {
    size_t height{}, width{};
    std::cout << "введите высоту и ширину вашей матрицы: " << std::endl;
    try {
        height = read_int();
        width = read_int();
    } catch (std::runtime_error & e) {
        // конец ввода
        return nullptr;
    } catch (std::invalid_argument & e) {
        // неверный ввод
        throw std::invalid_argument("wrong input in read_matrix()");
    }

    CSR_matrix * M = nullptr;
    // M->width = width;
    // M->height = height;

    size_t counter = 0;
    size_t size = 1;
    Item * items = new Item[1];
    Item * tmp = nullptr;
    std::cout << "enter not zero elements in your matrix in format:\n<i-index> <j-index> <int-data>" << std::endl;
    while (counter < height * width) {
        try {
            size_t i = read_size_t();
            size_t j = read_size_t();
            int data = read_int();

            while (i >= height || j >= width || i < 0 || j < 0) {
                std::cout << "wrong input. try again.";
                i = read_size_t();
                j = read_size_t();
                data = read_int();
            }
            items[counter].i = i;
            items[counter].j = j;
            items[counter].data = data;
        } catch (std::runtime_error & e) {
            // конец ввода
            // обрезаем массив
            try {
                tmp = new Item[counter];
            } catch (std::bad_alloc & ba) {
                std::cerr << ba.what() << std::endl;
                exit(MEMORY_ERROR);
            }
            std::memmove(tmp, items, sizeof(Item) * counter);
            delete[] items;
            items = tmp;

            // for (size_t i = 0; i < counter; ++i)
            //     std::cout << items[i].i << " " << items[i].j << " " << items[i].data << "\n";

            // создать матрицу
            M = init_CSR_matrix(items, counter, width, height);
            break;
        } catch (std::invalid_argument & e) {
            // неверный ввод
            continue;
        }
        ++counter;
        // расширение массива
        if (counter == size) {
            size *= 2;
            try {
                tmp = new Item[size];
            } catch (std::bad_alloc & ba) {
                std::cerr << ba.what() << std::endl;
                exit(MEMORY_ERROR);
            }
            std::memmove(tmp, items, sizeof(Item) * counter);
            delete[] items;
            items = tmp;
        }
    }
    delete[] items;

    return M;
}