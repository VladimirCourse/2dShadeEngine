#ifndef SHADEOBJECT
#define SHADEOBJECT

#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>

//TODO: fix artifacts
class ShadeObject{

private:
    //центр полигона объекта, который отбрасывает тень
    sf::Vector2f _center;
    //позиция объекта
    sf::Vector2f _position;
    //точки полигона
    std::vector <sf::Vector2f> _shapePoints;
    //тень объекта
    sf::ConvexShape _shade;
    //пересечение двух прямых
    bool isLineIntersects(const sf::Vector2f &pa1, const sf::Vector2f &pa2,
                          const sf::Vector2f &pb1, const sf::Vector2f &pb2);
    //поиск вектора от источника света до бесконечности, который не пересекает объект и проходит по краю объекта
    const sf::Vector2f &traceShadeVector(const sf::Vector2f &posFrom, const sf::Vector2f &pointPos, bool &result);

public:
    ShadeObject(const sf::Vector2f &position, const sf::Vector2f &center,
                const std::vector <sf::Vector2f> &shapePoints);
    //пересчитать тень
    void calculateShade(const sf::Vector2f &lightPos);
    const sf::ConvexShape &getShade();

};

#endif // SHADEOBJECT

