/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include <chrono>
#include <sstream>
#include <fstream>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::render(const IPrimitive& world)
{
    initialize();
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    Color pixel_color(0,0,0);

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            pixel_color.reset();
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(std::cout, pixel_samples_scale * pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

void Camera::render_section(const IPrimitive& world, const Camera& cam, std::vector<std::string> &buffer, int startX, int endX, int startY, int endY, int id)
{
    Color pixel_color(0,0,0);
    Ray r;

    std::string tmp_filename = "tmp_" + std::to_string(id) + ".ray";
    std::ofstream out (tmp_filename, std::ios::out);

    for (int j = startY; j < endY; j++) {
        for (int i = startX; i < endX; i++) {
            pixel_color.reset();
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, max_depth, world);
            }
            write_color(out, pixel_samples_scale * pixel_color);
        }
    }
    out.close();
    std::cerr << "Thread " << id << " done" << std::endl;
}

void Camera::renderMultithread(const IPrimitive& world)
{
    std::vector<std::thread> threads;
    unsigned int num_threads = std::thread::hardware_concurrency();

    if (num_threads == 0)
        num_threads = 8;
    initialize();
    std::stringstream ss;
    std::vector<std::string> buffer(image_height);
    std::ofstream out ("Rendu.ppm", std::ios::out);
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    num_threads = 2;
    int sectionHeight = image_height / num_threads;

    std::cout << "height: " << image_height << " sectionHeight: " << sectionHeight << " num_threads: " << num_threads << "\n";
    for (unsigned int i = 0; i < num_threads; i++) {
        int startY = i * sectionHeight;
        int endY = (i + 1) * sectionHeight;
        if (i == num_threads - 1)
            endY = image_height;
        std::cout << "Thread " << i << " : " << startY << " -> " << endY << std::endl;
        threads.emplace_back(&Camera::render_section, this, std::ref(world), *this, std::ref(buffer), 0, image_width, startY, endY, i);
    }
    for (auto& thread : threads) {
        thread.join();
    }
    for (int i = 0; i < num_threads; i++) {
        std::ofstream in ("tmp_" + std::to_string(i) + ".ray", std::ios::in);
        out << in.rdbuf();
        in.close();
    }
    out.close();
    std::clog << "\rDone.                 \n";
    for (int i = 0; i < num_threads; i++) {
        std::string tmp_filename = "tmp_" + std::to_string(i) + ".ray";
        remove(tmp_filename.c_str());
    }
}

void Camera::initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = Point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    auto viewport_upper_left =
        center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray Camera::get_ray(int i, int j) const {

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                        + ((i + offset.x()) * pixel_delta_u)
                        + ((j + offset.y()) * pixel_delta_v);
    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return {ray_origin, ray_direction};
}

Vec3 Camera::sample_square() const
{
    return {Utils::random_double() - 0.5, Utils::random_double() - 0.5, 0};
}

Color Camera::ray_color(const Ray& r, int depth, const IPrimitive& world) const
{
    Ray scattered;
    HitRecord rec;
    static Color attenuation;
    static Vec3 unit_direction;

    if (depth <= 0)
        return {0,0,0};

    if (world.hit(r, Interval(0.001, infinity), rec)) {
        attenuation.reset();
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world);
        return {0,0,0};
    }

    unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}
