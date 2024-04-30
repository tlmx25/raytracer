/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertion
*/

#pragma once

#include "utils.hpp"
#include "hittable.hpp"
#include "Imaterial.hpp"

class Lambertian : public Material {
  public:
    Lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override;

  private:
    color albedo;
};
