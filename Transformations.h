#pragma once
#include <SFML\Graphics.hpp>

class Transformations
{
public:
    static sf::Vector2f rotate(sf::Vector2f p_vec, double p_angle);

    static sf::Vector2f move(sf::Vector2f p_vec, float x, float y);

    static double toRadinas(double p_angle);

    static double toAngle(double p_radians);

    static float dotProduct(const sf::Vector2f & p_vec1, const sf::Vector2f & p_vec2);

    static float getAngleFromCos(double dotProductValue);

    static float length(sf::Vector2f p_vec);

    static sf::Vector2f normalize(sf::Vector2f p_vec);

    static sf::Vector2f reflect(sf::Vector2f p_vec, sf::Vector2f p_normal);

    static double distance(sf::Vector2f p_vec1, sf::Vector2f p_vec2);

};

