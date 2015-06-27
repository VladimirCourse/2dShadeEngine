#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "shadeobject.h"



int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Texture back;
    back.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\back.png");
    sf::Sprite backSprite;
    backSprite.setTexture(back);


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


    std::vector <sf::Vector2f> pts;
    for (int i = 0; i < p2.getPointCount(); i++){
        pts.push_back(p2.getPoint(i));
    }
    ShadeObject obj(p2.getPosition(), pts);
    sf::Texture lightTexture;
    sf::Sprite light1;

    sf::RenderTexture lightMapTexture;
    sf::Sprite lightmap;

    lightMapTexture.create(800, 600); // Make a lightmap that can cover our screen
    lightmap.setTexture(lightMapTexture.getTexture()); // Make our lightmap sprite use the correct texture

    lightTexture.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\light2.png"); // Load in our light
    lightTexture.setSmooth(true); // (Optional) It just smoothes the light out a bit

    light1.setTexture(lightTexture); // Make our lightsprite use our loaded image



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
                obj.formShade(pos);

            }
            if (event.type = sf::Event::KeyPressed ){

                if (event.key.code == sf::Keyboard::A){

                }
            }
        }

        window.clear();
        // Draw the sprite
        window.draw(backSprite);
        //window.draw(shade);
        window.draw(obj.getShade());
        window.draw(p2);
        lightMapTexture.clear(sf::Color(11,11,11));
        light1.setColor(sf::Color(255,180,130,255));
        lightMapTexture.draw(light1, sf::BlendAdd);
        lightMapTexture.display();

        lightmap.setTextureRect(sf::IntRect(0, 0, 800, 600)); // What from the lightmap we will draw
        lightmap.setPosition(0, 0); // Where on the backbuffer we will draw
        window.draw(lightmap, sf::BlendMultiply); // This blendmode is used to add the darkness from the lightmap with the parts where we draw ur light image show up brighter

        // window.draw(polygon);

        // window.draw(lightSprite, sf::BlendMultiply);



        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}


