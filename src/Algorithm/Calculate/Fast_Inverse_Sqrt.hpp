/**
 * @file Fast_Inverse_Sqrt.hpp
 * @author John Carmack (id Software)
 * @brief
 * @version 0.1
 * @date 2022-09-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = *(long*)&y;            // evil floating point bit level hacking
    i  = 0x5f3759df - (i >> 1); // what the fuck?
    y  = *(float*)&i;
    y  = y * (threehalfs - (x2 * y * y)); // 1st iteration
    // y = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}