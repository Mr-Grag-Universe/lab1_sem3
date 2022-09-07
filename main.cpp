#include <iostream>
#include <string>
#include <utility>

#include "matrixes.h"
#include "input.h"


int main() {
    CSR_matrix * M = init_CSR_matrix();
    M->width = 5;
    int row1[] = {0, 1, 0, 2, 0};
    insert_row_CSR_matrix(M, row1, 0);
    int row2[] = {1, 0, 0, 0, 3};
    insert_row_CSR_matrix(M, row2, 1);
    print_CSR_matrix(M);
    destruct_CSR_matrix(M);

    M = read_matrix();
    print_CSR_matrix(M);

    ListMatrix * LM = cut_CSR_matrix(M);
    print_list_matrix(LM);

    destruct_list_matrix(LM);
    destruct_CSR_matrix(M);

    std::cin >> row1[0];

    return 0;
}
