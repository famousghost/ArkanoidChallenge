#include "Paddle.h"

Rectangle::Rectangle(sf::Vector2f p_position, sf::Vector2f p_size, sf::Vector2f p_center, sf::Vector2f p_normal)
{
    m_posiiton = p_position;
    size = p_size;
    m_center = p_center;
    m_normal = p_normal;
    shouldDraw = true;
    m_shape = sf::RectangleShape(size);
    m_shape.setPosition(m_posiiton);
}
