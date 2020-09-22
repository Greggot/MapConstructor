#ifndef ZONE_H
#define ZONE_H

#include <SFML/Graphics/VertexArray.hpp>

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

struct TwoDPoint
{
    unsigned int x, y;
};

struct RectangleData
{
    TwoDPoint leftdown, rightup;
};

class Zone
{
    public:
        Zone();
        Zone(TwoDPoint  LeftDownVertex, TwoDPoint  RightUpVertex, bool IsWalked, TwoDPoint Translation);
        std::vector <sf::CircleShape> getPointsToDraw();
        std::vector <sf::RectangleShape> getRectanglesToDraw();
        TwoDPoint getLeftDownVertex();
        TwoDPoint getRightUpVertex();
        char getZoneType();
        virtual ~Zone();
    private:
        sf::Color ZoneColor;
        TwoDPoint  LeftDownVertex, RightUpVertex, LeftUpVertex, RightDownVertex;
        TwoDPoint Translation;
        std::vector <sf::CircleShape> VERTICES;
        std::vector <sf::RectangleShape> RECTANGLES;
        char ZoneType;

        void PointOut(TwoDPoint t);
};

#endif // ZONE_H
