/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "SolidColor.hpp"

Solid_color::Solid_color(const Color& albedo) : albedo(albedo)
{

}

Solid_color::Solid_color(double red, double green, double blue) : Solid_color(Color(red,green,blue))
{
    
}

Color Solid_color::value(double u, double v, const Point3& p) const
{
    return albedo;
}