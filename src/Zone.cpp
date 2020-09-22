#include "C:\OS\MapConstructor\include\Zone.h"
#include <iostream>
Zone ::Zone()
{
}

void Zone::PointOut(TwoDPoint t)
{
    std::cout<<t.x<<", "<<t.y<<"\n";
}

Zone::Zone (TwoDPoint LeftDownVertex, TwoDPoint RightUpVertex, bool IsWalked, TwoDPoint Translation)
{
    if(LeftDownVertex.x>RightUpVertex.x)
    {
        unsigned int t = LeftDownVertex.x;
        LeftDownVertex.x = RightUpVertex.x;
        RightUpVertex.x = t;
    }
    if(LeftDownVertex.y>RightUpVertex.y)
    {
        unsigned int t = LeftDownVertex.y;
        LeftDownVertex.y = RightUpVertex.y;
        RightUpVertex.y = t;
    }
    this->LeftDownVertex = LeftDownVertex;
    this->RightUpVertex = RightUpVertex;
    this->Translation = Translation;
    LeftUpVertex = {LeftDownVertex.x, RightUpVertex.y};
    RightDownVertex = {RightUpVertex.x, LeftDownVertex.y};

    if(IsWalked)
    {
        ZoneType='C';
        ZoneColor=sf::Color(230, 230, 255, 255);
    }
    else
    {
        ZoneType='W';
        ZoneColor=sf::Color(69, 228, 255, 255);
    }

    sf::CircleShape p1 (3.f);
    p1.setFillColor(ZoneColor);
    p1.setOutlineColor(sf::Color::Black);
    p1.setOutlineThickness(1.5f);

    p1.setPosition(LeftDownVertex.x, LeftDownVertex.y);
    VERTICES.push_back(p1);

    sf::CircleShape p2 (3.f);
    p2.setFillColor(ZoneColor);
    p2.setOutlineColor(sf::Color::Black);
    p2.setOutlineThickness(1.5f);

    p2.setPosition(LeftUpVertex.x, LeftUpVertex.y);
    VERTICES.push_back(p2);

    sf::CircleShape p3 (3.f);
    p3.setFillColor(ZoneColor);
    p3.setOutlineColor(sf::Color::Black);
    p3.setOutlineThickness(1.5f);

    p3.setPosition(RightUpVertex.x, RightUpVertex.y);
    VERTICES.push_back(p3);

    sf::CircleShape p4 (3.f);
    p4.setFillColor(ZoneColor);
    p4.setOutlineColor(sf::Color::Black);
    p4.setOutlineThickness(1.5f);

    p4.setPosition(RightDownVertex.x, RightDownVertex.y);
    VERTICES.push_back(p4);

    sf::RectangleShape rectangle;
    rectangle.setOutlineColor(sf::Color::Black); //ZoneColor
    rectangle.setFillColor(ZoneColor);
    rectangle.setOutlineThickness(2);
    rectangle.setSize(sf::Vector2f(RightUpVertex.x-LeftDownVertex.x,
                                   RightUpVertex.y-LeftDownVertex.y)); //Left-Right, Up-Down
    rectangle.setPosition(LeftDownVertex.x, LeftDownVertex.y); //LeftUp

    RECTANGLES.push_back(rectangle);
}

std::vector <sf::RectangleShape> Zone::getRectanglesToDraw()
{
    return RECTANGLES;
}

std::vector <sf::CircleShape> Zone::getPointsToDraw()
{
    return VERTICES;
}

TwoDPoint Zone::getLeftDownVertex()
{
    return {LeftUpVertex.x-Translation.x, Translation.y-LeftUpVertex.y};
}

TwoDPoint Zone::getRightUpVertex()
{
    return {RightDownVertex.x-Translation.x, Translation.y-RightDownVertex.y};
}
char Zone::getZoneType()
{
    return ZoneType;
}
Zone::~Zone()
{
}
