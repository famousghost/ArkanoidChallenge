#include "Input.h"
#include "Transformations.h"

bool Input::s_moveUp = false;
bool Input::s_moveDown = false;
bool Input::s_increaseLen = false;
bool Input::s_decreaseLen = false;
bool Input::s_rotateRight = false;
bool Input::s_rotateLeft = false;
float Input::s_speed = 500.0f;
float Input::s_sensitivity = 100.0f;

void Input::buttonsClick(sf::RenderWindow& p_window)
{
    sf::Event event;
    while (p_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            p_window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            p_window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                s_moveUp = true;
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                s_moveDown = true;
            }
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                s_increaseLen = true;
            }
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                s_decreaseLen = true;
            }
            if (event.key.code == sf::Keyboard::Q)
            {
                s_rotateLeft = true;
            }
            if (event.key.code == sf::Keyboard::E)
            {
                s_rotateRight = true;
            }
        }
        else if(event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                s_moveUp = false;
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                s_moveDown = false;
            }
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                s_increaseLen = false;
            }
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                s_decreaseLen = false;
            }
            if (event.key.code == sf::Keyboard::Q)
            {
                s_rotateLeft = false;
            }
            if (event.key.code == sf::Keyboard::E)
            {
                s_rotateRight = false;
            }
        }
    }
}

void Input::movePaddle(sf::Vector2f& p_point, const sf::Vector2f& p_direction, float p_deltaTime)
{
    if (Input::s_increaseLen)
    {
        p_point += p_direction * s_speed * p_deltaTime;
    }
    if (Input::s_decreaseLen)
    {
        p_point -= p_direction * s_speed * p_deltaTime;
    }
}

void Input::rotate(sf::Vector2f& p_point, float p_deltaTime)
{
    if (s_rotateLeft)
    {
        p_point = Transformations::rotate(p_point, s_sensitivity * p_deltaTime * -1.0);
    }
    if (s_rotateRight)
    {
        p_point = Transformations::rotate(p_point, s_sensitivity * p_deltaTime);
    }
}
