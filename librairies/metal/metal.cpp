/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** metal
*/

#include "metal.hpp"

bool Metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const
{
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
}
