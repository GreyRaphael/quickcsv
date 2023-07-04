#include <iostream>

#include "quickcsv.h"

template <typename T>
void test_converter(std::string const& str) {
    auto val = quickcsv::Converter<T>::convert("123456");
    std::cout << typeid(val).name() << '\t' << val << '\n';
}

int main() {
    test_converter<int>("12345");
    test_converter<double>("12346.1");
    test_converter<std::string>("12346.1");
}
