#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "shadeobject.h"

const sf::Vector2f LEFTUP = sf::Vector2f(-1, -1);
const sf::Vector2f RIGHTUP = sf::Vector2f(1, -1);
const sf::Vector2f LEFTDOWN = sf::Vector2f(-1, 1);
const sf::Vector2f RIGHTDOWN = sf::Vector2f(1, 1);

bool intersect(sf::Vector2f pa1, sf::Vector2f pa2 , sf::Vector2f pb1, sf::Vector2f pb2){
    float v1,v2,v3,v4;

    v1 = (pb2.x - pb1.x) * (pa1.y - pb1.y) - (pb2.y - pb1.y) * (pa1.x - pb1.x);
    v2 = (pb2.x - pb1.x) * (pa2.y - pb1.y) - (pb2.y - pb1.y) * (pa2.x - pb1.x);
    v3 = (pa2.x - pa1.x) * (pb1.y - pa1.y) - (pa2.y - pa1.y) * (pb1.x - pa1.x);
    v4 = (pa2.x - pa1.x) * (pb2.y - pa1.y) - (pa2.y - pa1.y) * (pb2.x - pa1.x);
    // std::cout<<v1<<v2<<v3<<v4<<std::endl;
    return (v1*v2<0) && (v3*v4<0);
}

sf::Vector2f getVec(sf::Vector2f posFrom, sf::Vector2f point, sf::Vector2f side1, sf::Vector2f side2, bool &result, sf::Vector2f eps){
    sf::Vector2f vec = point - posFrom;
    float size = sqrt(vec.x*vec.x + vec.y*vec.y);
    // std::cout<<size<<std::endl;
    vec.x*=1000/size;
    vec.y*=1000/size;
    // std::cout<< size<<std::endl;
    vec += point + eps;
    //      std::cout<< vec.x<<std::endl;
    //std::cout<<side1.x<<" "<<point.x<<" "<<posFrom.x<< " "<<vec.x<<std::endl;
    bool b1 = intersect(side1, point, posFrom, vec);
    bool b2 = intersect(point, side2, posFrom, vec);
    result = b1 || b2;
    // std::cout<<result<<std::endl;
    if (result){

        //  std::cout<<1;
        return point;
    }
    return vec;
}

int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Texture back;
    back.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\back.png");
    sf::Sprite backSprite;
    backSprite.setTexture(back);
    sf::Texture front;
    front.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\front.png");
    sf::Sprite frontSprite;
    frontSprite.setTexture(front);
    frontSprite.setColor(sf::Color(0,0,0,245));
    sf::Texture light;
    light.loadFromFile("C:\\Users\\wooden\\Documents\\testsfml\\light2.png");
    sf::Sprite lightSprite;
    lightSprite.setTexture(light);
    lightSprite.setColor(sf::Color(222,222,55, 100));
    sf::ConvexShape p2;
    p2.setPointCount(5);
    p2.setPoint(0, sf::Vector2f(0, 0));
    p2.setPoint(1, sf::Vector2f(55, 0));
    p2.setPoint(2, sf::Vector2f(130, 55));
    p2.setPoint(3, sf::Vector2f(100, 155));
    p2.setPoint(4, sf::Vector2f(0, 55));
    p2.setFillColor(sf::Color(0,0,225,255));
    sf::ConvexShape polygon;
    polygon.setPointCount(4);
    polygon.setPoint(0, sf::Vector2f(0, 0));
    polygon.setPoint(1, sf::Vector2f(800, 0));
    polygon.setPoint(2, sf::Vector2f(800, 600));
    polygon.setPoint(3, sf::Vector2f(0, 600));
    polygon.setFillColor(sf::Color(0,0,0,248));
    double alpha = 248;
    p2.setPosition(300,300);
    // lightSprite.setColor(sf::Color(0,0,0,240));
    // Start the game loop
    double color = 0;
    int t = 1;
    sf::ConvexShape shade;
    shade.setPointCount(4);
    shade.setPoint(0, sf::Vector2f(300, 300));
    shade.setPoint(1, sf::Vector2f(355, 300));
    shade.setPoint(2, sf::Vector2f(55, 55));
    shade.setPoint(3, sf::Vector2f(0, 55));

    shade.setFillColor(sf::Color(0,0,0,245));
    sf::Vertex line[8];
    sf::Vector2f pointPos[] = {LEFTUP, RIGHTUP, RIGHTDOWN + sf::Vector2f(1,0),RIGHTDOWN,LEFTDOWN};

    sf::CircleShape shape(200);
    //  std::cout<<shape.getPointCount();

    // zapilit intensivnost teni v zavisimosti ot rasstoyaniya
    shape.setFillColor(sf::Color(100, 250, 50, 100));
    int pos1,  pos2;

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
                //  polygon.setPoint(2, sf::Vector2f(sf::Mouse::getPosition(window)));
                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
                lightSprite.setPosition(pos - sf::Vector2f(160, 160));
            //    std::cout<<pos.y<<" "<<p2.getPosition().x<<std::endl;
                obj.formShade(pos);
              /*  light1.setPosition(pos - sf::Vector2f(160, 160));
                line[0].position = pos;
                bool res = false;

                bool taked = false;

                for (int i = 0; i < 5; i++){
                    int left = i - 1, right = i + 1;
                    if (i == 0){
                        left = 4;
                    }
                    if (i == 4){
                        right = 0;
                    }
                    // line[i+1].position = p2.getPosition() + p2.getPoint(i);
                    line[i+1].position = getVec(pos, p2.getPosition() + p2.getPoint(i), p2.getPoint(left) + p2.getPosition(), p2.getPoint(right) + p2.getPosition(), res,  pointPos[i]);

                    if (!res && !taked){
                        //   std::cout<<i<<" ";
                        taked = true;
                        //posOne = line[i+1].position;
                        pos1 = i;
                         shade.setPoint(3, p2.getPoint(i) + p2.getPosition());
                         shade.setPoint(0, line[i+1].position);

                        res = false;
                    }

                    if (!res && taked){
                        pos2 = i;
                        // std::cout<<i<<std::endl;
                                  shade.setPoint(2, p2.getPoint(i) + p2.getPosition());
                                shade.setPoint(1, line[i+1].position);
                    }
                }
                // std::cout<<taked<<std::endl;
                std::cout<<pos1<<" "<<pos2<<std::endl;
               // shade.setPoint(3, p2.getPoint(pos1) + p2.getPosition());
               // shade.setPoint(0, line[pos1+1].position);
               // shade.setPoint(2, p2.getPoint(pos2) + p2.getPosition());
               // shade.setPoint(1, line[pos2+1].position);*/

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
        lightMapTexture.clear(sf::Color(222,222,222));
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


