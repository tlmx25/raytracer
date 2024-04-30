/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Imateril
*/

#pragma once

    #include "Utils.hpp"
    #include "Color.hpp"
    #include "Ray.hpp"
    #include "HitRecord.hpp"

class IMaterial {
  public:
    virtual ~IMaterial() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const = 0;
};
