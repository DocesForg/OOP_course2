#include "Sand.h"
#include "BMP.h"

#include <cassert>
#include <cinttypes>
#include <cstring>

using namespace std;
                                                                                                   // (new type_grain[height * width])
Sand::Sand(decltype(height) height, decltype(width) width) : height(height), width(width), grains((type_grain*)calloc(height * width, sizeof(type_grain))) {
    if(!grains)
        throw bad_alloc{};
}

Sand::~Sand()
{
    free(grains);   //delete[] grains;
}

bool Sand::from_file(const char *name) {
    FILE *in = fopen(name, "r");
    if (in == nullptr)
        return false;

    type_sizes y, x;
    type_grain n;
    while (fscanf(in, "%" SP_TYPE_SIZES "\t%" SP_TYPE_SIZES "\t%" SP_TYPE_GRAIN "\n", &y, &x, &n) == 3) {
        set(y, x, n);
    }

    fclose(in);
    return true;
}

bool Sand::save_to_file(const char *name) const {
    FILE *out = fopen(name, "w");
    if (out == nullptr)
        return false;

    for (type_sizes i = 0; i < height; i++) {
        for (type_sizes j = 0; j < width; j++) {
            fprintf(out, "%" SP_TYPE_SIZES "\t%" SP_TYPE_SIZES "\t%" SP_TYPE_GRAIN "\n", i, j, get(i, j));
        }
    }

    fclose(out);
    return true;
}

bool Sand::save_to_bmp(unsigned long long iter, const char *folder) const {
    char full_name[1024];
    sprintf(full_name, "%s%llu.bmp", folder, iter);
    return save_array_to_BMP<type_sizes, type_grain>(full_name, height, width, grains);
}

bool Sand::step() {
    Sand next_state(shift_top + height + shift_bot, shift_left + width + shift_right);

    bool is_stable = true;
    for(size_t i = 0; i < height; i++)
    {
        for(size_t j = 0; j < width; j++)
        {
            if(get(i, j) >= 4)
            {
                next_state.add(shift_top + i - 1,   shift_left + j      );
                next_state.add(shift_top + i,       shift_left + j - 1  );
                next_state.add(shift_top + i + 1,   shift_left + j      );
                next_state.add(shift_top + i,       shift_left + j + 1  );
                next_state.get(shift_top + i,       shift_left + j      ) += get(i, j) - 4;
                is_stable = false;
            }
            else
            {
                next_state.add(shift_top + i, shift_left + j, get(i, j));
            }
        }
    }


    if (!is_stable)
        swap(next_state);

    return is_stable;
}

void Sand::swap(Sand &other) {
    std::swap(height, other.height);
    std::swap(width, other.width);
    std::swap(grains, other.grains);

    std::swap(shift_top, other.shift_top);
    std::swap(shift_left, other.shift_left);
    std::swap(shift_right, other.shift_right);
    std::swap(shift_bot, other.shift_bot);
}

void Sand::check_borders(type_sizes y, type_sizes x, type_grain val)
{
    if(val >= 4)
    {
        if(y == 0)
            shift_top = true;
        if(y == height - 1)
            shift_bot = true;
        if(x == 0)
            shift_left = true;
        if(x == width - 1)
            shift_right = true;
    }
}

void Sand::set(type_sizes y, type_sizes x, type_grain val) {
    check_borders(y, x, grains[y*height + x] = val);
}

void Sand::add(type_sizes y, type_sizes x, type_grain val) {
    check_borders(y, x, grains[y*height + x] += val);
}

void Sand::add(type_sizes y, type_sizes x) {
    check_borders(y, x, grains[y*height + x] += 1);
}

type_grain &Sand::get(type_sizes y, type_sizes x) const {
    return grains[y*height + x];
}

//cout << a << b;
std::ostream &operator<<(std::ostream &stream, const Sand &sand) {
    for(size_t i = 0; i < sand.height; i++)
    {
        for(size_t j = 0; j < sand.width; j++) {
            stream << sand.get(i, j) << " ";
        }
        stream << "\n";
    }
    return stream;
}