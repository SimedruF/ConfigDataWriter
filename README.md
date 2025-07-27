# ConfigDataWriter

ConfigDataWriter is a C++ class designed to save and load configuration data in various formats, including binary, text, CSV, and INI files. It provides a flexible interface for managing application settings and data serialization in C++ projects.

## Features
- Save and load configuration data in binary format
- Save and read simple integer configuration files
- Save integer and float data in CSV format
- Save and parse INI configuration files
- Set and retrieve configuration buffers
- Tokenize and read CSV files

## Usage
The main usage is demonstrated in `test.cpp`, which shows how to:
- Create configuration data structures
- Save and load configuration data in different formats
- Read and write CSV and INI files

### Example
```cpp
#include "ConfigDataWriter.h"

ConfigDataWriter config("config.cfg");
ConfigData data = { ... };
config.SaveCfgDataBinary(data);
config.LoadCfgDataBinary(data);
```

## File & Folder Overview
- `source/ConfigDataWriter.h`, `source/ConfigDataWriter.cpp`, `source/ConfigDataWriterStruct.h`: Main class and configuration structure implementation
- `test/test.cpp`, `test/test.h`: Main test file and test structures
- `test/test_ini.cpp`: Dedicated test for INI file operations
- `test/data/`: Contains all test data files:
    - `app_cfg.csv`, `integer_data.csv`, `float_data.csv`: Example CSV files
    - `program.ini`: Example INI configuration file
    - `ea_test1.cfg`, `ea_test1.txt`: Example config files
- `build/build.sh`, `build/build.bat`: Build scripts for Linux and Windows
- `build/`: Compiled executables and build configuration files

## Build
To build the project on Linux:
```bash
sh build.sh
```
On Windows:
```bat
build.bat
```

## License

This project is licensed under the MIT License. See below:

```
MIT License

Copyright (c) 2025 SimedruF

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
