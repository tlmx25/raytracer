/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** utils
*/

#include "Utils.hpp"

double Utils::degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

double Utils::random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

double Utils::random_double(double min, double max)
{
    return min + (max - min) * random_double();
}
