/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
}

// void Camera::render(const IPrimitive& world)
// {    
//     initialize();
//     std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
//     for (int j = 0; j < image_height; j++) {
//         std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
//         for (int i = 0; i < image_width; i++) {
//             Color pixel_color(0,0,0);
//             for (int sample = 0; sample < samples_per_pixel; sample++) {
//                 Ray r = get_ray(i, j);
//                 pixel_color += ray_color(r, max_depth, world);
//             }
//             write_color(std::cout, pixel_samples_scale * pixel_color);
//         }
//     }
//     std::clog << "\rDone.                 \n";
// }

void Camera::render_section(const IPrimitive& world, const Camera& cam, int startX, int endX, int startY, int endY)
{
    for (int j = startY; j < endY; j++) {
        std::clog << "\rScanlines remaining: " << (endY - j) << ' ' << std::flush;
        for (int i = startX; i < endX; i++) {
            Color pixel_color(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, max_depth, world);
            }
            write_color(std::cout, pixel_samples_scale * pixel_color);
        }
    }
}


void Camera::render(const IPrimitive& world)
{
    std::vector<std::thread> threads;
    unsigned int num_threads = std::thread::hardware_concurrency();

    if (num_threads == 0)
        num_threads = 8;
    initialize();
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    int sectionHeight = image_height / (2 * num_threads);
    for (unsigned int i = 0; i < num_threads; ++i) {
        int startY = i * sectionHeight * 2;
        int endY = (i + 1) * sectionHeight * 2;
        threads.emplace_back(&Camera::render_section, this, std::cref(world), std::cref(*this), 0, image_width, startY, endY);
    }
    for (auto& thread : threads)
        thread.join();
    std::clog << "\rDone.                 \n";
    // std::cout << num_threads << std::endl;
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

    return Ray(ray_origin, ray_direction);
}

Vec3 Camera::sample_square() const
{
    return Vec3(Utils::random_double() - 0.5, Utils::random_double() - 0.5, 0);
}

Color Camera::ray_color(const Ray& r, int depth, const IPrimitive& world) const
{
    if (depth <= 0)
        return Color(0,0,0);
    HitRecord rec;

    if (world.hit(r, Interval(0.001, infinity), rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world);
        return Color(0,0,0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}
