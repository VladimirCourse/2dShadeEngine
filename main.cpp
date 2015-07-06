#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "shadeobject.h"

#include "intersection.h"

int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Texture back;
    back.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\background.png");
    back.setSmooth(true);
    sf::Sprite backSprite;
    backSprite.setTexture(back);
    backSprite.setScale(800.0f/back.getSize().x, 600.0f/back.getSize().y);


    sf::ConvexShape p1;
    p1.setPointCount(4);
    p1.setPoint(0, sf::Vector2f(0, 0));
    p1.setPoint(1, sf::Vector2f(55, 0));
    p1.setPoint(2, sf::Vector2f(130, 55));
    p1.setPoint(3, sf::Vector2f(0, 55));
    p1.setFillColor(sf::Color(0,222,225,255));

    sf::ConvexShape p2;
    p2.setPointCount(5);
    p2.setPoint(0, sf::Vector2f(0, 0));
    p2.setPoint(1, sf::Vector2f(55, 0));
    p2.setPoint(2, sf::Vector2f(130, 55));
    p2.setPoint(3, sf::Vector2f(100, 155));
    p2.setPoint(4, sf::Vector2f(0, 55));
    p2.setFillColor(sf::Color(0,0,225,255));

    p2.setPosition(300,300);
    // lightSprite.setColor(sf::Color(0,0,0,240));
    // Start the game loop


    std::vector <sf::Vector2f> pts1;
    for (int i = 0; i < p1.getPointCount(); i++){
        pts1.push_back(p1.getPoint(i));
    }

    std::vector <sf::Vector2f> pts;
    for (int i = 0; i < p2.getPointCount(); i++){
        pts.push_back(p2.getPoint(i));
    }
    ShadeObject obj(p2.getPosition(), sf::Vector2f(65,65), pts);
    sf::Texture lightTexture;
    sf::Sprite light1;

    sf::RenderTexture lightMapTexture;
    sf::Sprite lightmap;

    lightMapTexture.create(800, 600); // Make a lightmap that can cover our screen
    lightmap.setTexture(lightMapTexture.getTexture()); // Make our lightmap sprite use the correct texture

    lightTexture.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\light2.png"); // Load in our light
    lightTexture.setSmooth(true); // (Optional) It just smoothes the light out a bit

    light1.setTexture(lightTexture); // Make our lightsprite use our loaded image

    sf::Texture lamptex;
    lamptex.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\lamp.png");
    sf::Sprite light2;
    light2.setTexture(lamptex);
    light2.setScale(0.5,0.5);
    light2.setOrigin(160,160);

    Intersection inter;
    /*
    std::vector <sf::Vector2f> poly1;
    std::vector <sf::Vector2f> poly2;
    poly1.push_back(sf::Vector2f(0, 0));
    poly1.push_back(sf::Vector2f(0, 3));
    poly1.push_back(sf::Vector2f(3, 3));
    poly1.push_back(sf::Vector2f(3, 0));

    poly2.push_back(sf::Vector2f(4, 4));
    poly2.push_back(sf::Vector2f(4, 6));
    poly2.push_back(sf::Vector2f(6, 6));
    poly2.push_back(sf::Vector2f(6, 4));
    std::cout<<inter.intersection(poly1, poly2);
    */
    for (int i = 0; i < pts.size(); i++){
        pts[i] += p2.getPosition();
    }
    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type = sf::Event::MouseMoved){

                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
                light1.setPosition(pos - sf::Vector2f(160, 160));
                light2.setPosition(pos);
                obj.formShade(pos);
                p1.setPosition(pos);
                for (int i = 0; i < pts1.size(); i++){
                    pts1[i] = pos + p1.getPoint(i);
                 //   std::cout<<pts1[i].x <<" " << pts1[i].y <<std::endl;
                }
            //     std::cout<<"////////////"<<std::endl;
                for (int i = 0; i < pts.size(); i++){

                //    std::cout<<pts[i].x <<" " << pts[i].y <<std::endl;
                }
             //   std::cout<<std::endl;

                std::cout<<inter.intersection(pts1, pts)<<std::endl;


            }
            if (event.type = sf::Event::KeyPressed ){

                if (event.key.code == sf::Keyboard::A){

                }
            }
        }

        window.clear();
        window.draw(backSprite);
        window.draw(obj.getShade());
        window.draw(p2);
         window.draw(p1);
        lightMapTexture.clear(sf::Color(222,222,222));
        light1.setColor(sf::Color(230,230,55,255));
        lightMapTexture.draw(light1, sf::BlendAdd);
        lightMapTexture.display();
        window.draw(light2);
        lightmap.setTextureRect(sf::IntRect(0, 0, 800, 600)); // What from the lightmap we will draw
        lightmap.setPosition(0, 0); // Where on the backbuffer we will draw
        window.draw(lightmap, sf::BlendMultiply); // This blendmode is used to add the darkness from the lightmap with the parts where we draw ur light image show up brighter

        window.display();
    }
    return EXIT_SUCCESS;
}


