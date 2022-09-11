//
// Created by Stephan on 10.09.2022.
//
#include <iostream>
#include <string>
#include <cstring>

#include "matrixes.h"

using namespace MyMatrixes;


void * MyMatrixes::insert(void * array, size_t len, void * sub_array, size_t sub_len, size_t offset) {
    char * tmp = new char[len+sub_len];
    std::memcpy(tmp, array, offset);
    std::memcpy(tmp + offset + sub_len, tmp + offset, len-offset);
    std::memcpy(tmp + offset, sub_array, sub_len);
    return (void *) tmp;
}

int MyMatrixes::item_comp(const void *a, const void *b) {
    Item * item1 = (Item*) a;
    Item * item2 = (Item*) b;
    if (item1->i != item2->i)
        return (int) ((long long) item1->i - (long long) item2->i);
    return (int) ((long long) item1->j - (long long) item2->j);
}

