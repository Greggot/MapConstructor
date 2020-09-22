#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <C:\OS\MapConstructor\include\RedactorManager.h>

#include <iostream>
#include <string>
#include <vector>

std::vector<Zone> ZONES;

const unsigned int width = 1600;
const unsigned int height = 900;

int main()
{
    bool FirstVerticeHasBeenCreated = false;
    bool IsWalked = false;

    bool IsConnectionActivated = true;
    unsigned int ConnectionRadius = 10;

    RectangleData DATA;

    std::vector <TwoDPoint> ConnectionPoints;
    sf::Vector2f Translation(100.f, height-100);

    ConnectionPoints.push_back({Translation.x, Translation.y});

    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    ///---------------AXYS----------------------------
    sf::VertexArray Ox(sf::PrimitiveType::Lines, 2);
    Ox[0].position = sf::Vector2f(Translation.x, Translation.y);
    Ox[1].position = sf::Vector2f(Translation.x+40.f, Translation.y);
    Ox[0].color = sf::Color::Red;
    Ox[1].color = sf::Color::Red;
    sf::VertexArray Oy(sf::PrimitiveType::Lines, 2);
    Oy[0].position = sf::Vector2f(Translation.x, Translation.y);
    Oy[1].position = sf::Vector2f(Translation.x, Translation.y-40.f);
    Oy[0].color = sf::Color::Blue;
    Oy[1].color = sf::Color::Blue;
    ///-----------------------------------------------

    sf::RenderWindow Redactor(sf::VideoMode(1600, 900), "MAP CREATOR v 0.1");
    sf::Event event;
    sf::Vector2i MousePosition;

    while (Redactor.isOpen())
    {
        while (Redactor.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    Redactor.close();
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Q:
                        {
                            IsConnectionActivated ? IsConnectionActivated=false : IsConnectionActivated=true;
                            break;
                        }
                        case sf::Keyboard::E:
                        {
                            IsWalked ? IsWalked = false : IsWalked = true;
                            break;
                        }
                        case sf::Keyboard::R:
                            {
                                if(ZONES.size()>0)
                                    ZONES.pop_back();
                                break;
                            }
                        case sf::Keyboard::S:
                            {
                                FileTranslator T (ZONES);
                                T.MapIntoFile("Map1.txt");
                                break;
                            }
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        MousePosition = sf::Mouse::getPosition(Redactor);
                        if(MousePosition.x>Translation.x && MousePosition.y<Translation.y)
                        {
                            TwoDPoint ScreenCoordinates {MousePosition.x, MousePosition.y};
                            if(IsConnectionActivated)
                            {
                                for(unsigned int i = 0; i<ConnectionPoints.size(); i++)
                                {
                                    if(ScreenCoordinates.x-ConnectionPoints[i].x<ConnectionRadius ||
                                       ConnectionPoints[i].x-ScreenCoordinates.x<ConnectionRadius)
                                        ScreenCoordinates.x = ConnectionPoints[i].x;
                                    if(ScreenCoordinates.y-ConnectionPoints[i].y<ConnectionRadius ||
                                       ConnectionPoints[i].y-ScreenCoordinates.y<ConnectionRadius)
                                        ScreenCoordinates.y = ConnectionPoints[i].y;
                                }
                            }
                            TwoDPoint AbstractMapCoordinates   {ScreenCoordinates.x - Translation.x,
                                                                Translation.y - ScreenCoordinates.y};
                            ConnectionPoints.push_back(ScreenCoordinates);
                            if(FirstVerticeHasBeenCreated)
                            {
                                DATA.rightup = ScreenCoordinates;
                                ZONES.push_back(Zone(DATA.leftdown, DATA.rightup, IsWalked,
                                                     {Translation.x, Translation.y}));
                                FirstVerticeHasBeenCreated = false;
                            }
                            else
                            {
                                FirstVerticeHasBeenCreated = true;
                                DATA.leftdown = ScreenCoordinates;
                            }
                        }
                    }
                }
            }
        }
        Redactor.clear(sf::Color::White);

        std::string ZoneTypeDescr;
        IsWalked ? ZoneTypeDescr = "walked" : ZoneTypeDescr = "closed" ;

        std::string OutputText = "Q - Deactivate connection to the already existing points\nE - Change zone type to "+
                                ZoneTypeDescr+"\nR - Undo zone creation\nS - Save";
        sf::Text text(OutputText, font);
        text.setCharacterSize(16);
        text.setPosition(Translation.x, Translation.y+3);
        text.setFillColor(sf::Color::Black);

        for(unsigned int i = 0; i<ZONES.size(); i++)
        {
            for(unsigned int j = 0; j<ZONES[i].getRectanglesToDraw().size(); j++)
                Redactor.draw(ZONES[i].getRectanglesToDraw()[j]);
        }
        for(unsigned int i = 0; i<ZONES.size(); i++)
        {
            for(unsigned int j = 0; j<ZONES[i].getPointsToDraw().size(); j++)
                Redactor.draw(ZONES[i].getPointsToDraw()[j]);
        }
        Redactor.draw(Oy);Redactor.draw(Ox);
        Redactor.draw(text);
        Redactor.display();
    }

    return 0;
}
