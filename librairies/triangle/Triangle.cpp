/*
** EPITECH PROJECT, 2023
** raytracer [WSL: Ubuntu-22.04]
** File description:
** Triangle.cpp
*/

#include "Triangle.hpp"
#include <iostream>

Triangle::Triangle(Point3 a, Point3 b, Point3 c, shared_ptr<IMaterial> mat) : APrimitive(mat), _a(a), _b(b), _c(c)
{
}

Triangle::Triangle(const libconfig::Setting &settings) : APrimitive()
{
    try {
        settings["a"].lookupValue("x", _a[0]);
        settings["a"].lookupValue("y", _a[1]);
        settings["a"].lookupValue("z", _a[2]);
        settings["b"].lookupValue("x", _b[0]);
        settings["b"].lookupValue("y", _b[1]);
        settings["b"].lookupValue("z", _b[2]);
        settings["c"].lookupValue("x", _c[0]);
        settings["c"].lookupValue("y", _c[1]);
        settings["c"].lookupValue("z", _c[2]);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Triangle: error on reading triangle." << std::endl;
        std::cerr << "example : Triangle = { a = { x = 0; y = 0; Z = 0 }; b = { x = 0; y = 0; Z = 0 };\
        c = { x = 0; y = 0; Z = 0 };  material = \"metal\"}" << std::endl;
        throw std::runtime_error("Triangle: error on reading triangle.");
    }
}

Triangle::Triangle(const Triangle &obj) : APrimitive(obj.getMaterial()), _a(obj._a), _b(obj._b), _c(obj._c)
{
}

Triangle::~Triangle()
{
}

bool Triangle::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    Vec3 norme = (this->_b - this->_a) * (this->_c - this->_a);
    Vec3 n = norme / norme.length();

    auto dotedND = dot(n, r.direction());
    if (dotedND == 0)
        return false;
    auto t = dot((this->_a - r.origin()), n) / dot(r.direction(), n);
    if (t < ray_t.min || t > ray_t.max)
        return false;
    Vec3 T = r.origin() + t * r.direction();
    if (dot((this->_b - this->_a) * (T - this->_a), n) < 0 ||
        dot((this->_b - this->_a) * (T - this->_a), n) < 0 ||
        dot((this->_b - this->_a) * (T - this->_a), n) < 0)
            return false;
    rec.t = t;
    rec.p = r.at(rec.t);
    rec.mat = this->getMaterial();
    return true;
}

Triangle &Triangle::operator=(const Triangle &obj)
{
    if (this == &obj)
        return *this;
    this->setMaterial(obj.getMaterial());
    this->_a = obj._a;
    this->_b = obj._b;
    this->_c = obj._c;
    return *this;
}

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings)
{
    return (new Triangle(settings));
}
