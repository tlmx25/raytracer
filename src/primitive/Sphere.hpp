/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Sphere
*/

#pragma once

  #include "IPrimitive.hpp"
  #include "Utils.hpp"

class Sphere : public IPrimitive {
  public:
    Sphere(const Point3& center, double radius, shared_ptr<IMaterial> mat);
    ~Sphere();
  public:
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
  private:
    Point3 center;
    double radius;
    shared_ptr<IMaterial> mat;
};
