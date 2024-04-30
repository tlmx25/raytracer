/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PrimList
*/

#pragma once

    #include <vector>
    #include <memory.h>
    #include "IPrimitive.hpp"

class PrimList : public IPrimitive {
    public:
        PrimList();
        PrimList(shared_ptr<IPrimitive> object);
        ~PrimList();
    public:
        void clear();
        void add(shared_ptr<IPrimitive> object);
        bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const override;
    public:
        std::vector<shared_ptr<IPrimitive>> objects;
};
