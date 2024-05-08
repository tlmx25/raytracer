/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** preview
*/

#include "Preview.hpp"

Preview::Preview(int image_width, int image_height)
{
    this->image_width = image_width;
    this->image_height = image_height;
    init();
}

void Preview::init()
{
    window.create(sf::VideoMode(image_width, image_height), "Raytracer");
    image.create(image_width, image_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}
