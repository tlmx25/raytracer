/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

#include "vec3.hpp"
#include "Imaterial.hpp"
#define UNUSED __attribute__((unused))

class Lambertian : public IMaterial {
  public:
    Lambertian(const color& albedo) : albedo(albedo) {}

    virtual bool scatter(UNUSED const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const {
        auto scatter_direction = rec.normal + random_unit_vector();

         if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

  private:
    color albedo;
};

//class metal : public IMaterial {
//  public:
//    metal(const color& albedo) : albedo(albedo) {}
//
//    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
//    const {
//        vec3 reflected = reflect(r_in.direction(), rec.normal);
//        scattered = ray(rec.p, reflected);
//        attenuation = albedo;
//        return true;
//    }
//
//  private:
//    color albedo;
//};
