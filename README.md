# Quick CSV

- [Quick CSV](#quick-csv)
  - [Installation](#installation)
  - [Usage](#usage)

quickcsv is an easy-to-use C++ CSV reader and parser library. It supports C++17 (and later), is header-only and comes with a basic test suite.

## Installation

Simply copy [src/quickcsv.h](src/quickcsv.h) to your project/include directory and include it.

## Usage

[example1](tests/example1.h): Reading all data from the following `test.csv`.

```csv
symbol,open,high,low,close,volume
AAPL,123.750000,127.930000,122.790001,127.790001,116307900
MSFT,235.899994,237.470001,233.149994,236.940002,25324000,
IBM,115.057358,116.940727,114.588913,115.430206,5977367
TSLA,230.036667,239.666672,228.350006,239.476669,81408600
```

```cpp
#include <cassert>  // for assert
#include <iostream>
#include <vector>

#include "quickcsv.h"

void test_example1(std::string const& filename) {
    // get all columns: symbol,open,high,low,close,volume
    // the parsing types is: <std::string, double, double, double, double, int> respectively
    auto [symbol_vec, open_vec, high_vec, low_vec, close_vec, volume_vec] = quickcsv::read_csv<std::string, double, double, double, double, int>(filename);

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

int main(){
    test_example1("test.csv");
}
```

```bash
# output
AAPL    123.75  127.93  122.79  127.79  116307900
MSFT    235.9   237.47  233.15  236.94  25324000
IBM     115.057 116.941 114.589 115.43  5977367
TSLA    230.037 239.667 228.35  239.477 81408600
```

[example2](tests/example2.h): Reading first 3 columns from the following `test.csv`

```csv
symbol,open,high,low,close,volume
AAPL,123.750000,127.930000,122.790001,127.790001,116307900
MSFT,235.899994,237.470001,233.149994,236.940002,25324000,
IBM,115.057358,116.940727,114.588913,115.430206,5977367
TSLA,230.036667,239.666672,228.350006,239.476669,81408600
```

```cpp
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

int main(){
    test_example1("test.csv");
}
```

```bash
# output
AAPL    123.75  127
MSFT    235.9   237
IBM     115.057 116
TSLA    230.037 239
```

[example3](tests/example3.h): Reading specified columns from the following `test.csv`

```csv
symbol,open,high,low,close,volume
AAPL,123.750000,127.930000,122.790001,127.790001,116307900
MSFT,235.899994,237.470001,233.149994,236.940002,25324000,
IBM,115.057358,116.940727,114.588913,115.430206,5977367
TSLA,230.036667,239.666672,228.350006,239.476669,81408600
```

```cpp
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
```

```bash
# output
AAPL    127.79  116307900
MSFT    236.94  25324000
IBM     115.43  5977367
TSLA    239.477 81408600
```