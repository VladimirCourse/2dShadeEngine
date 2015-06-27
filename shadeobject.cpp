#include <shadeobject.h>

ShadeObject::ShadeObject(sf::Vector2f center, std::vector<sf::Vector2f> shapePoints){
    m_center = center;
    m_shapePoints = shapePoints;
    m_shade.setPointCount(m_shapePoints.size());
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
    sf::Vector2f eps = point - m_center;
    eps = eps*0.5f - eps;
    float size = sqrt(vec.x*vec.x + vec.y*vec.y);
    vec.x*=1000/size;
    vec.y*=1000/size;
    vec += point + eps;
    bool b1 = checkLineIntersection(side1, point, posFrom, vec);
    bool b2 = checkLineIntersection(point, side2, posFrom, vec);
    result = b1 || b2;
    if (result){
        return point;
    }
    return vec;
}

void ShadeObject::formShade(sf::Vector2f lightPos){
    bool res = false;
    bool taked = false;
    int polySize = m_shapePoints.size();
    for (int i = 0; i < polySize; i++){
        int left = i - 1, right = i + 1;
        if (i == 0){
            left = polySize - 1;
        }
        if (i == polySize - 1){
            right = 0;
        }
        sf::Vector2f endPos = getShadeSideVector(lightPos, m_shapePoints[i], m_shapePoints[left], m_shapePoints[right], res);
        if (!res && !taked){
            taked = true;
            m_shade.setPoint(3, m_shapePoints[i]);
            m_shade.setPoint(0, endPos);
            res = false;
        }
        if (!res && taked){
            m_shade.setPoint(2, m_shapePoints[i]);
            m_shade.setPoint(1, endPos);
        }
    }
}

sf::ConvexShape ShadeObject::getShade(){
    return m_shade;
}
