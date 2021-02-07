#pragma once
#include <SFML\Graphics.hpp>

struct Rectangle
{
    Rectangle(sf::Vector2f p_position, sf::Vector2f p_size, sf::Vector2f p_center, sf::Vector2f p_normal);
    bool shouldDraw;

    sf::Vector2f size;

    sf::Vector2f m_posiiton;

    sf::Vector2f m_center;

    sf::Vector2f m_normal;

    sf::RectangleShape m_shape;

};

