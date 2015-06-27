#ifndef SHADEOBJECT
#define SHADEOBJECT

#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>

class ShadeObject{

private:
    //центр полигона объекта, который отбрасывает тень
    sf::Vector2f m_center;
    //точки полигона
    std::vector <sf::Vector2f> m_shapePoints;
    //сама тень
    sf::ConvexShape m_shade;
    bool checkLineIntersection(sf::Vector2f pa1, sf::Vector2f pa2 , sf::Vector2f pb1, sf::Vector2f pb2);
    sf::Vector2f getShadeSideVector(sf::Vector2f posFrom, sf::Vector2f point, sf::Vector2f side1, sf::Vector2f side2, bool &result);

public:
    ShadeObject(sf::Vector2f center, std::vector <sf::Vector2f> shapePoints);
    void formShade(sf::Vector2f lightPos);
    sf::ConvexShape getShade();

};

#endif // SHADEOBJECT

