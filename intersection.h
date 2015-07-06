#ifndef INTERSECTION
#define INTERSECTION

#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>


class Intersection{

private:
    //векторное произведение
    float dot(sf::Vector2f vec1, sf::Vector2f vec2);
    //нормаль
    sf::Vector2f normal(sf::Vector2f vec);
    //перпендикулярный вектор
    sf::Vector2f perpend(sf::Vector2f vec);
    //проекция полигона на ось
    sf::Vector2f projection(std::vector <sf::Vector2f> poly, sf::Vector2f axis);
    //пересечение отрезков
    bool segOverlap(sf::Vector2f seg1, sf::Vector2f seg2);
    //пересечение полигона poly1 с poly2
    bool checkIntersection(std::vector <sf::Vector2f> poly1, std::vector <sf::Vector2f> poly2);

public:
    bool intersection(std::vector <sf::Vector2f> poly1, std::vector <sf::Vector2f> poly2);
};


#endif // INTERSECTION

