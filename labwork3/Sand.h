#pragma once

#include <vector>
#include <sstream>
#include <cinttypes>

#define SP_TYPE_SIZES SCNuFAST16
#define SP_TYPE_GRAIN SCNuFAST64
typedef uint_fast16_t type_sizes;
typedef uint_fast64_t type_grain;

class Sand
{
    type_sizes height;   //y - length
    type_sizes width;    //x
    type_grain *grains;
    bool shift_top = false, shift_left = false;
    bool shift_right = false, shift_bot = false;

public:
    Sand(decltype(height) height, decltype(width) width);
    ~Sand();

    bool from_file(const char *name);
    bool save_to_file(const char *name) const;
    bool save_to_bmp(unsigned long long iter, const char *folder) const;
    bool step();

private:
    void swap(Sand &other);
    inline void check_borders(type_sizes y, type_sizes x, type_grain val);
    inline void set(type_sizes y, type_sizes x, type_grain val);
    inline void add(type_sizes y, type_sizes x, type_grain val);
    inline void add(type_sizes y, type_sizes x);
    inline type_grain& get(type_sizes y, type_sizes x) const;
    friend std::ostream& operator<<(std::ostream& stream, const Sand& sand);
};