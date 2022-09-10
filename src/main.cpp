#include <iostream>

#include "matrixes.h"
#include "input.h"


int main() {
    //std::string input;

    std::cout << "Введите вашу матрицу" << std::endl;

    MyMatrixes::CSR_matrix * M = MyMatrixes::read_compressed_matrix(); //MyMatrixes::read_matrix();
    if (M == nullptr) {
        std::cout << "you failed input. try again next time" << std::endl;
        return 1;
    }
    print_CSR_matrix(M);

    MyMatrixes::ListMatrix * LM = cut_CSR_matrix(M);

    std::cout << "Ваша обрезанная матрица:\n" << std::endl;
    print_list_matrix(LM);

    std::cout << "Введите любую строку, чтобы завершить работу программы";


    destruct_list_matrix(LM);
    destruct_CSR_matrix(M);
    return 0;
}
