# Quick CSV

- [Quick CSV](#quick-csv)
  - [Installation](#installation)
  - [Usage](#usage)

quickcsv is an easy-to-use C++ CSV reader and parser library. It supports C++17 (and later), is header-only and comes with a basic test suite.

## Installation

Simply copy [src/quickcsv.h](src/quickcsv.h) to your project/include directory and include it.

## Usage

Here is a simple example reading a CSV file with many types.

| symbol | open       | high       | low        | close      | volume    |
| ------ | ---------- | ---------- | ---------- | ---------- | --------- |
| AAPL   | 123.75     | 127.93     | 122.790001 | 127.790001 | 116307900 |
| MSFT   | 235.899994 | 237.470001 | 233.149994 | 236.940002 | 25324000  |
| IBM    | 115.057358 | 116.940727 | 114.588913 | 115.430206 | 5977367   |
| TSLA   | 230.036667 | 239.666672 | 228.350006 | 239.476669 | 81408600  |

```csv
; test.csv
symbol,open,high,low,close,volume
AAPL,123.750000,127.930000,122.790001,127.790001,116307900
MSFT,235.899994,237.470001,233.149994,236.940002,25324000,
IBM,115.057358,116.940727,114.588913,115.430206,5977367
TSLA,230.036667,239.666672,228.350006,239.476669,81408600
```

```cpp
#include <iostream>
#include <cassert>
#include <vector>

int main() {
    // get_csv(filename, usecols, skiprows)
    // @filename="test.csv"
    // @usecols={"symbol", "open", "high", "low", "close", "volume"}
    // @skiprows=1
    // usecols_types: <std::string, double, double, double, double, int> 
    // return std::tuple<std::vector<std::string>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<double>,std::vector<int>>
    auto [symbol_vec, open_vec, high_vec, low_vec, close_vec, volume_vec] = get_csv<std::string, double, double, double, double, int>("test.csv", {"symbol", "open", "high", "low", "close", "volume"}, 1);

    assert(typeid(symbol_vec) == typeid(std::vector<std::string>));
    assert(typeid(open_vec) == typeid(std::vector<double>));
    assert(typeid(high_vec) == typeid(std::vector<double>));
    assert(typeid(low_vec) == typeid(std::vector<double>));
    assert(typeid(close_vec) == typeid(std::vector<double>));
    assert(typeid(volume_vec) == typeid(std::vector<int>));

    size_t vect_size = symbol_vec.size();
    for (unsigned i = 0; i < vect_size; ++i) {
        std::cout << symbol_vec[i] << '\t' << close_vec[i] << '\t' << volume_vec[i] << '\n';
    }

    // // output
    // AAPL    127.79  116307900
    // MSFT    236.94  25324000
    // IBM     115.43  5977367
    // TSLA    239.477 81408600
}
```

