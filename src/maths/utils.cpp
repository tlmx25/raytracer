/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** utils
*/

#include "utils.hpp"

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}
