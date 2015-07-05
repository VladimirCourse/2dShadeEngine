#include "intersection.h"


float Intersection::dot(sf::Vector2f vec1, sf::Vector2f vec2){
    return vec1 * vec2;
}

sf::Vector2f Intersection::normal(sf::Vector2f vec){
    float size = sqrt(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2f(vec.x/size, vec.y/size);
}

sf::Vector2f Intersection::perpend(sf::Vector2f vec){
    return sf::Vector2f(vec.y, -vec.x);
}
//проверить работу
sf::Vector2f projection(std::vector <sf::Vector2f> poly, sf::Vector2f axis){
    axis = normal(axis);
    float mmin = dot(poly[0], axis);
    float mmax = mmin;
    for (int i = 1; i < poly.size(); i++){
        float cur = dot(poly[i], axis);
        if (cur < mmin){
            mmin = cur;
        }
        if (cur > mmax){
            mmax = cur;
        }
    }

    return sf::Vector2f(mmin, mmax);
}
//проверить работу
bool Intersection::segOverlap(sf::Vector2f seg1, sf::Vector2f seg2){
    return (seg1.x < seg2.x && seg1.y > seg2.x) || (seg1.x > seg2.x && seg2.y > seg1.x);
}
//допилить
bool Intersection::checkIntersection(std::vector<sf::Vector2f> poly1, std::vector<sf::Vector2f> poly2){
    for (int i = 0; i < poly1.size() - 1; i++){

    }
}
