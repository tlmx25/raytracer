/*
** EPITECH PROJECT, 2024
** PRIVATE_RAYTRACER
** File description:
** main
*/

#include "Camera.hpp"
#include "PrimList.hpp"
// #include "material.hpp"
#include <memory>
#include "builder/builder.hpp"


int main() {

    PrimList world;

    Camera cam;

    Builder builder("config.cfg");
    auto materials = builder.getMaterials();

    auto primitives = builder.getPrimitives(materials);
    cam.render(primitives);
}
