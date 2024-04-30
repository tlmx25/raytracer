/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

#include "utils.hpp"
#include "hittable.hpp"
#include "Imaterial.hpp"

class Metal : public Material {
  public:
    Metal(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override;

  private:
    color albedo;
};

extern "C" Arcade::IDisplay *entryPointDisplay();