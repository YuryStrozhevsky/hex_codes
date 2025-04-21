# hex_codes

Aux tool to work with hexadecimal codes. 
Sometimes I need to encode binary data to hex codes, or decode hex coded to binary. In order to do that I made the simple tool.

# Usage
```cpp
    std::cout << "Convert to and from hex codes" << std::endl;
    std::cout << "(c) 2025, Yury Strozhevsky (yury@strozhevsky.com)" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "\tConvert from hex to binary:" << std::endl;
    std::cout << "\t\thex_codes -from <path_to_input> <path_to_output>" << std::endl;
    std::cout << "\tConvert from binary to hex (with \"space\" as a delimiter):" << std::endl;
    std::cout << "\t\thex_codes -to1 <path_to_input> <path_to_output>" << std::endl;
    std::cout << "\tConvert from binary to hex (without any delimiters):" << std::endl;
    std::cout << "\t\thex_codes -to2 <path_to_input> <path_to_output>" << std::endl;
```

# License
(c) 2025, Yury Strozhevsky, [yury@strozhevsky.com](mailto:yury@strozhevsky.com)

Anyone allowed to do whatever he/she want with the code.