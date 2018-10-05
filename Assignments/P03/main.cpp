//
//  main.cpp
//  SFMLtest
//
//  Created by Logan on 10/2/18.
//  Copyright © 2018 Logan Wheeler. All rights reserved.
//

#include <SFML/Graphics.hpp>
int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}






//frame rate fram lock inside class
//or surround in a logical block.
