#pragma once

#include <cassert>  // for assert
#include <iostream>
#include <vector>

#include "quickcsv.h"

void test_example1(std::string const& filename) {
    // get all columns: symbol,open,high,low,close,volume
    // the parsing types is: <std::string, double, int> related to column index
    auto [symbol_vec, open_vec, high_vec, low_vec, close_vec, volume_vec] = quickcsv::read_csv<std::string, double, double, double, double, int>(filename);

    assert(typeid(symbol_vec) == typeid(std::vector<std::string>));
    assert(typeid(open_vec) == typeid(std::vector<double>));
    assert(typeid(high_vec) == typeid(std::vector<double>));
    assert(typeid(low_vec) == typeid(std::vector<double>));
    assert(typeid(close_vec) == typeid(std::vector<double>));
    assert(typeid(volume_vec) == typeid(std::vector<int>));

    size_t vect_size = symbol_vec.size();
    for (unsigned i = 0; i < vect_size; ++i) {
        std::cout << symbol_vec[i] << '\t';
        std::cout << open_vec[i] << '\t';
        std::cout << high_vec[i] << '\t';
        std::cout << low_vec[i] << '\t';
        std::cout << close_vec[i] << '\t';
        std::cout << volume_vec[i] << '\n';
    }
}
