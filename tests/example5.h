#pragma once

#include <iostream>

#include "quickcsv.h"

void test_example5(std::string const& filename) {
    auto [stockcode_vec, name_vec, close_vec, volume_vec] = quickcsv::read_csv<std::string, std::string, double, int>(filename);

    for (unsigned i = 0; i < stockcode_vec.size(); ++i) {
        std::cout << stockcode_vec[i] << '\t';
        std::cout << name_vec[i] << '\t';
        std::cout << close_vec[i] << '\t';
        std::cout << volume_vec[i] << '\n';
    }
}
