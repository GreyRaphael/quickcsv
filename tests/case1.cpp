#include <iostream>

#include "quickcsv.h"

template <typename T>
void test_converter(std::string const& str) {
    auto val = quickcsv::Converter<T>::convert("123456");
    std::cout << typeid(val).name() << '\t' << val << '\n';
}

void test_read_csv(std::string const& filename) {
    auto table = quickcsv::read_csv(filename);

    for (auto&& row : table) {
        for (auto&& cell : row) {
            std::cout << cell << '\t';
        }
        std::cout << '\n';
    }
}

int main() {
    // test_converter<int>("12345");
    // test_converter<double>("12346.1");
    // test_converter<std::string>("12346.1");
    test_read_csv("test.csv");
}
