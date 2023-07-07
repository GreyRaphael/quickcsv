/*
 * quickcsv.h
 *
 * URL:      https://github.com/GreyRaphael/quickcsv
 * Version:  1.0
 *
 * Copyright (C) 2023-2023 Wei Ge
 * All rights reserved.
 *
 * quick is distributed under the BSD 3-Clause license, see LICENSE for details.
 *
 */
#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace quickcsv {

inline auto read_raw_csv(std::string const& filename, std::vector<std::string> usecols = {}, size_t skiprows = 0, char sep = ',') {
    // read csv row by row, support utf8
    // example: read_csv("test.csv", {"last", "time"}, ',');
    bool file_exist = std::filesystem::exists(filename);
    if (!file_exist) {
        std::cout << filename << " not exist!\n";
        std::exit(EXIT_SUCCESS);
    }

    std::ifstream file(filename, std::ios::in);
    std::string line;
    std::stringstream ss;
    std::string cell;

    for (size_t i = 0; i < skiprows; ++i) {
        std::getline(file, line);
    }

    // read headers
    std::vector<std::string> header_vector;
    header_vector.reserve(8);
    std::getline(file, line);
    ss << line;
    while (std::getline(ss, cell, sep)) {
        header_vector.emplace_back(cell);
    }
    ss.clear();

    usecols = (usecols.size() > 0) ? usecols : header_vector;

    // process headers
    std::vector<int> index_vect;
    index_vect.reserve(header_vector.size());

    for (auto const& hearder_name : header_vector) {
        auto it = std::find(usecols.begin(), usecols.end(), hearder_name);
        if (it != usecols.end()) {
            index_vect.emplace_back(std::distance(usecols.begin(), it));
        } else {
            index_vect.emplace_back(-1);
        }
    }

    std::vector<std::vector<std::string>> table;
    table.reserve(32);
    uint col_nums = usecols.size();
    while (std::getline(file, line)) {
        if (line.size() < 1) {
            break;
        }
        std::vector<std::string> row_vector(col_nums);

        ss << line;
        for (uint i = 0; std::getline(ss, cell, sep); ++i) {
            int col_index = index_vect[i];
            if (col_index != -1) {
                row_vector[col_index] = cell;
            }
        }
        ss.clear();

        table.emplace_back(row_vector);
    }
    file.close();

    return table;
}

template <typename T>
struct Converter {
    static constexpr auto convert(const std::string& str) {
        if constexpr (std::is_same_v<T, int>)
            return std::stoi(str);
        else if constexpr (std::is_same_v<T, long>)
            return std::stol(str);
        else if constexpr (std::is_same_v<T, long long>)
            return std::stoll(str);
        else if constexpr (std::is_same_v<T, unsigned>)
            return std::stoul(str);
        else if constexpr (std::is_same_v<T, unsigned long>)
            return std::stoul(str);
        else if constexpr (std::is_same_v<T, unsigned long long>)
            return std::stoull(str);
        else if constexpr (std::is_same_v<T, char>)
            return str[0];
        else if constexpr (std::is_same_v<T, float>)
            return std::stof(str);
        else if constexpr (std::is_same_v<T, double>)
            return std::stod(str);
        else if constexpr (std::is_same_v<T, long double>)
            return std::stold(str);
        else
            return str;
    }
};

template <typename... Ts>
struct Parser {
    constexpr static int N = sizeof...(Ts);
    // the inline specifier allows the static member containter to be defined within the class itself
    inline static std::tuple<std::vector<Ts>...> CONTAINER{};

    template <int... I>
    static void ParseTable(const std::vector<std::vector<std::string>>& table, std::integer_sequence<int, I...>) {
        (std::get<I>(CONTAINER).reserve(table.size()), ...);
        for (const auto& row : table) {
            (std::get<I>(CONTAINER).push_back(Converter<Ts>::convert(row[I])), ...);
        }
    }

    static auto Parse(const std::vector<std::vector<std::string>>& table) {
        ParseTable(table, std::make_integer_sequence<int, N>());
        return CONTAINER;
    }
};

struct Param {
    char sep = ',';
    size_t skiprows = 0;
    std::vector<std::string> usecols{};
};

template <typename... Ts>
auto read_csv(std::string const& filename, Param const& parameters) {
    auto table = read_raw_csv(filename, parameters.usecols, parameters.skiprows, parameters.sep);
    return Parser<Ts...>::Parse(table);
}

}  // namespace quickcsv
