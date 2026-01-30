#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <format>
//****************************************************************************************************
std::vector<unsigned char> from_hex_codes(std::string value)
{
    #pragma region Inital variables
    std::vector<unsigned char> result;

    bool gotSymbol = false;
    char digit[] = { '\0', '\0', '\0' };
    #pragma endregion

    #pragma region Main loop
    for(auto&& symbol : value)
    {
        if(!std::isxdigit(symbol))
        {
            if(gotSymbol)
                throw std::exception("Invalid input data");

            continue;
        }

        switch(gotSymbol)
        {
            case true:
                digit[1] = symbol;
                result.push_back((unsigned char)std::stoul(digit, nullptr, 16));
                gotSymbol = false;
                break;
            case false:
                digit[0] = symbol;
                gotSymbol = true;
                break;
        }
    }
    #pragma endregion

    #pragma region Check for validity
    if(gotSymbol)
        throw std::exception("Invalid input data");
    #pragma endregion

    return result;
}
//****************************************************************************************************
std::string hex_codes(std::vector<unsigned char> value, bool separator = true)
{
    std::stringstream stream;
    stream << std::uppercase << std::setfill('0') << std::hex;

    // It is hard to use "std::copy" here due to fact that "setw" flag is not preserved
    for(unsigned char element : value)
    {
        if(separator)
        {
            if((size_t)stream.tellp())
                stream << " ";
        }

        stream << std::setw(2) << (int)element;
    }

    return stream.str();
}
//****************************************************************************************************
void process_from(std::wstring path, std::wstring output)
{
    #pragma region Aux lambda
    auto error = [](std::string_view message){ std::cout << message << std::endl; };
    #pragma endregion

    #pragma region Get input data
    std::ifstream stream(path.data(), std::ios::in | std::ios::binary | std::ios::ate);
    if(stream.is_open() == false)
        return error("Cannot open data file");

    auto size = stream.tellg();

    std::string stringData;
    stringData.resize(size);

    stream.seekg(0);
    stream.read(stringData.data(), size);
    #pragma endregion

    #pragma region Convert input and store result
    try
    {
        auto converted = from_hex_codes(stringData);

        std::ofstream outfile(output, std::ios::out | std::ios::binary);
        if(!outfile.is_open())
            throw std::exception("Cannot create file");

        outfile.write((char*)converted.data(), converted.size());
        outfile.flush();
        outfile.close();
    }
    catch(std::exception ex)
    {
        return error(std::format("Exception: {}", ex.what()));
    }
    catch(...)
    {
        return error("UNKNOWN EXCEPTION");
    }
    #pragma endregion
}
//****************************************************************************************************
void process_to(std::wstring path, std::wstring output, bool separator = true)
{
    #pragma region Aux lambda
    auto error = [](std::string_view message){ std::cout << message << std::endl; };
    #pragma endregion

    #pragma region Get input data
    std::ifstream stream(path.data(), std::ios::in | std::ios::binary | std::ios::ate);
    if(stream.is_open() == false)
        return error("Cannot open data file");

    auto size = stream.tellg();
    std::vector<unsigned char> data(size);

    stream.seekg(0);
    stream.read((char*)data.data(), size);
    #pragma endregion

    #pragma region Convert input and store result
    try
    {
        auto converted = hex_codes(data, separator);

        std::ofstream outfile(output, std::ios::out | std::ios::binary);
        if(!outfile.is_open())
            throw std::exception("Cannot create file");

        outfile.write((char*)converted.data(), converted.size());
        outfile.flush();
        outfile.close();
    }
    catch(std::exception ex)
    {
        return error(std::format("Exception: {}", ex.what()));
    }
    catch(...)
    {
        return error("UNKNOWN EXCEPTION");
    }
    #pragma endregion
}
//****************************************************************************************************
void usage()
{
    std::cout << std::endl;
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
    std::cout << std::endl;
}
//****************************************************************************************************
int wmain(int argc, wchar_t* argv[])
{
    if(argc == 4)
    {
        std::wstring key = argv[1];

        if(key == L"-from")
        {
            process_from(argv[2], argv[3]);
            return 0;
        }
        if(key == L"-to1")
        {
            process_to(argv[2], argv[3]);
            return 0;
        }
        if(key == L"-to2")
        {
            process_to(argv[2], argv[3], false);
            return 0;
        }
    }

    usage();
    return 0;
}
//****************************************************************************************************
