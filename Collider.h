#pragma once
#include <SFML\Graphics.hpp>
struct Collider
{
    Collider(sf::Vector2f p_closestPoint, bool p_isCollide);

    bool m_isCollide;
    sf::Vector2f m_closestPoint;
};

