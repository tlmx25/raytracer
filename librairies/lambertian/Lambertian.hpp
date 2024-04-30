/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

#include <libconfig.h++>
#include "vec3.hpp"
#include "Imaterial.hpp"
#define UNUSED __attribute__((unused))

class Lambertian : public IMaterial {
  public:
    Lambertian(const color& albedo) : albedo(albedo) {}
    Lambertian(const libconfig::Setting &settings) {
        try {
            albedo = color(settings["albedo"][0], settings["albedo"][1], settings["albedo"][2]);
        } catch(const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Lambertian: Missing 'albedo' setting in configuration." << std::endl;
            std::cerr << "example : Lambertian = { albedo = { 0.5, 0.5, 0.5 } }" << std::endl;
            throw nfex;
        }
    }

    virtual bool scatter(UNUSED const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override;

  private:
    color albedo;
};

extern "C" IMaterial *entryPointLambertian(const libconfig::Setting &settings);
