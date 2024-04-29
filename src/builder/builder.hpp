/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** builder
*/

#pragma once
#include <iostream>
#include <libconfig.h++>

class Builder {
    public:
        Builder(std::string path);
        Builder(const char *path);
        ~Builder() {};
    private:
        libconfig::Config _cfg;
};
