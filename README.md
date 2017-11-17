# [Cpp-Guards](https://github.com/offa/cpp-guards)

[![Build Status](https://travis-ci.org/offa/cpp-guards.svg?branch=master)](https://travis-ci.org/offa/cpp-guards)
[![GitHub release](https://img.shields.io/github/release/offa/cpp-guards.svg)](https://github.com/offa/cpp-guards/releases)
[![License](https://img.shields.io/badge/license-GPLv3-yellow.svg)](LICENSE)
![C++](https://img.shields.io/badge/c++-14-green.svg)

C++ RAII template classes.


## Requirements

- [**CMake**](http://www.cmake.org/)


## Testing

```
mkdir build && cd build
cmake ..
make
make unittest
```

It's also possible to use `make test` / `ctest`, this will execute the tests using `ctest`.


## Examples


```cpp
#include "guards/Guards.h"
#include <iostream>
#include <sys/socket.h>

void example()
{
    using namespace guards;
    auto guard = makeScopeGuard([]{ std::cout << "The End\n"; });

    // ...
    // 'The End' is printed on guard's destruction
}

void example2()
{
    using namespace guards;
    auto guard1 = makeTransactionGuard([]{ std::cout << "Guard #1\n"; });

    auto guard2 = makeTransactionGuard([]{ std::cout << "Guard #2\n"; });
    guard2.commit(); // Disarm

    // ...
    // Only 'Guard #1' is printed
}

void example3()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    // Ensure 'fd' is closed in any case
    auto guard = makeScopeGuard([&fd] { close(fd); });

    // ...

    /*
     * The socket is closed as `guard` is destructed,
     * eg. out-of-scope or by an exception.
     */
}
```



## License

**GNU General Public License (GPL)**

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


