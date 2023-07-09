#pragma once

#include <iostream>

#include "quickcsv.h"

template <typename T>
void test_converter(std::string const& str) {
    auto val = quickcsv::Converter<T>::convert("123456");
    std::cout << typeid(val).name() << '\t' << val << '\n';
}

void test_read_raw_csv(std::string const& filename) {
    auto table = quickcsv::read_raw_csv(filename);

    for (auto&& row : table) {
        for (auto&& cell : row) {
            std::cout << cell << '\t';
        }
        std::cout << '\n';
    }
}
