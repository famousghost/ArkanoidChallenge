#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <math.h>
#include "GameWindow.h"
#include "Input.h"
#include "Paddle.h"
#include "Ball.h"
#include "CollsionChecker.h"
#include "Transformations.h"

namespace
{
    constexpr float BALL_SPEED = 500.0f;
    constexpr int BLOCK_LINES = 9;
}

Rectangle resetPaddle(double p_windowWidth,
                      double p_windowHeight,
                      double p_paddleHeight,
                      double p_paddleWidth)
{
    return  Rectangle(sf::Vector2f(p_windowWidth / 2.0f - p_paddleWidth / 2.0f,
                                   p_windowHeight - 100.0f),
                      sf::Vector2f(p_paddleWidth, p_paddleHeight),
                      sf::Vector2f(0.0f, 0.0f),
                      sf::Vector2f(0.0f, 1.0f));
}

Ball resetBall(double p_windowWidth,
                    double p_windowHeight,
                    double p_radius)
{
    return Ball(sf::Vector2f(p_windowWidth / 2.0f,
                              p_windowHeight / 2.0f),
                 sf::Vector2f(0.0f, -1.0f),
                 p_radius);
}

std::vector<Rectangle> resetBlocks(int& currentAmount, int amount, double p_windowWidth, double p_wallSize)
{
    currentAmount = 0;
    float l_blockSize = 40.0f;
    float l_padding = 45.0f;
    float l_wallPaddig = 5.0f;
    sf::Vector2f l_blockStartingPoint = sf::Vector2f(p_windowWidth / 2.0f, p_wallSize + l_wallPaddig);
    sf::Vector2f l_blockPaddingX = sf::Vector2f(l_padding, 0.0f);
    sf::Vector2f l_blockPaddingY = sf::Vector2f(0.0f, l_padding);

    std::vector<Rectangle> l_blocks;
    int l_lineSize = amount;
    l_blockStartingPoint -= l_lineSize /2.0f * l_blockPaddingX;
    for (int i = 0; i < amount; ++i)
    {
        for(int j = 0; j < l_lineSize; ++j)
        {
            l_blocks.emplace_back(l_blockStartingPoint, 
                                  sf::Vector2f(l_blockSize, l_blockSize), 
                                  sf::Vector2f(0.0f, 0.0f), 
                                  sf::Vector2f(0.0f, 0.0f));
            l_blocks.back().m_shape.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 255.0f));
            l_blockStartingPoint += l_blockPaddingX;
            currentAmount++;
        }
        l_lineSize -= 2;
        l_blockStartingPoint = sf::Vector2f(p_windowWidth / 2.0f, l_blockStartingPoint.y);
        l_blockStartingPoint -= l_lineSize / 2.0f * l_blockPaddingX;
        l_blockStartingPoint += l_blockPaddingY;
    }
    return l_blocks;
}

int main()
{
    int points = 0;
    int currentAmount = 0;

    const unsigned int l_windowWidth = 800;
    const unsigned int l_windowHeight = 600;
    std::string l_title = "Arkanoid";
    sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
    float l_prevTime = 0.0f;
    float l_currentTime = 0.0f;
    sf::Clock clock;

    double l_wallSize = 20.0;

    Ball ball = resetBall(l_windowWidth, l_windowHeight, 8.0f);
    Rectangle paddle = resetPaddle(l_windowWidth, l_windowHeight, 15.0f, 100.0f);
    std::vector<Rectangle> l_blocks = resetBlocks(currentAmount, BLOCK_LINES, l_windowWidth, l_wallSize);

    std::array<Rectangle, 3> l_walls = { Rectangle{ sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(l_wallSize,
                     static_cast<double>(l_windowHeight)),
        sf::Vector2f(20.0f, l_windowHeight / 2.0f),
        sf::Vector2f(1.0f, 0.0f) },
        Rectangle{ sf::Vector2f(l_windowWidth - 20.0f, 0.0f),
        sf::Vector2f(l_wallSize,
                     static_cast<double>(l_windowHeight)),
        sf::Vector2f(l_windowWidth - 20.0f, l_windowHeight / 2.0f),
        sf::Vector2f(-1.0f, 0.0f) },
        Rectangle{ sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(static_cast<double>(l_windowWidth),
                     l_wallSize),
        sf::Vector2f(l_windowWidth / 2.0f, 20.0f),
        sf::Vector2f(0.0f, 1.0f) }
    };

    for (auto& wall : l_walls)
    {
        wall.m_shape.setFillColor(sf::Color(255, 255, 0, 255));
    }

    for (auto& wall : l_walls)
    {
        wall.m_shape.setFillColor(sf::Color(255, 255, 0, 255));
    }

    sf::CircleShape ballShape(ball.m_radius);
    ballShape.setPosition(ball.m_position);

    sf::Text l_text;
    sf::Font l_font;

    if (!l_font.loadFromFile("arial.ttf"))
    {
        std::cout << "cannot load arail.ttf";
        return -1;
    }


    l_text.setFont(l_font);

    l_text.setCharacterSize(32);

    l_text.setPosition(l_windowWidth - 4.0f * l_wallSize, l_wallSize);

    l_text.setFillColor(sf::Color::White);

    l_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    while (m_window.isOpen())
    {
        Input::buttonsClick(m_window);
        sf::Time l_elapsed = clock.getElapsedTime();
        l_prevTime = l_currentTime;
        l_currentTime = l_elapsed.asSeconds();
        float l_deltaTime = l_currentTime - l_prevTime;
        m_window.clear();
        Input::movePaddle(paddle.m_posiiton, sf::Vector2f(1.0f, 0.0f), l_deltaTime);
        if (paddle.m_posiiton.x >= l_windowWidth - (l_wallSize + paddle.size.x))
        {
            paddle.m_posiiton.x = l_windowWidth - (l_wallSize + paddle.size.x);
        }
        if (paddle.m_posiiton.x <= l_wallSize)
        {
            paddle.m_posiiton.x = l_wallSize;
        }
        paddle.m_shape.setPosition(paddle.m_posiiton);
        ball.move(BALL_SPEED, l_deltaTime);
        ballShape.setPosition(ball.m_position);
        if (ball.m_position.y >= l_windowHeight)
        {
            ball = resetBall(l_windowWidth, l_windowHeight, 8.0f);
            paddle = resetPaddle(l_windowWidth, l_windowHeight, 15.0f, 100.0f);
            l_blocks = resetBlocks(currentAmount, BLOCK_LINES, l_windowWidth, l_wallSize);
            points = 0;
        }
        auto l_collider = CollsionChecker::checkIfBallAndRectangleCollide(paddle, ball);
        if (l_collider.m_isCollide)
        {
            sf::Vector2f l_paddleCenter = paddle.m_posiiton + sf::Vector2f(paddle.size.x / 2.0f, paddle.size.y);
            sf::Vector2f l_fromCenterToBall = sf::Vector2f(ball.m_position.x - l_paddleCenter.x, ball.m_position.y - l_paddleCenter.y);
            ball.m_direction = Transformations::normalize(sf::Vector2f(-ball.m_direction.x + l_fromCenterToBall.x, -ball.m_direction.y + l_fromCenterToBall.y));
        }

        for (const auto& wall : l_walls)
        {
            auto l_collider = CollsionChecker::checkIfBallAndRectangleCollide(wall, ball);
            if (l_collider.m_isCollide)
            {
                ball.m_direction += 2.0f * wall.m_normal;
                ball.m_direction = Transformations::normalize(ball.m_direction);
            }
            m_window.draw(wall.m_shape);
        }

        for (auto& block : l_blocks)
        {
            if (block.shouldDraw)
            {
                auto l_collider = CollsionChecker::checkIfBallAndRectangleCollide(block, ball);
                if (l_collider.m_isCollide)
                {
                    points++;
                    block.shouldDraw = false;
                    sf::Vector2f l_blockCenter = block.m_posiiton + sf::Vector2f(block.size.x / 2.0f, block.size.y / 2.0f);
                    sf::Vector2f l_fromCenterToBall = sf::Vector2f(ball.m_position.x - l_blockCenter.x, ball.m_position.y - l_blockCenter.y);
                    ball.m_direction = Transformations::normalize(sf::Vector2f(-ball.m_direction.x + l_fromCenterToBall.x, -ball.m_direction.y + l_fromCenterToBall.y));
                }
                m_window.draw(block.m_shape);
            }
        }

        if (points == currentAmount)
        {
            ball = resetBall(l_windowWidth, l_windowHeight, 8.0f);
            paddle = resetPaddle(l_windowWidth, l_windowHeight, 15.0f, 100.0f);
            l_blocks = resetBlocks(currentAmount, BLOCK_LINES, l_windowWidth, l_wallSize);
            points = 0;
        }

        std::stringstream ss;
        ss << points;

        l_text.setString(ss.str());

        m_window.draw(l_text);
        m_window.draw(paddle.m_shape);
        m_window.draw(ballShape);
        m_window.display();
    }

    return 0;
}