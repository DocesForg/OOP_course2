#pragma once
#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <cstdio>


#define SIZE_PIXEL_BIT (4)      ///4 or 24


#if SIZE_PIXEL_BIT == 4
constexpr unsigned char BMP_Header[] =
        {0x42, 0x4D,
         0x00, 0x00, 0x00, 0x00,
         0x00, 0x00,
         0x00, 0x00,
         0x36, 0x00, 0x00, 0x00};
constexpr unsigned char DIB_Header[] =
        {0x28, 0x00, 0x00, 0x00,
         0x02, 0x00, 0x00, 0x00,    /// Width pix
         0x02, 0x00, 0x00, 0x00,    /// Height pix
         0x01, 0x00,
         0x04, 0x00,                ///pix bit size
         0x00, 0x00, 0x00, 0x00,
         0x80, 0x46, 0x00, 0x00,
         0x13, 0x0B, 0x00, 0x00,
         0x13, 0x0B, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00,

         0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x80, 0x00,
         0x00, 0x80, 0x00, 0x00,
         0x00, 0x80, 0x80, 0x00,
         0x80, 0x00, 0x00, 0x00,
         0x80, 0x00, 0x80, 0x00,
         0x80, 0x80, 0x00, 0x00,
         0x80, 0x80, 0x80, 0x00,
         0xC0, 0xC0, 0xC0, 0x00,
         0x00, 0x00, 0xFF, 0x00,
         0x00, 0xFF, 0x00, 0x00,
         0x00, 0xFF, 0xFF, 0x00,
         0xFF, 0x00, 0x00, 0x00,
         0xFF, 0x00, 0xFF, 0x00,
         0xFF, 0xFF, 0x00, 0x00,
         0xFF, 0xFF, 0xFF, 0x00};


enum Color {
    WHITE = 15,
    GREEN = 6,
    VIOLET = 5,
    YELLOW = 11,
    BLACK = 0
};
#elif SIZE_PIXEL_BIT == 24
constexpr unsigned char BMP_Header[] =
        {0x42, 0x4D,
         0x00, 0x00, 0x00, 0x00,
         0x00, 0x00,
         0x00, 0x00,
         0x36, 0x00, 0x00, 0x00};
constexpr unsigned char DIB_Header[] =
        {0x28, 0x00, 0x00, 0x00,
         0x03, 0x00, 0x00, 0x00,    /// Width pix
         0x03, 0x00, 0x00, 0x00,    /// Height pix
         0x01, 0x00,
         0x18, 0x00,                ///24 bits for one pixel (3 * 8)
         0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00,
         0x13, 0x0B, 0x00, 0x00,
         0x13, 0x0B, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00};

enum Color {
    WHITE = 0xFFFFFF,
    GREEN = 0x408000,
    VIOLET = 0x7608AA,
    YELLOW = 0xFFD800,
    BLACK = 0x000000
};
#endif


constexpr unsigned char size_pixel_bit = SIZE_PIXEL_BIT;
constexpr unsigned char k_row = 4;

#define MAX(x, y) x > y ? (x) : (y)
#define MIN(x, y) x < y ? (x) : (y)



template<typename T_size, typename T_data>
bool save_array_to_BMP(char *name, T_size height, T_size width, T_data *data)
{
    size_t row_size = (SIZE_PIXEL_BIT * width + 7)/8;
    size_t row_padding_size = (k_row - (row_size % k_row)) % k_row;
    row_size += row_padding_size;
    size_t bitmap_size = row_size * height;
    size_t all_bmp_size = sizeof(BMP_Header) + sizeof(DIB_Header) + bitmap_size;

/// auto *all_bmp = (uint8_t *)malloc(all_bmp_size);
    auto *all_bmp = static_cast<uint8_t *> (malloc(all_bmp_size));

    if(all_bmp == nullptr)
        return false;

    size_t pos = 0;
    memcpy(all_bmp, &BMP_Header, sizeof(BMP_Header));
    pos += sizeof(BMP_Header);
    memcpy(all_bmp + pos, &DIB_Header, sizeof(DIB_Header));
    pos += sizeof(DIB_Header);

    memcpy(all_bmp + sizeof(BMP_Header) + 4, &width, MIN(sizeof(T_size), 4));
    memcpy(all_bmp + sizeof(BMP_Header) + 8, &height, MIN(sizeof(T_size), 4));
    memcpy(all_bmp + sizeof(BMP_Header) + 14, &size_pixel_bit, MIN(sizeof(T_size), 1));

    for(size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Color color;
            switch (data[i*height + j]) {
                case 0:
                    color = WHITE;
                    break;
                case 1:
                    color = GREEN;
                    break;
                case 2:
                    color = VIOLET;
                    break;
                case 3:
                    color = YELLOW;
                    break;
                default:
                    color = BLACK;
                    break;
            }

            #if SIZE_PIXEL_BIT == 4
                if(j%2== 0)
                {
                    all_bmp[pos] = color << 4;
                }
                else
                {
                    all_bmp[pos] += color;
                    pos++;
                }
            #elif SIZE_PIXEL_BIT == 24
                memcpy(all_bmp + pos, &color, 3);
                pos += 3;
            #endif

        }
        #if SIZE_PIXEL_BIT == 4
            if(width%2 == 1)
                pos++;
        #endif

        if(row_padding_size) {
            uint_fast32_t padding = 0;
            memcpy(all_bmp + pos, &padding, row_padding_size);
            pos += row_padding_size;
        }
    }

    FILE *out = fopen(name, "wb");
    if(out == nullptr)
        return false;

    fwrite(all_bmp, all_bmp_size, 1, out);

    fclose(out);
    free(all_bmp);
    return true;
}
