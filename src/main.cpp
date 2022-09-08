#include <iostream>

#include "matrixes.h"
#include "input.h"


int main() {
//    CSR_matrix * M = init_CSR_matrix();
//    M->width = 5;
//    int row1[] = {0, 1, 0, 2, 0};
//    insert_row_CSR_matrix(M, row1, 0);
//    int row2[] = {1, 0, 0, 0, 3};
//    insert_row_CSR_matrix(M, row2, 1);
//    print_CSR_matrix(M);
//    destruct_CSR_matrix(M);

    std::cout << "Введите вашу матрицу" << std::endl;

    MyMatrixes::CSR_matrix * M = MyMatrixes::read_matrix();
    if (M == nullptr) {
        std::cout << "you failed input. try again next time" << std::endl;
        return 1;
    }
    print_CSR_matrix(M);

    MyMatrixes::ListMatrix * LM = cut_CSR_matrix(M);

    std::cout << "Ваша обрезанная матрица:\n" << std::endl;
    print_list_matrix(LM);

    destruct_list_matrix(LM);
    destruct_CSR_matrix(M);

    return 0;
}
