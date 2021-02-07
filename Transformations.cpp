#include "Transformations.h"
#include <math.h>

# define M_PI 3.14159265358979323846  

sf::Vector2f Transformations::rotate(sf::Vector2f p_vec, double p_angle)
{
    double l_angle = toRadinas(p_angle);
    return sf::Vector2f(std::cos(l_angle) * p_vec.x - std::sin(l_angle) * p_vec.y, 
                        std::sin(l_angle) * p_vec.x + std::cos(l_angle) * p_vec.y);
}

sf::Vector2f Transformations::move(sf::Vector2f p_vec, float x, float y)
{
    return p_vec + sf::Vector2f(x, y);
}

double Transformations::toRadinas(double p_angle)
{
    return (p_angle * M_PI) / 180.0f;
}

double Transformations::toAngle(double p_radians)
{
    return (p_radians * 180.0f) / M_PI;
}

float Transformations::dotProduct(const sf::Vector2f& p_vec1, const sf::Vector2f& p_vec2)
{
    return p_vec1.x * p_vec2.x + p_vec1.y * p_vec2.y;
}

float Transformations::getAngleFromCos(double dotProductValue)
{
    return toAngle(acos(dotProductValue));
}

float Transformations::length(sf::Vector2f p_vec)
{
    return std::sqrt((p_vec.x) * (p_vec.x) + (p_vec.y) * (p_vec.y));
}

sf::Vector2f Transformations::normalize(sf::Vector2f p_vec)
{
    auto ln = length(p_vec);
    return sf::Vector2f(p_vec.x / ln, p_vec.y / ln);
}

sf::Vector2f Transformations::reflect(sf::Vector2f p_vec, sf::Vector2f p_normal)
{
    return p_vec - 2.0f * dotProduct(p_vec, p_normal) * p_normal;
}

double Transformations::distance(sf::Vector2f p_vec1, sf::Vector2f p_vec2)
{
    return std::sqrt((p_vec2.x - p_vec1.x) * (p_vec2.x - p_vec1.x) 
           + (p_vec2.y - p_vec1.y) * (p_vec2.y - p_vec1.y));
}
