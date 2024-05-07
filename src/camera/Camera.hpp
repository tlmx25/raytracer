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
        explicit Camera(const libconfig::Setting &settings);
        ~Camera();
    public:
        void render(const IPrimitive& world);
        void preview(const IPrimitive& world);
        void initialize();
        void init_preview();
        Ray get_ray(int i, int j) const;
        Vec3 sample_square() const;
        Color ray_color(const Ray& r, int depth, const IPrimitive& world) const;
        Point3 defocus_disk_sample() const;
    public:
        double aspect_ratio = 1.0;
        int image_width  = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;

        double vfov = 90;
        Point3 lookfrom = Point3(0,0,0);
        Point3 lookat = Point3(0,0,-1);
        Vec3 vup = Vec3(0,1,0);

        double defocus_angle = 0;
        double focus_dist = 10;
    private:
        int image_height;
        double pixel_samples_scale;
        Point3 center;
        Point3 pixel00_loc;
        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;
        Vec3 u, v, w;
        Vec3 defocus_disk_u;
        Vec3 defocus_disk_v;
        sf::RenderWindow window;
        sf::Image image;
        sf::Texture texture;
        sf::Event event;
        sf::Sprite sprite;
};
