#include <iostream>
#include <SFML/Graphics.hpp>
#include "shadeobject.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Texture back;
    back.loadFromFile("D:\\Src\\testsfml\\background.png");
    back.setSmooth(true);
    //фон
    sf::Sprite backSprite;
    backSprite.setTexture(back);
    backSprite.setScale(800.0f / back.getSize().x, 600.0f / back.getSize().y);
    //объект, отбрасывающий тень
    sf::ConvexShape p1;
    p1.setPointCount(5);
    p1.setPoint(0, sf::Vector2f(0, 0));
    p1.setPoint(1, sf::Vector2f(55, 0));
    p1.setPoint(2, sf::Vector2f(130, 55));
    p1.setPoint(3, sf::Vector2f(100, 155));
    p1.setPoint(4, sf::Vector2f(0, 55));
    p1.setFillColor(sf::Color(0,0,225,255));
    p1.setPosition(300,300);

    std::vector <sf::Vector2f> pts;
    for (int i = 0; i < p1.getPointCount(); i++){
        pts.push_back(p1.getPoint(i));
    }

    ShadeObject obj(p1.getPosition(), sf::Vector2f(65, 65), pts);

    for (int i = 0; i < pts.size(); i++){
        pts[i] += p1.getPosition();
    }
    //темная текстура поверх экрана
    sf::RenderTexture lightMapTexture;
    sf::Sprite lightmap;
    lightMapTexture.create(800, 600);
    lightmap.setTexture(lightMapTexture.getTexture());
    //свет
    sf::Texture lightTexture;
    sf::Sprite lightShine;
    lightTexture.loadFromFile("D:\\Src\\testsfml\\light2.png");
    lightTexture.setSmooth(true);
    lightShine.setTexture(lightTexture);
    //лампа
    sf::Texture lamptex;
    sf::Sprite lamp;
    lamptex.loadFromFile("D:\\Src\\testsfml\\lamp.png");
    lamp.setTexture(lamptex);
    lamp.setScale(0.5,0.5);
    lamp.setOrigin(160,160);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type = sf::Event::MouseMoved){
                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
                lightShine.setPosition(pos - sf::Vector2f(160, 160));
                lamp.setPosition(pos);
                //если изменилась позиция света, пересчитать тень
                obj.calculateShade(pos);
            }
        }

        window.clear();
        window.draw(backSprite);
        window.draw(obj.getShade());
        window.draw(p1);
        lightMapTexture.clear(sf::Color(15, 15, 15));
        lightShine.setColor(sf::Color(230, 230, 55, 255));
        lightMapTexture.draw(lightShine, sf::BlendAdd);
        lightMapTexture.display();
        window.draw(lamp);
        lightmap.setTextureRect(sf::IntRect(0, 0, 800, 600));
        lightmap.setPosition(0, 0);
        window.draw(lightmap, sf::BlendMultiply);

        window.display();
    }
    return EXIT_SUCCESS;
}


