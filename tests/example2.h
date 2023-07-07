#pragma once

#include <iostream>

#include "quickcsv.h"

void test_example2(std::string const& filename) {
    // get first three colums: symbol,open,high
    // the parsing types is: <std::string, double, int> related to column index
    auto [symbol_vec, close_vec, volume_vec] = quickcsv::read_csv<std::string, double, int>(filename);

    for (unsigned i = 0; i < symbol_vec.size(); ++i) {
        std::cout << symbol_vec[i] << '\t' << close_vec[i] << '\t' << volume_vec[i] << '\n';
    }
}
