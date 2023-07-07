#pragma once

#include <iostream>

#include "quickcsv.h"

void test_example3(std::string const& filename) {
    // get specified columns: symbol,close,volume
    // the parsing types is: <std::string, double, int> related to column index
    // specify parameters: sep, skiprows, usecols
    quickcsv::Param parameters{
        .sep = ',',
        .skiprows = 0,
        .usecols = {"symbol", "close", "volume"},
    };
    auto [symbol_vec, close_vec, volume_vec] = quickcsv::read_csv<std::string, double, int>(filename, parameters);
    for (unsigned i = 0; i < symbol_vec.size(); ++i) {
        std::cout << symbol_vec[i] << '\t' << close_vec[i] << '\t' << volume_vec[i] << '\n';
    }
}
