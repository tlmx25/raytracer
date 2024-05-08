/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera()
{
    aspect_ratio      = 16.0 / 9.0; // Obligatoire
    image_width       = 400; // obligatoire
    samples_per_pixel = 200;
    max_depth         = 50;

    vfov = 90; // Obligatoire
    lookfrom = Point3(-2,2,1); // obligatoire
    lookat = Point3(0,0,-1); // obligatoire
    vup = Vec3(0,1,0);

    defocus_angle = 0.0;
    focus_dist    = 1.0;
}

Camera::Camera(const libconfig::Setting &settings)
{
    aspect_ratio = Utils::settings_get_ratio(settings["aspect_ratio"]);
    settings.lookupValue("image_width", image_width);
    settings.lookupValue("vfov", vfov);
    lookfrom = Vec3::parseVec3(settings["lookfrom"]);
    lookat = Vec3::parseVec3(settings["lookat"]);

    if (settings.exists("vup"))
        vup = Vec3::parseVec3(settings["vup"]);
    if (settings.exists("defocus_angle"))
        defocus_angle = Utils::settings_get_double(settings, "defocus_angle");
    if (settings.exists("focus_dist"))
        focus_dist = Utils::settings_get_double(settings, "focus_dist");
    if (settings.exists("samples_per_pixel"))
        samples_per_pixel = Utils::settings_get_double(settings, "samples_per_pixel");
    if (settings.exists("max_depth"))
        max_depth= Utils::settings_get_int(settings, "max_depth");
    initialize();
}

Camera::~Camera()
{
}

void Camera::display_preview(Preview &preview, const IPrimitive& world)
{
    while (preview.window.isOpen()) {
        while (preview.window.pollEvent(preview.event)) {
            if (preview.event.type == sf::Event::Closed)
                preview.window.close();
        }

        for (int j = 0; j < preview.image_height; j++) {
            for (int i = 0; i < preview.image_width; i++) {
                Color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                pixel_color *= pixel_samples_scale;
                preview.image.setPixel(i, j, sf::Color(
                    static_cast<sf::Uint8>(255.999 * pixel_color.x()),
                    static_cast<sf::Uint8>(255.999 * pixel_color.y()),
                    static_cast<sf::Uint8>(255.999 * pixel_color.z())
                ));
            }
        }
        preview.texture.update(preview.image);
        preview.window.clear();
        preview.window.draw(preview.sprite);
        preview.window.display();
    }
}


void Camera::render(const IPrimitive& world)
{    
    initialize();
    Preview preview(image_width, image_height);
    display_preview(preview, world);
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            Color pixel_color(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(std::cout, pixel_samples_scale * pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

void Camera::initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    auto theta = Utils::degrees_to_radians(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2 * h * focus_dist;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = viewport_height * -v;
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = focus_dist * tan(Utils::degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

Ray Camera::get_ray(int i, int j) const {

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                        + ((i + offset.x()) * pixel_delta_u)
                        + ((j + offset.y()) * pixel_delta_v);
    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
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

Point3 Camera::defocus_disk_sample() const
{
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}
