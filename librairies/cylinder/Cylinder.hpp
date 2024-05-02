/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#pragma once

    #include "APrimitive.hpp"

class Cylinder : public APrimitive {
    public:
        Cylinder();
        ~Cylinder();
    private:
};

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings);
