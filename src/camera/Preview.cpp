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

Preview::~Preview()
{
    this->window.close();
}

void Preview::init()
{
    window.create(sf::VideoMode(image_width, image_height), "Raytracer");
    image.create(image_width, image_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

void Preview::display()
{
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        texture.update(image);
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
