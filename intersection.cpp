#include "intersection.h"


float Intersection::dot(sf::Vector2f vec1, sf::Vector2f vec2){
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

sf::Vector2f Intersection::normal(sf::Vector2f vec){
    float size = sqrt(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2f(vec.x/size, vec.y/size);
}

sf::Vector2f Intersection::perpend(sf::Vector2f vec){
    return sf::Vector2f(vec.y, -vec.x);
}

sf::Vector2f Intersection::projection(std::vector <sf::Vector2f> poly, sf::Vector2f axis){
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

bool Intersection::segOverlap(sf::Vector2f seg1, sf::Vector2f seg2){
    return (seg1.x < seg2.x && seg1.y > seg2.x) || (seg1.x > seg2.x && seg2.y > seg1.x);
}

bool Intersection::checkIntersection(std::vector<sf::Vector2f> poly1, std::vector<sf::Vector2f> poly2){
    sf::Vector2f axis = poly1.back() - poly1[0];
    axis = perpend(axis);
    sf::Vector2f pr1 = projection(poly1, axis);
    sf::Vector2f pr2 = projection(poly2, axis);
    if (!segOverlap(pr1, pr2)){
        return 0;
    }
    for (int i = 0; i < poly1.size() - 1; i++){
        axis = poly1[i + 1] - poly1[i];
        axis = perpend(axis);
        pr1 = projection(poly1, axis);
        pr2 = projection(poly2, axis);
        if (!segOverlap(pr1, pr2)){
            return 0;
        }
    }
    return 1;
}
bool Intersection::intersection(std::vector <sf::Vector2f> poly1, std::vector <sf::Vector2f> poly2){
    return checkIntersection(poly1, poly2) && checkIntersection(poly2, poly1);
}
