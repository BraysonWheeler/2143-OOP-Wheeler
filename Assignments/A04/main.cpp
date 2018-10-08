

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

struct golCell {
    bool isAlive;
    int neighborCount;
    RectangleShape Rect;
    int Width;
    int Height;
    
    golCell(){
        Width = 10;
        Height = 10;
        Rect.setSize(sf::Vector2f(Width, Height));
        Rect.setFillColor(Color::Green);
        Rect.setOutlineColor(Color::Black);
        Rect.setOutlineThickness(1);
    }
    
    void setCellPos(int x,int y){
        Rect.setPosition(x*Width, y*Height);
    }
    
};

struct gameOfLife{
    int Width;
    int Height;
    int framerate = 100;
    int framecount = 0;
    RenderWindow Window;
    golCell** World;
    gameOfLife(int width,int height) {
        Width = width;
        Height = height;
        Window.create(VideoMode(Width, Height), "Game of Life");
        
        World = new golCell*[height];
        
        for(int i=0;i<height;i++){
            World[i] = new golCell[width];
            for(int j=0;j<width;j++){
                World[i][j].setCellPos(i,j);
            }
        }
    }
    
    void drawWorld(){
        Window.clear();
        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){
                Window.draw(World[i][j].Rect);
            }
        }
        Window.display();
    }
};



int main(){
    
    gameOfLife Gol(1000,1000);
    
    
    
    while (Gol.Window.isOpen()){
        
        Event event;
        
        while (Gol.Window.pollEvent(event)){
            
            if(Gol.framecount == Gol.framerate){
                Gol.drawWorld();
                if(event.type == Event::Closed){
                    Gol.Window.close();
                }
            }
            
            Gol.framecount++;
        }
        
        
    }
    
    return 0;
}

