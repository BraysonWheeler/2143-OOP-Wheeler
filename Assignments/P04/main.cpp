/**
 *  Course: CMPS 2143 - OOP
 *  Assignment: A01
 *  Purpose: The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbors, which are the cells that are directly horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:
 
        Any live cell with fewer than two live neighbors dies, as if caused by under-population.
        Any live cell with more than three live neighbors dies, as if by overcrowding.
        Any live cell with two or three live neighbors lives on to the next generation.
        Any dead cell with exactly three live neighbors becomes a live cell.
 *  @author Logan Wheeler
 *  @version 1.1 10/15/18
 */


#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

#define CELLSIZE 10

using namespace std;
using namespace sf;

/**
 * lifeCell : A single instance of a cell in a Game of Life array
 * @Extends:
 *   sf::Drawable
 * @Data-Elements:
 *     RectangleShape rect;    // sfml rectangle type
 *     bool alive;        // is cell alive or not
 * @Methods:
 *     void draw(RenderTarget& target, RenderStates state) const
 */
struct lifeCell : public Drawable {
    RectangleShape rect;
    bool alive;
    int neighborCount;
protected:
    /**
     * void draw: draws an SFML shape to an SFML window.
     */
    void draw(RenderTarget& target, RenderStates state) const // means this method won't change
    // anything...
    {
        target.draw(rect);
    }
};

/**
 * Starter class to represent game of life
 */
class gameOfLife {
private:
    lifeCell **World;                // double pointer to a lifeCell (defined above)
    int Rows;                    // num rows in game board
    int Cols;                    // num cols in game board
    RenderWindow &WindowRef;    // reference to sfml window so we can draw to it.
    string line;

    
public:
    /**
     * GameOfLife Constructor extends sfml WindowRef
     * param:
     *    RenderWindow : a reference to our sfml window
     *
     */
    gameOfLife(RenderWindow &thatWindow,ifstream &infile) : WindowRef(thatWindow) {
        initBoard(infile);
    }

    /**
     * GameOfLife Constructor extends sfml WindowRef
     * param:
     *    RenderWindow : a reference to our sfml window
     *    int rows : num of rows in board
     *    int cols : num of cols in board
     *
     */
    
    gameOfLife(RenderWindow &thatWindow, int rows, int cols,ifstream &infile) : WindowRef(thatWindow) {
        initBoard(infile);
    }
        /**
         * Function: print
         *    Prints out the array in text format rather than SFML
         *
         * param:
         *    None
         * returns:
         *       True or false
         */
    
    void print(){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Cols; j++){
                cout << World[i][j].alive;
            }
            cout << endl;
        }
    }
        /**
         * Function: rulse
         *     Runs the rules GOL:
         *        less than two the cell dies
         *        more than three the cell dies
         *        two or three the cell lives
         *
         *
         * param:
         *    None
         * returns:
         *       True or false
         */
    
    void rules(){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Cols; j++){
                if(World[i][j].neighborCount < 2){
                    World[i][j].alive = 0;
                }

                if(World[i][j].neighborCount > 3){
                    World[i][j].alive = 0;
                }
                
                if(World[i][j].neighborCount == 3 && World[i][j].alive == 0){
                    World[i][j].alive = 1;
                }
            }
        }
    }
        

        /**
         * Function: onWorld
         *     Tests if World[i][j] is on the board
         * param:
         *    None
         * returns:
         *       True or false
         */
    
    bool onWorld(int i,int j){
        return (i >=0 && i < Rows && j >= 0 && j < Cols);
    }
    
        /**
         * Function: countNeighbors
         *     Cheks to see if neighbors are on the world and if the cell is alive
         *     increases the neighborcount
         * param:
         *    None
         * returns:
         *       None
         */
    
    void countNeighbors(){
        for(int i = 0; i < Rows; i++){
            for(int j = 0; j < Cols; j++){
                if(onWorld(i-1,j-1)){
                    if(World[i-1][j-1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i-1,j)){
                    if(World[i-1][j].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i-1,j+1)){
                    if(World[i-1][j+1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i,j-1)){
                    if(World[i][j-1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i,j+1)){
                    if(World[i][j+1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i+1,j-1)){
                    if(World[i+1][j-1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i+1,j)){
                    if(World[i+1][j].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
                if(onWorld(i+1,j+1)){
                    if(World[i+1][j+1].alive == 1){
                        World[i][j].neighborCount++;
                    }
                }
            }
        }
    }
    
    /**
     * Function: initBoard
     *     intitilizes board from input file creates an array full of cells
     * param:
     *    None
     * returns:
     *       None
     */
    void initBoard(ifstream &infile){
        
        infile >> Rows >> Cols;
        World = new lifeCell*[Rows];

        for(int i=0;i< Rows;i++){
            World[i] = new lifeCell[Cols];
        }
        
        
        for(int i = 0; i < Rows; i++){
            infile >> line;
            cout << line;
            for(int j = 0; j < Cols; j++){
                World[i][j].alive = line[j] - 48;
            }
            cout << endl;
            
        }
    }
    
    /**
     * Function: resetNeightborCount
     *     resets NeighborCount in life cell to 0 used for checking neighbor count
     * param:
     *    None
     * returns:
     *       None
     */
    
    void resetNeighborCount() {
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                World[i][j].neighborCount = 0;
            }
        }
    }
    
        /**
         * Function: printBoard
         *     Prints board to an sfml window
         * parm
         *    None
         * returns:
         *       None
         */
    
    void printBoard() {
        int x = 0;
        int y = 0;
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                if (World[i][j].alive == 1) {
                    y = (i) * CELLSIZE;
                    x = (j) * CELLSIZE;
                    std::cout << x << "," << y << std::endl;
                    World[i][j].rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
                    World[i][j].rect.setPosition((i)*CELLSIZE, (j)*CELLSIZE);
                    World[i][j].rect.setFillColor(Color::Green);
                    WindowRef.draw(World[i][j].rect);
                }
            }
        }
    }
    
    
    /**
     * Function: outfileBoard
     *     Prints array to output file
     * parm
     *    None
     * returns:
     *       None
     */
    void outfileBoard(ofstream &outfile){
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                outfile << World[i][j].alive;
            }
            outfile << endl;
        }
    }
};



/**
 * directionType : A single instance of a cell in a Game of Life array
 * Data-Elements:
 *     int x;    // x direction (positive = right)
 *     int y;    // y direction (positive = down)
 * Methods:
 *     None
 */
struct directionType {
    int x;
    int y;
    directionType() {
        x = 1;
        y = 1;
    }
};

/**
 * directionType direction:
 * params:
 *    int rows - number of rows in 2D array
 *    int cols - numberof cols in 2D array
 * returns: **RectangleShape (pointer)
 */
directionType direction(CircleShape shape, Vector2u winSize) {
    Vector2f position = shape.getPosition();
    
    directionType d;
    
    if (position.x >= winSize.x) {
        d.x = -1;
    }
    if (position.y >= winSize.y) {
        d.y = -1;
    }
    
    if (position.x <= 0) {
        d.x = 1;
    }
    if (position.y <= 0) {
        d.y = 1;
    }
    
    return d;
}


int main(int argc, char** argv) {
    // input output initilization
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open("output.txt");
    RenderWindow window(VideoMode(600, 600), "Game of Life");
    
    int frameRate = 1;
    int frameCount = 0;
    
    // setting size of window
    Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;
    gameOfLife Gol(window,infile);

    // while window is open print board, count the neighbors, run through the rules,
    // and resets the neighborCount to zero so we can loop again.
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        
        Gol.printBoard();
        Gol.countNeighbors();
        Gol.rules();
        Gol.resetNeighborCount();

        if (frameCount % frameRate == 0) {
            window.display();
        }

        frameCount++;
        
        if(frameCount == 338){
            break;
        }
    }
    
    // outfiles board to output file
    Gol.outfileBoard(outfile);
    return 0;
}
