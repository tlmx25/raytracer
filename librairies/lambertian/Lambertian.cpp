/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Lambertian.hpp"

bool Lambertian::scatter(UNUSED const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

extern "C" IMaterial *entryPointLambertian(const libconfig::Setting &settings)
{
    return (new Lambertian(settings));
}
