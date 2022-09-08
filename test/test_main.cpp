//
// Created by Stephan on 08.09.2022.
//

#include "gtest/gtest.h"
#include "compressed_matrix_lib/matrixes.h"
#include <compressed_matrix_lib/input.h>

TEST(read_matrix, test) {
    // CSR_matrix * M = read_matrix();
    // destruct_CSR_matrix(M);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}