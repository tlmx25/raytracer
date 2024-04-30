/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** builder
*/

#pragma once

    #include <iostream>
    #include <libconfig.h++>
    #include <map>
    #include "IMaterial.hpp"

class Builder {
    public:
        Builder(std::string path);
        Builder(const char *path);
        ~Builder() {};
        std::map<std::string, shared_ptr<IMaterial>> getMaterials();
    private:
        libconfig::Config _cfg;
};
