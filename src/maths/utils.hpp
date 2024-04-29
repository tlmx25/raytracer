/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** utils
*/

#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "interval.hpp"
