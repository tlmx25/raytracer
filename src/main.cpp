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

    // auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    // auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    // auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
    // auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

    // world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 1200;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;

//    cam.render(world);
    Builder builder("/home/justine/Documents/tek2/raytracer/raytracer/config.cfg");
    auto materials = builder.getMaterials();

//    for (auto const& [key, val] : materials) {
//        std::cout << key << " => " << val << std::endl;
//    }

    auto primitives = builder.getPrimitives(materials);
//    std::cout << primitives.size() << std::endl;
    cam.renderMultithread(primitives);

    // real    0m1,347s
    // user    0m1,258s
    // sys     0m0,089s

    // real    0m5,806s
    // user    0m8,856s
    // sys     1m15,775s
}
