#include "example1.h"
#include "example2.h"
#include "example3.h"
#include "example4.h"
#include "test_func.h"

int main() {
    // test_converter<int>("12345");
    // test_converter<double>("12346.1");
    // test_converter<std::string>("12346.1");
    // test_read_raw_csv("test.csv");

    test_example1("test.csv");
    test_example2("test.csv");
    test_example3("test.csv");
    test_example4("test.csv");
}