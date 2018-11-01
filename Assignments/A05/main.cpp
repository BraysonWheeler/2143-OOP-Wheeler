#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>



// https://www.sfml-dev.org/tutorials/2.5/system-time.php
using namespace std;

class Counter{
private:

public:
    int Timer,Seconds,upDown;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time start;
    sf::Time end;
    sf::Text text;

    
    
    Counter(int s, int ud){
        start = sf::seconds(s);
        end = sf::seconds(s);
        setUpDown(ud);
    }
    
    string toString(){
        stringstream ss;
        ss << Timer <<endl;
        
        string newString = ss.str();
        return newString;
    }
    
    void setUpDown(int updown){
        upDown = updown;
    }
    void startClock(){
        if (upDown == 1){
            Timer = clock.getElapsedTime().asSeconds();
        }
        else{
            elapsed = clock.getElapsedTime();
            Timer = start.asSeconds()-elapsed.asSeconds();
            
        }
    }
    
    void reset(){
        clock.restart();
    }
    int printClock(){
        return Timer;
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Logan Wheeler Assignment 5");
    
    int updown, seconds;
    int count = 0;
    bool pressed = false;
    
    sf::Text text;
    sf::Font font;
    
    cout << endl << "IMPORTANT : RIGHT click window to start clock." << endl;
    cout << "            LEFT click to reset clock" << endl << endl;
    cout << "count up or down? input 1 up or 0 down" << endl;
    cin >> updown;
    cout << "set length of time to run 0 - infinity?" << endl;
    cin >> seconds;
    
    if (!font.loadFromFile("Segment7Standard.otf"))
    {
        cout << "error loading text" << endl;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
    Counter C(seconds, updown);
    

    
    while (window.isOpen())
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            pressed = true;
        }
        if(pressed == true){
            if(count == 0){
                C.reset(); 
                count++;
            }
            sf::Event event;
            // If window is closed by pressing x
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            //Converts int C.Timer to string prints for testing not working though
            cout << C.toString();
            text.setString(C.toString());
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                C.reset();
            }
            if(C.upDown == 1){
                C.startClock();
            }
            if(updown == 0){
                C.startClock();
            }
            if (updown == 1 && C.Timer > seconds){
                window.close();
            }
            if (updown == 0 && C.Timer < 0){
                window.close();
            }
            
            window.clear();
            window.draw(text);
            window.display();
    
            }
    }
    return 0;
}

