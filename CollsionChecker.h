#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "Collider.h"

class CollsionChecker
{
public:

    static Collider checkIfBallAndRectangleCollide(const Rectangle& paddle, const Ball& ball);

    static sf::Vector2f closestPoint(const Rectangle & paddle, const Ball & ball);

    static sf::Vector2f fetchPointValue(double x0, double x1, double y0, double y1, const sf::Vector2f & p_ballPosition);

};

