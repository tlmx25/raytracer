/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ColorMat
*/


#include "IMaterial.hpp"

class ColorMat : IMaterial {
    public:
        ColorMat(const Color &color) : _color(color) {}
        bool scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override;

    private:
        Color _color;
};
