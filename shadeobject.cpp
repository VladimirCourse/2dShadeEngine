#include <shadeobject.h>
#include <iostream>

#define MAX_RANGE 5000

ShadeObject::ShadeObject(const sf::Vector2f &position, const sf::Vector2f &center,
                         const std::vector<sf::Vector2f> &shapePoints):
    _position(position), _center(center), _shapePoints(shapePoints){
    _shade.setPointCount(4);
    //цвет и прозрачность тени
    _shade.setFillColor(sf::Color(0,0,0,245));
}
//пересечение прямых
bool ShadeObject::isLineIntersects(const sf::Vector2f &pa1, const sf::Vector2f &pa2,
                                   const sf::Vector2f &pb1, const sf::Vector2f &pb2){
    double v1, v2, v3, v4;
    v1 = (pb2.x - pb1.x) * (pa1.y - pb1.y) - (pb2.y - pb1.y) * (pa1.x - pb1.x);
    v2 = (pb2.x - pb1.x) * (pa2.y - pb1.y) - (pb2.y - pb1.y) * (pa2.x - pb1.x);
    v3 = (pa2.x - pa1.x) * (pb1.y - pa1.y) - (pa2.y - pa1.y) * (pb1.x - pa1.x);
    v4 = (pa2.x - pa1.x) * (pb2.y - pa1.y) - (pa2.y - pa1.y) * (pb2.x - pa1.x);
    return (v1 * v2 < 0) && (v3 * v4 < 0);
}
//поиск вектора-границы тени от источника света posFrom до точки полигона point
const sf::Vector2f &ShadeObject::traceShadeVector(const sf::Vector2f &posFrom, const sf::Vector2f &pointPos, bool &result){
    //приведение к координатам относительно центра
    sf::Vector2f vec = pointPos - posFrom;
    sf::Vector2f eps = pointPos - (_position + _center);
    //кастуем луч далеко по направлению от света до точки полигона
    eps -= eps * 0.9f;
    float size = sqrt(vec.x * vec.x + vec.y * vec.y);
    vec *= MAX_RANGE / size;
    vec += pointPos;
    result = false;
    sf::Vector2f posTo = vec + eps;
    //проверяем, не пересекает ли луч какую-то сторону полигона
    for (int i = 0; i < _shapePoints.size() - 1; i++){
        result = result || isLineIntersects(posFrom, posTo, _shapePoints[i] + _position, _shapePoints[i+1] + _position);
    }
    result = result || isLineIntersects(posFrom, posTo, _shapePoints[0] + _position, _shapePoints.back() + _position);
    return vec;
}
//пересчет тени
void ShadeObject::calculateShade(const sf::Vector2f &lightPos){
    //нашли первую сторону тени
    bool beginFound = false;
    //начало и конец второй стороны тени
    sf::Vector2f lastPoint;
    sf::Vector2f lastEnd;
    double maxSize = 0;
    for (int i = 0; i < _shapePoints.size(); i++){
        bool res = false;
        sf::Vector2f pointPos = _shapePoints[i] + _position;
        sf::Vector2f endPos = traceShadeVector(lightPos, pointPos, res);
        //если луч не пересекает ни одну из сторону полигона
        if (!res){
            //нашли первую сторону тени
            if (!beginFound){
                _shade.setPoint(3, pointPos);
                _shade.setPoint(0, endPos);
                res = true;
                beginFound = true;
            }else{
                //ищем вторую сторону, максимально удаленную от первой
                sf::Vector2f vec = _shade.getPoint(0) - endPos;
                double curSize = sqrt(vec.x * vec.x + vec.y * vec.y);
                if (curSize >= maxSize ){
                    maxSize = curSize;
                    lastPoint = pointPos;
                    lastEnd = endPos;
                }
            }
        }
    }
    //задаем вторую сторону
    _shade.setPoint(2, lastPoint);
    _shade.setPoint(1, lastEnd);
}

const sf::ConvexShape &ShadeObject::getShade(){
    return _shade;
}
