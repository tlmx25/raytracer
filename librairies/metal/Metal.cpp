/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Metal.hpp"

Metal::Metal(const libconfig::Setting &settings)
{
    try {
        albedo = Color(settings["metal"][0], settings["metal"][1], settings["metal"][2]);
        fuzz = settings["metal"][3];
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Metal: Missing 'albedo' setting in configuration." << std::endl;
        std::cerr << "example : Metal = { albedo = { 0.5, 0.5, 0.5 } fuzz = 0.5 }" << std::endl;
        throw nfex;
    }
}

Metal::~Metal()
{
}

bool Metal::scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

extern "C" IMaterial *entryPointMetal(const libconfig::Setting &settings)
{
    return (new Metal(settings));
}
