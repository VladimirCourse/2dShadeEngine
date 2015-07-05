#ifndef INTERSECTION
#define INTERSECTION

#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>


class Intersection{

private:
    float dot(sf::Vector2f vec1, sf::Vector2f vec2);
    sf::Vector2f normal(sf::Vector2f vec);
    sf::Vector2f perpend(sf::Vector2f vec);
    sf::Vector2f projection(std::vector <sf::Vector2f> poly, sf::Vector2f axis);
    bool segOverlap(sf::Vector2f seg1, sf::Vector2f seg2);

public:
    bool checkIntersection(std::vector <sf::Vector2f> poly1, std::vector <sf::Vector2f> poly2);
};


#endif // INTERSECTION

