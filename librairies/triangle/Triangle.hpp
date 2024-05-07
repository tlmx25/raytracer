/*
** EPITECH PROJECT, 2023
** raytracer [WSL: Ubuntu-22.04]
** File description:
** Triangle.hpp
*/

#pragma once

    #include "APrimitive.hpp"

class Triangle : public APrimitive {
    public:
        Triangle(Point3 a, Point3 b, Point3 c, shared_ptr<IMaterial> mat);
        Triangle(const libconfig::Setting &settings);
        Triangle(const Triangle &obj);
        ~Triangle();
    public:
        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
    public:
        Triangle &operator=(const Triangle &obj);
    private:
        Point3 _a;
        Point3 _b;
        Point3 _c;
};

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings);