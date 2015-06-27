#include <shadeobject.h>
#include <iostream>

ShadeObject::ShadeObject(sf::Vector2f center, std::vector<sf::Vector2f> shapePoints){
    m_center = center;
    m_shapePoints = shapePoints;
    m_shade.setPointCount(4);
    m_shade.setFillColor(sf::Color(0,0,0,245));
}

bool ShadeObject::checkLineIntersection(sf::Vector2f pa1, sf::Vector2f pa2 , sf::Vector2f pb1, sf::Vector2f pb2){
    float v1,v2,v3,v4;
    v1 = (pb2.x - pb1.x) * (pa1.y - pb1.y) - (pb2.y - pb1.y) * (pa1.x - pb1.x);
    v2 = (pb2.x - pb1.x) * (pa2.y - pb1.y) - (pb2.y - pb1.y) * (pa2.x - pb1.x);
    v3 = (pa2.x - pa1.x) * (pb1.y - pa1.y) - (pa2.y - pa1.y) * (pb1.x - pa1.x);
    v4 = (pa2.x - pa1.x) * (pb2.y - pa1.y) - (pa2.y - pa1.y) * (pb2.x - pa1.x);
    return (v1*v2<0) && (v3*v4<0);
}

sf::Vector2f ShadeObject::getShadeSideVector(sf::Vector2f posFrom, sf::Vector2f point, sf::Vector2f side1, sf::Vector2f side2, bool &result){
    sf::Vector2f vec = point - posFrom;
    sf::Vector2f eps = point - (m_center + sf::Vector2f(60, 60));
    eps = eps*0.5f - eps;
    float size = sqrt(vec.x*vec.x + vec.y*vec.y);
    //пофиксить для близкого расстояния
    vec *=sqrtf(500.0/size);
    vec += point;
    bool b1 = checkLineIntersection(side1, point + eps, posFrom, vec);
    bool b2 = checkLineIntersection(point + eps, side2, posFrom, vec);
    result = b1 || b2;
    if (result){
        return point;
    }
    return vec;
}

void ShadeObject::formShade(sf::Vector2f lightPos){
    bool res = false;
    int polySize = m_shapePoints.size();
    int takeId = -1;
    for (int i = 0; i < polySize; i++){
        int left = i - 1, right = i + 1;
        if (i == 0){
            left = polySize - 1;
        }
        if (i == polySize){
            right = 0;
        }
        sf::Vector2f pointPos =  m_shapePoints[i] + m_center;
        sf::Vector2f endPos = getShadeSideVector(lightPos, pointPos, m_shapePoints[left] + m_center, m_shapePoints[right] + m_center, res);
        if (!res && takeId == -1){
            takeId = i;
            m_shade.setPoint(3, pointPos);
            m_shade.setPoint(0, endPos);
            res = false;
        }
        if (!res && takeId != -1){
            int px = pointPos.x, py = pointPos.y;
            if ((m_shade.getPoint(takeId).x == px && px == lightPos.x) || (m_shade.getPoint(takeId).y == py && py == lightPos.y)){
                continue;
            }
            m_shade.setPoint(2, pointPos);
            m_shade.setPoint(1, endPos);
        }
    }
}

sf::ConvexShape ShadeObject::getShade(){
    return m_shade;
}
