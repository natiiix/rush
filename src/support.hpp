#pragma once

#include <vector>
#include <algorithm>

namespace support
{
template <class T, class U, class F>
void map(const std::vector<T> src, std::vector<U> &dest, const F f)
{
    dest.resize(src.size());
    std::transform(src.begin(), src.end(), dest.begin(), f);
}

template <class T>
std::vector<T> toVector(const T arr[], const int length)
{
    if (length < 0)
    {
        return nullptr;
    }

    std::vector<T> vec(arr, arr + length);
    return vec;
}
}
