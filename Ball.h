#pragma once
#include <SFML\Graphics.hpp>

struct Ball
{
    void move(float p_speed, float p_deltaTime);
    Ball(sf::Vector2f p_position, sf::Vector2f p_direction, double p_radius);

    double m_radius;
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
};

