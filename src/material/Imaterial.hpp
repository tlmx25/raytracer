/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Imateril
*/

#pragma once
    #include "utils.hpp"
    #include "color.hpp"
    #include "ray.hpp"
    #include "hittable.hpp"
class IMaterial {
  public:
    virtual ~IMaterial() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};
