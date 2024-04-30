/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** hittable
*/

#pragma once

#include "Imaterial.hpp"
#include "ray.hpp"
#include "interval.hpp"

class hit_record {
  public:
    point3 p;
    vec3 normal;
    shared_ptr<IMaterial> mat;
    double t;

    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
