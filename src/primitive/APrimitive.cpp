/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"

APrimitive::APrimitive(shared_ptr<IMaterial> _mat) : mat(_mat)
{
    if (_mat == nullptr)
        throw PrimError("APrimitive : Material can't be null");
}

APrimitive::APrimitive(const APrimitive &obj)
{
    this->mat = obj.mat;
}

APrimitive::~APrimitive()
{
}

shared_ptr<IMaterial> APrimitive::getMat() const
{
    return this->mat;
};

void APrimitive::setMat(shared_ptr<IMaterial> _mat)
{
    this->mat = mat;
}

APrimitive &APrimitive::operator=(const APrimitive &obj)
{
    if (this == &obj)
        return *this;
    
    this->mat = obj.mat;
    return *this;
}
