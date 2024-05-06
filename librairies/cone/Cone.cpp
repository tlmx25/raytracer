/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#include "Cone.hpp"

Cone::Cone(const double radius, const Point3& center, shared_ptr<IMaterial> mat) :  APrimitive(mat), _center(center),
_radius(fmax(0,radius))
{
}

Cone::Cone(const Cone &obj) : APrimitive(obj.getMaterial()), _center(obj._center), _radius(obj._radius)
{
}

Cone::Cone(const libconfig::Setting &settings) : APrimitive()
{
    try {
        float radius_str = 84;
        settings["center"].lookupValue("x", _center[0]);
        settings["center"].lookupValue("y", _center[1]);
        settings["center"].lookupValue("z", _center[2]);
        if (!settings.lookupValue("radius", radius_str)) {
            std::cerr << "Cone: error on reading radius." << std::endl;
            throw std::runtime_error("Cone: error on reading radius.");
        }
        _radius = radius_str;
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Cone: error on reading sphere." << std::endl;
        std::cerr << "example : Cone = { center = { x = 0; y = 0; Z = 0 }; radius = 1;  material = \"metal\"}" << std::endl;
        throw std::runtime_error("Cone: error on reading sphere.");
    }
}

Cone::~Cone()
{
}

bool Cone::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    (void)r;
    (void)ray_t;
    (void)rec;
}

Cone &Cone::operator=(const Cone &obj)
{
    if (this == &obj)
        return *this;
    this->_center = obj._center;
    this->_radius = obj._radius;
    this->setMaterial(obj.getMaterial());
    return *this;
}

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings)
{
    return (new Cone(settings));
}
