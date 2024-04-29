/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** raytracer
*/

#pragma once

#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

// Common Headers

#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "interval.hpp"
#endif //RAYTRACER_RAYTRACER_HPP
