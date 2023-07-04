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

namespace quickcsv {

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

}  // namespace quickcsv
