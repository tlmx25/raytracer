/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** camera
*/

#pragma once

    #include "IPrimitive.hpp"
    #include "Color.hpp"
    #include "Utils.hpp"
    #include "IMaterial.hpp"

class Camera {
    public:
        Camera();
        ~Camera();
    public:
        void render(const IPrimitive& world);
        void initialize();
        Ray get_ray(int i, int j) const;
        Vec3 sample_square() const;
        Color ray_color(const Ray& r, int depth, const IPrimitive& world) const;
    public:
        double aspect_ratio = 1.0;
        int image_width  = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;
    private:
        int image_height;
        double pixel_samples_scale;
        Point3 center;
        Point3 pixel00_loc;
        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;
};
