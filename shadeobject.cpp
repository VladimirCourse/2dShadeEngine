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

bool ShadeObject::checkAllIntersections(sf::Vector2f posFrom, sf::Vector2f posTo){
    bool result = 0;
    for (int i = 0; i < m_shapePoints.size() - 1; i++){
        result = result || checkLineIntersection(posFrom, posTo, m_shapePoints[i] + m_center, m_shapePoints[i+1] + m_center);
    }
    return result || checkLineIntersection(posFrom, posTo, m_shapePoints[0] + m_center, m_shapePoints.back() + m_center);
}

sf::Vector2f ShadeObject::getShadeSideVector(sf::Vector2f posFrom, sf::Vector2f point, bool &result){
    sf::Vector2f vec = point - posFrom;
    sf::Vector2f eps = point - (m_center + sf::Vector2f(65, 65));
    eps = eps - eps * 0.9f;
    float size = sqrt(vec.x*vec.x + vec.y*vec.y);
    //4len с ним, и так работает
    vec*=5000/size;
    //float angle = vec.x/size;
   // std::cout<<acos(angle)*180.0/3.14<<std::endl;
  //  vec.x+=100;
  //  vec.y+=tan(angle)*100;
 //   float c = ((vec.x + 100)*vec.y)/vec.x - vec.y;
    //std::cout<<vec.y + c<<std::endl;
   // vec.y = c;
   // vec.x += 100;
    vec += point;
    result = checkAllIntersections(posFrom, vec + eps);
    return vec;
}

void ShadeObject::formShade(sf::Vector2f lightPos){
    bool res = false;
    int polySize = m_shapePoints.size();
    int takeId = -1;
    sf::Vector2f lastPoint;
    sf::Vector2f lastEnd;
    float maxSize = 0;
    for (int i = 0; i < polySize; i++){
        sf::Vector2f pointPos =  m_shapePoints[i] + m_center;
        sf::Vector2f endPos = getShadeSideVector(lightPos, pointPos, res);
        if (!res && takeId == -1){
            takeId = i;
            m_shade.setPoint(3, pointPos);
            m_shade.setPoint(0, endPos);
            res = true;
        }
        if (!res && takeId != -1){
            sf::Vector2f vec = m_shade.getPoint(0) - endPos;
            float curSize = sqrt(vec.x*vec.x + vec.y*vec.y);
            if (curSize >= maxSize ){
                maxSize = curSize;
                lastPoint = pointPos;
                lastEnd = endPos;
           }
        }
    }
    m_shade.setPoint(2, lastPoint);
    m_shade.setPoint(1, lastEnd);
}

sf::ConvexShape ShadeObject::getShade(){
    return m_shade;
}
