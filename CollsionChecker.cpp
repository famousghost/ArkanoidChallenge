#include "CollsionChecker.h"
#include "Transformations.h"

Collider CollsionChecker::checkIfBallAndRectangleCollide(const Rectangle & rect, const Ball & ball)
{
    sf::Vector2f l_closestPoint = closestPoint(rect, ball);

    if (Transformations::distance(ball.m_position, l_closestPoint) <= ball.m_radius)
    {
        return Collider(l_closestPoint, true);
    }
    return Collider(l_closestPoint, false);
}

sf::Vector2f CollsionChecker::closestPoint(const Rectangle & rect, const Ball & ball)
{
    auto x0 = rect.m_posiiton.x;
    auto x1 = rect.m_posiiton.x + rect.size.x;

    auto y0 = rect.m_posiiton.y;
    auto y1 = rect.m_posiiton.y + rect.size.y;

    sf::Vector2f l_closestPoint;

    l_closestPoint = fetchPointValue(x0, x1, y0, y1, ball.m_position);

    return l_closestPoint;
}

sf::Vector2f CollsionChecker::fetchPointValue(double x0, double x1, double y0, double y1, const sf::Vector2f & p_ballPosition)
{
    sf::Vector2f l_result;
    if (p_ballPosition.x > x0 && p_ballPosition.x < x1)
    {
        l_result.x = p_ballPosition.x;
    }
    else if (p_ballPosition.x <= x0)
    {
        l_result.x = x0;
    }
    else if (p_ballPosition.x >= x1)
    {
        l_result.x = x1;
    }

    if (p_ballPosition.y > y0 && p_ballPosition.y < y1)
    {
        l_result.y = p_ballPosition.y;
    }
    else if (p_ballPosition.y <= y0)
    {
        l_result.y = y0;
    }
    else if (p_ballPosition.y >= y1)
    {
        l_result.y = y1;
    }
    return l_result;
}
