#include <iostream>
#include "Sand.h"
#include <cstdio>

using namespace std;

bool compare(const char *a, const char *b)
{
    int i = 0;
    for(; a[i] != '\0' && b[i] != '\0'; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    if(a[i] != b[i])
        return false;

    return true;
}

struct Parametrs
{
    type_sizes length = 0;
    type_sizes width = 0;
    char *input_file = nullptr;
    char *output_folder = nullptr;
    unsigned long long max_iter = 1;
    unsigned long long freq  = 1;
};

bool scan_param(int argc, char** argv, Parametrs &param)
{
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-' && argv[i][1] != '\0')
        {
            int c = 1;
            if(argv[i][1] == '-')
            {
                bool is_success;
                c = 2;
                switch (argv[i][c]) {
                    case 'l':
                    {
                        is_success = compare(argv[i], "--length\0");
                        break;
                    }
                    case 'w':
                    {
                        is_success = compare(argv[i], "--width\0");
                        break;
                    }
                    case 'i':
                    {
                        is_success = compare(argv[i], "--input\0");
                        break;
                    }
                    case 'o':
                    {
                        is_success = compare(argv[i], "--output\0");
                        break;
                    }
                    case 'm':
                    {
                        is_success = compare(argv[i], "--max-iter\0");
                        break;
                    }
                    case 'f':
                    {
                        is_success = compare(argv[i], "--freq\0");
                        break;
                    }
                    default:
                        return false;
                }
                if(!is_success)
                    return false;
            }

            switch (argv[i][c]) {
                case 'l':
                {
                    sscanf(argv[i+1], "%" SP_TYPE_SIZES, &(param.length));
                    break;
                }
                case 'w':
                {
                    sscanf(argv[i+1], "%" SP_TYPE_SIZES, &(param.width));
                    break;
                }
                case 'i':
                {
                    param.input_file = argv[i+1];
                    break;
                }
                case 'o':
                {
                    param.output_folder = argv[i+1];
                    break;
                }
                case 'm':
                {
                    sscanf(argv[i+1], "%llu", &(param.max_iter));
                    break;
                }
                case 'f':
                {
                    sscanf(argv[i+1], "%llu", &(param.freq));
                    break;
                }
                default:
                    return false;
            }
            i++;
        }
    }
    return true;
}

bool save_to_bmp_message(unsigned long long i, Parametrs &param, Sand &sand)
{
    if(sand.save_to_bmp(i, param.output_folder))
        cout << "BMP, folder \"" << param.output_folder << "\" - save iteration " << i << endl;
    else
    {
        cout << "invalid output folder: \"" << param.output_folder << "\"" << endl;
        cout << "check that the symbol \'/\' is at the end!" << endl;
        return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    Parametrs param;

    if(scan_param(argc, argv, param))
    {
        cout << "Scan parametrs: success"       << endl;
        cout << "=================================" << endl;
        cout << "length: " << param.length      << endl;
        cout << "width: "  << param.width       << endl;
        cout << "input_file: ";
        if(param.input_file)
            cout << '\"' << param.input_file << '\"' << endl;
        else
            cout << "nullptr" << endl;
        cout << "output_folder: ";
        if(param.output_folder)
            cout << '\"' << param.output_folder << '\"' << endl;
        else
            cout << "nullptr" << endl;
        cout << "max_iter: "    << param.max_iter   << endl;
        cout << "freq: "        << param.freq       << endl;
        cout << "=================================" << endl << endl;
    }
    else
    {
        cout << "Scan parametrs: failed"       << endl;
        return -1;
    }

    if(param.length == 0)
    {
        cout << "parametr length is invalid:" << param.length << endl;
        return -2;
    }
    if(param.width == 0)
    {
        cout << "parametr length is invalid:" << param.width << endl;
        return -3;
    }
    if(param.output_folder == nullptr)
    {
        cout << "parametr output_folder is null" << endl;
        return -4;
    }


    Sand sand(param.length, param.width);
    if(param.input_file)
        if(!sand.from_file(param.input_file))
        {
            cout << "invalid input filename: \"" << param.input_file << "\"" << endl;
            return -5;
        }


    if(param.freq > 0)
    {
        if(!save_to_bmp_message(0, param, sand)) return -6;
        for(unsigned long long i = 1; i < param.max_iter + 1 && !sand.step(); i++)
        {
            if(i%param.freq == 0)
                if(!save_to_bmp_message(i, param, sand)) return -6;
        }
    }
    else
    {
        unsigned long long i = 1;
        for(; i < param.max_iter + 1 && !sand.step(); i++); ///step == true - stable
        if(!save_to_bmp_message(i, param, sand)) return -6;
    }
    return 0;
}