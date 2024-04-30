/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Lambertian.hpp"

Lambertian::Lambertian(const Color& albedo) : albedo(albedo)
{

}

Lambertian::Lambertian(const libconfig::Setting &settings)
{
    try {
        albedo = Color(settings["albedo"][0], settings["albedo"][1], settings["albedo"][2]);
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Lambertian: Missing 'albedo' setting in configuration." << std::endl;
        std::cerr << "example : Lambertian = { albedo = { 0.5, 0.5, 0.5 } }" << std::endl;
        throw nfex;
    }
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

extern "C" IMaterial *entryPointLambertian(const libconfig::Setting &settings)
{
    return (new Lambertian(settings));
}
