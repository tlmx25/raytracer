/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

Sphere::Sphere(const Point3& center, double radius, shared_ptr<IMaterial> mat) : center(center),
radius(fmax(0,radius)), APrimitive(mat)
{
}

Sphere::Sphere(const Sphere &obj) : center(obj.center), radius(obj.radius), APrimitive(obj.getMat())
{
}

Sphere::~Sphere()
{
}

bool Sphere::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    Vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = this->getMat();
    return true;
}

Sphere &Sphere::operator=(const Sphere &obj)
{
    if (this == &obj)
        return *this;
    this->center = obj.center;
    this->radius = obj.radius;
    this->setMat(obj.getMat());
    return *this;
}