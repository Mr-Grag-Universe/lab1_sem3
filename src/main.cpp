#include <iostream>

#include "matrixes.h"
#include "input.h"


int main() {
    //std::string input;
    MyMatrixes::CSR_matrix * M = nullptr;
    MyMatrixes::ListMatrix * LM = nullptr;
    try {
        std::cout << "Введите вашу матрицу" << std::endl;
        M = MyMatrixes::read_compressed_matrix(); //MyMatrixes::read_matrix();
        if (M == nullptr) {
            std::cout << "you failed input. try again next time" << std::endl;
            return 1;
        }
        print_CSR_matrix(M);
        LM = cut_CSR_matrix(M);
    } catch (std::bad_alloc & ba) {
        std::cout << "not enough memory for this program. sorry =(" << std::endl;
        if (M)
            MyMatrixes::destruct_CSR_matrix(M);
        if (LM)
            MyMatrixes::destruct_list_matrix(LM);
        return 1;
    } catch (std::invalid_argument & ia) {
        std::cerr << ia.what() << std::endl;
        return 1;
    }


    std::cout << "Ваша обрезанная матрица:\n" << std::endl;
    print_list_matrix(LM);

    std::cout << "Введите любую строку, чтобы завершить работу программы";

    destruct_list_matrix(LM);
    destruct_CSR_matrix(M);
    return 0;
}
