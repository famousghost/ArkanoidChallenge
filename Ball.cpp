#include "Ball.h"

void Ball::move(float p_speed, float p_deltaTime)
{
    m_position += (m_direction * p_speed * p_deltaTime);
}

Ball::Ball(sf::Vector2f p_position, sf::Vector2f p_direction, double p_radius)
    :m_position(p_position), m_direction(p_direction), m_radius(p_radius)
{
}
